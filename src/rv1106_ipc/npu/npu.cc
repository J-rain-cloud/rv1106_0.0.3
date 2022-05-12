#include "npu.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "../include/rk_comm_video.h"
#include "RgaApi.h"
#include <vector>
#include "postprocess.h"
#include "draw_rect.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct _network{
    int width=0;                                                  // 模型需要的宽度
    int height=0;                                                 // 模型需要的高度 
    int channel=0;                                                // 模型需要的通道数量

    rknn_input_output_num io_num;                               // 输入输出端口数量 
    rknn_tensor_attr input_attrs[1];                              // 网络的输入属性 
    rknn_tensor_attr output_attrs[3];                             // 网络的输出属性 
    rknn_tensor_attr orig_output_attrs[3];                      // 原始输出属性
    rknn_tensor_mem *output_mems_nchw[3] ={NULL};
    
    rknn_custom_string custom_string;                           //自定义字符串

    rknn_tensor_mem *input_mems[1] = {NULL};                    //输入缓存
    rknn_tensor_mem *output_mems[3] = {NULL};                   //输出缓存


    std::vector<float> out_scales;                              //缩放尺度
    std::vector<int32_t> out_zps;                               //零点

    /* 目标检测 */
    float scale_w;
    float scale_h;
    const float nms_threshold = NMS_THRESH;
    const float box_conf_threshold = BOX_THRESH;
    detect_result_group_t detect_result_group;

}network_info_s;

static network_info_s network;
static rga_info_s rga;
static rknn_tensor_type input_type = RKNN_TENSOR_UINT8;
static rknn_tensor_format input_layout = RKNN_TENSOR_NHWC;
static rknn_context ctx = 0;
static int ret = 0;

static bool g_npu_run = true;
static bool g_recv_data = false;
static bool g_process_end = true;
static int g_img_width = 0;
static int g_img_height = 0;
static int g_img_channel = 3;

static unsigned char *g_input_data = NULL;

static pthread_mutex_t g_network_lock = PTHREAD_MUTEX_INITIALIZER;

static int g_fd;
static pthread_t g_npu_proc;

void * npu_process(void *arg);
/*-------------------------------------------
                  Functions
-------------------------------------------*/
// 画框函数 imfill
static int draw_box(rga_buffer_t buf, im_rect *rect, int line_pixel, int color)
{    
    int x = rect->x;
    int y = rect->y;
    int width = rect->width;
    int height = rect->height;

	im_rect rect_up = {x, y, width, line_pixel};
	im_rect rect_buttom = {x, y + height - line_pixel, width, line_pixel};
	im_rect rect_left = {x, y, line_pixel, height};
	im_rect rect_right = {x + width - line_pixel, y, line_pixel, height};
	IM_STATUS STATUS = imfill(buf, rect_up, color);
	STATUS = imfill(buf, rect_buttom, color);
	STATUS = imfill(buf, rect_left, color);
	STATUS = imfill(buf, rect_right, color);
	return STATUS == IM_STATUS_SUCCESS ? 0 : 1;
}

// 分配输入输出内存,设置对应的结构体信息
static int allocate_in_out_mem()
{
	// 分配输入内存
	network.input_mems[0] = rknn_create_mem(ctx, network.input_attrs[0].size_with_stride);
	if (network.input_mems[0] == NULL) {
		printf("--------allocate input memory failed--------\n");
		return -1;
	}

	// 分配输出内存
	for (uint32_t i = 0; i < network.io_num.n_output; ++i) {
		network.output_mems[i] =
			rknn_create_mem(ctx, network.output_attrs[i].size_with_stride);
		if (network.output_mems[i] == NULL) {
			printf("--------allocate output memory failed--------\n");
			return -1;
		}
	}

	// 设置输入的结构体信息
	ret = rknn_set_io_mem(ctx, network.input_mems[0], &network.input_attrs[0]);
	if (ret < 0) {
		printf("input_memory: rknn_set_io_mem fail! ret=%d\n", ret);
		return -1;
	}

	// 设置输出的结构体信息
	for (uint32_t i = 0; i < network.io_num.n_output; ++i) {
		// set output memory and attribute
		ret = rknn_set_io_mem(ctx, network.output_mems[i], &network.output_attrs[i]);
		if (ret < 0) {
			printf("output_memory: rknn_set_io_mem fail! ret=%d\n", ret);
			return -1;
		}
	}
	printf("--------set in_out put struct info over--------\n");
	return 0;
}

// rga处理,尺寸变换,映射到input.mem中
static int rga_resize(rga_info_s * rga)
{
	rga->src = wrapbuffer_physicaladdr((void *)rga->image_md_info.phyAddr, rga->image_md_info.width,
			rga->image_md_info.height, RK_FORMAT_YCbCr_420_SP);
	rga->dst = wrapbuffer_physicaladdr((void *)network.input_mems[0]->phys_addr, 
			network.width, network.height, RK_FORMAT_RGB_888);
	ret = imcheck(rga->src, rga->dst, rga->src_rect, rga->dst_rect);
	if (IM_STATUS_NOERROR != ret)
	{
		printf("%d, check error! %s", __LINE__, imStrError((IM_STATUS)ret));
		return -1;
	}
	IM_STATUS STATUS = imresize(rga->src, rga->dst);
	return IM_STATUS_SUCCESS;
}

// 打印tensor
static void dump_tensor_attr(rknn_tensor_attr *attr) {
	char dims[128] = {0};
	for (int i = 0; i < attr->n_dims; ++i) {
		int idx = strlen(dims);
		sprintf(&dims[idx], "%d%s", attr->dims[i], (i == attr->n_dims - 1) ? "" : ", ");
	}
	printf("  index=%d, name=%s, n_dims=%d, dims=[%s], n_elems=%d, size=%d, fmt=%s, type=%s, "
	       "qnt_type=%s, "
	       "zp=%d, scale=%f\n",
	       attr->index, attr->name, attr->n_dims, dims, attr->n_elems, attr->size,
	       get_format_string(attr->fmt), get_type_string(attr->type),
	       get_qnt_type_string(attr->qnt_type), attr->zp, attr->scale);
}

// 通道转换
static int NC1HWC2_to_NCHW(const int8_t *src, int8_t *dst, uint32_t *dims, int channel,
                           int hw_dst) {
	int batch = dims[0];
	int C1 = dims[1];
	int h = dims[2];
	int w = dims[3];
	int C2 = dims[4];
	int hw_src = w * h;
	for (int i = 0; i < batch; i++) {
		src = src + i * C1 * hw_src * C2;
		dst = dst + i * channel * hw_dst;
		for (int c = 0; c < channel; ++c) {
			int plane = c / C2;
			const int8_t *src_c = plane * hw_src * C2 + src;
			int offset = c % C2;
			for (int cur_h = 0; cur_h < h; ++cur_h)
				for (int cur_w = 0; cur_w < w; ++cur_w) {
					int cur_hw = cur_h * w + cur_w;
					dst[c * hw_dst + cur_h * w + cur_w] = src_c[C2 * cur_hw + offset];
				}
		}
	}

	return 0;
}

// 查询模型的origin output,分配输出通道NHCW的结构体内存
static int query_origin_output(){
	// 查询网络推理的原始输出
	memset(network.orig_output_attrs, 0, network.io_num.n_output * sizeof(rknn_tensor_attr));
	for (uint32_t i = 0; i < network.io_num.n_output; i++) {
		network.orig_output_attrs[i].index = i;
		// query info
		ret = rknn_query(ctx, RKNN_QUERY_OUTPUT_ATTR, &(network.orig_output_attrs[i]),
							sizeof(rknn_tensor_attr));
		if (ret != RKNN_SUCC) {
			printf("rknn_query fail! ret=%d\n", ret);
			return -1;
		}
		//dump_tensor_attr(&network.orig_output_attrs[i]);
	}

	// 分配输出NCHW的结构体内存

	for (uint32_t i = 0; i < network.io_num.n_output; ++i) {
		int size = network.orig_output_attrs[i].size_with_stride;
		network.output_mems_nchw[i] = rknn_create_mem(ctx, size);
	}

	for (uint32_t i = 0; i < network.io_num.n_output; i++) {
		int channel = network.orig_output_attrs[i].dims[1];
		int h = network.orig_output_attrs[i].n_dims > 2 ? network.orig_output_attrs[i].dims[2] : 1;
		int w = network.orig_output_attrs[i].n_dims > 3 ? network.orig_output_attrs[i].dims[3] : 1;
		int hw = h * w;
		// 拷贝输出的NCHW数据到预先分配的输出内存上  模型默认输出NC1HWC2,需要转换为NCHW
		ret = NC1HWC2_to_NCHW((int8_t *)network.output_mems[i]->virt_addr,
								(int8_t *)network.output_mems_nchw[i]->virt_addr,
								network.output_attrs[i].dims, channel, hw);
		if (ret != 0) {
			printf("--------transfer NC1HWC2 to NCHW failed--------\n");
			return -1;
		}
	}
	return 0;
}

// RGA对应的格式
static int get_rga_format(int src_format) {
	int dst_format;
	switch (src_format) {
	case RK_FMT_YUV420SP:
		dst_format = RK_FORMAT_YCbCr_420_SP;
		break;
	case RK_FMT_RGB888:
		dst_format = RK_FORMAT_RGB_888;
		break;
	case RK_FMT_BGR888:
		dst_format = RK_FORMAT_BGR_888;
		break;
	default:
		dst_format = RK_FORMAT_RGB_888;
		break;
	}
	return dst_format;
}

// 格式字符串
static char *get_rga_format_string(int format, char *str) {
	switch (format) {
	case RK_FORMAT_YCbCr_420_SP:
		strcpy(str, "RK_FORMAT_YCbCr_420_SP");
		break;
	case RK_FORMAT_RGB_888:
		strcpy(str, "RK_FORMAT_RGB_888");
		break;
	case RK_FORMAT_BGR_888:
		strcpy(str, "RK_FORMAT_BGR_888");
		break;
	default:
		strcpy(str, "none");
		break;
	}

	return str;
}

void recv_frame(RK_VOID *ptr, RK_U64 phy, int width, int height, int format, int fd) {
    int ret;
    g_img_width = width;
    g_img_height = height;
	char str[1024];

	rga_buffer_t src, dst;
    im_rect src_rect, dst_rect;
	im_handle_param_t src_param, dst_param;
	rga_buffer_handle_t src_handle, dst_handle;
	
    do {
        pthread_mutex_lock(&g_network_lock);
        if (g_process_end == false) {
            printf("-------- npu processing --------\n");
            break;
        }

        memset(&src, 0, sizeof(src));
		memset(&dst, 0, sizeof(dst));
		memset(&src_rect, 0, sizeof(src_rect));
		memset(&dst_rect, 0, sizeof(dst_rect));
		memset(&src_param, 0, sizeof(im_handle_param_t));
		memset(&dst_param, 0, sizeof(im_handle_param_t));

		src_handle = importbuffer_physicaladdr(phy, &src_param);
		dst_handle = importbuffer_physicaladdr(network.input_mems[0]->phys_addr, &dst_param);
		src = wrapbuffer_handle_t(src_handle, width, height, width, height, get_rga_format(format));
		dst = wrapbuffer_handle_t(dst_handle, network.width, network.height, network.width, network.height, RK_FORMAT_RGB_888);

        ret = imcheck(src, dst, src_rect, dst_rect);
        if (IM_STATUS_NOERROR != ret){
            printf("%d, check error! %s", __LINE__, imStrError((IM_STATUS)ret));
            break;
        }
        // printf("-------- check success--------\n");

        IM_STATUS STATUS = imresize(src, dst);
        if(STATUS != IM_STATUS_SUCCESS){
            printf("--------imresize failed--------\n");
			break;
        }
        // printf("--------imresize success--------\n");

        g_recv_data = true;
        g_process_end = false;
    } while(0);

    pthread_mutex_unlock(&g_network_lock);
	im_rect object_rect;
	// YUV_Rect object_rect;
	// YUV_Color red = {76, 84, 255};
    // printf("--------network.detect_result_group.count=%d--------\n", network.detect_result_group.count);
    for (int i = 0; i < network.detect_result_group.count; i++)
    {   
        detect_result_t *det_result = &(network.detect_result_group.results[i]);
        printf("det_result->name:%s, det_result->prop%.7f\n", det_result->name, det_result->prop * 100);
        printf("%s @ (%d %d %d %d) %f\n",
           det_result->name,
           det_result->box.left, det_result->box.top, det_result->box.right, det_result->box.bottom,
           det_result->prop);

		// 画框
		object_rect.x = det_result->box.left;
		object_rect.y = det_result->box.top;
		object_rect.width = det_result->box.right - det_result->box.left;
		object_rect.height = det_result->box.bottom - det_result->box.top;
		printf("x=%d, y=%d, box_width=%d, box_height=%d\n", object_rect.x, object_rect.y, object_rect.width, object_rect.height);
		draw_box(src, &object_rect, 2, 0x000000ff);
		// yuv420_draw_rectangle(ptr, width, height, rect, red);

		/*ret = draw_box(src, x, y, box_width, box_height, 2, 0x0000ff);
		if(ret == 0){
			printf("--------draw box failed--------\n");
		}*/

		// stbi_write_png("/user/out.png", 640, 640, 3, network.input_mems[0]->virt_addr, 0);
		// stbi_write_png("/user/out.png", 640, 640, 3, dst.vir_addr, 0);
		printf("--------save png image--------\n");
	}
	
    return ;
}

// network init
int network_init(char *model_path) {
	// load model
	ret = rknn_init(&ctx, model_path, 0, 0, NULL);
	if (ret < 0) {
		printf("--------rknn_init fail! ret=%d--------\n", ret);
		return -1;
	}

	// sdk version
	rknn_sdk_version sdk_version;
	ret = rknn_query(ctx, RKNN_QUERY_SDK_VERSION, &sdk_version, sizeof(sdk_version));
	if (ret != RKNN_SUCC) {
		printf("rknn_query version fail! ret=%d\n", ret);
		return -1;
	}
	printf("rknn_api/rknnrt version: %s, driver version: %s\n", sdk_version.api_version,
	       sdk_version.drv_version);

	// input output num
	ret = rknn_query(ctx, RKNN_QUERY_IN_OUT_NUM, &network.io_num, sizeof(network.io_num));
	if (ret != RKNN_SUCC) {
		printf("rknn_query in_out_num fail! ret=%d\n", ret);
		return -1;
	}
	printf("model input num: %d, output num: %d\n", network.io_num.n_input,
	       network.io_num.n_output);

	// input tensor
	printf("input tensors:\n");
	// network.input_attrs =
	//     (rknn_tensor_attr *)malloc(sizeof(rknn_tensor_attr) * network.io_num.n_input);
	memset(network.input_attrs, 0, network.io_num.n_input * sizeof(rknn_tensor_attr));
	printf("----------------------------->>\n");
	for (uint32_t i = 0; i < network.io_num.n_input; i++) {
		network.input_attrs[i].index = i;
		// query info
		ret = rknn_query(ctx, RKNN_QUERY_NATIVE_INPUT_ATTR, &(network.input_attrs[i]),
		                 sizeof(rknn_tensor_attr));
		if (ret < 0) {
			printf("rknn_query input error! ret=%d\n", ret);
			return -1;
		}
		dump_tensor_attr(&network.input_attrs[i]);
	}

	// output tensor
	printf("output tensors:\n");
	// network.output_attrs =
	//     (rknn_tensor_attr *)malloc(sizeof(rknn_tensor_attr) * network.io_num.n_output);
	memset(network.output_attrs, 0, network.io_num.n_output * sizeof(rknn_tensor_attr));
	printf("----------------------------->>\n");
	for (uint32_t i = 0; i < network.io_num.n_output; i++) {
		network.output_attrs[i].index = i;
		// query info
		ret = rknn_query(ctx, RKNN_QUERY_NATIVE_OUTPUT_ATTR, &(network.output_attrs[i]),
		                 sizeof(rknn_tensor_attr));
		if (ret != RKNN_SUCC) {
			printf("rknn_query output error! ret=%d\n", ret);
			return -1;
		}
		dump_tensor_attr(&network.output_attrs[i]);
	}

	// Get custom string
	ret = rknn_query(ctx, RKNN_QUERY_CUSTOM_STRING, &network.custom_string,
	                 sizeof(network.custom_string));
	if (ret != RKNN_SUCC) {
		printf("rknn_query fail! ret=%d\n", ret);
		return -1;
	}
	printf("custom string: %s\n", network.custom_string.string);

	//网络输入格式
	network.input_attrs[0].type = input_type;
	network.input_attrs[0].fmt = input_layout; // 默认是NHWC, NPU在零拷贝的模式下只支持NHWC

	printf("--------network init over--------\n");

	//网络的输入通道宽高
	if (network.input_attrs[0].fmt == RKNN_TENSOR_NCHW) {
		printf("model is NCHW input fmt\n");
		network.channel = network.input_attrs[0].dims[1];
		network.width = network.input_attrs[0].dims[2];
		network.height = network.input_attrs[0].dims[3];
	} else {
		printf("model is NHWC input fmt\n");
		network.channel = network.input_attrs[0].dims[3];
		network.width = network.input_attrs[0].dims[1];
		network.height = network.input_attrs[0].dims[2];
	}
			
	ret = allocate_in_out_mem();
	if(ret != 0){
		printf("--------allocate_in_out_memfailed--------\n");
		return -1;
	}

	// 开启NPU处理线程
	pthread_create(&g_npu_proc, NULL, npu_process, (void *)&ctx);
	return 0;
}

// npu process
void *npu_process(void *arg) {
    int epoch = 0;
	printf("--------%s thread start--------\n", __func__);
	rknn_context *ctx = (rknn_context *)arg;
	int ret = 0;
    //缩放尺度
	do { // 没有拿到互斥锁,这堵塞等待解锁
		pthread_mutex_lock(&g_network_lock);
		//拿到锁后判断是否有数据  input_data
		if (g_recv_data == false) {
			pthread_mutex_unlock(&g_network_lock);
			continue;
		}
		//有数据则进行下一步
		network.scale_w = (float)network.width / g_img_width;
	    network.scale_h = (float)network.height / g_img_height;
	    /* printf("--------model_width=%d, model_height=%d, input_width=%d, input_height=%d--------\n",
			network.width, network.height, g_img_width, g_img_height);*/
		// Run
		ret = rknn_run(*ctx, NULL);
		if (ret < 0) {
			printf("rknn run error %d\n", ret);
			pthread_exit((void *)-1);
		}

		ret = query_origin_output();
		if(ret != 0){
			printf("--------query_origin_output failed--------\n");
			pthread_exit((void *)-1);
		}
	
		// post process
		for (int i = 0; i < network.io_num.n_output; ++i) {
			network.out_scales.push_back(network.output_attrs[i].scale);
			network.out_zps.push_back(network.output_attrs[i].zp);
		}
		ret = post_process(
		    (int8_t *)network.output_mems_nchw[0]->virt_addr, (int8_t *)network.output_mems_nchw[1]->virt_addr,
		    (int8_t *)network.output_mems_nchw[2]->virt_addr, 640, 640, network.box_conf_threshold,
		    network.nms_threshold, network.scale_w, network.scale_h, network.out_zps,
		    network.out_scales, &network.detect_result_group);
        if (ret != 0) {
			printf("--------post process failed--------\n");
		}

        // printf("--------post process end--------\n");
        
		g_process_end = true;
		g_recv_data = false;
		// printf("------epoch %d--------\n", epoch++);
		// 释放锁
		pthread_mutex_unlock(&g_network_lock);

        for (uint32_t i = 0; i < network.io_num.n_output; ++i) {
            if(network.output_mems_nchw[i] != NULL){
			    rknn_destroy_mem(*ctx, network.output_mems_nchw[i]);
            }
		}
        
	} while (g_npu_run);

	printf("--------npu_process thread exit--------\n");
	pthread_exit((void *)-1);
}

// network deinit
void network_exit() {
	g_npu_run = false;

	if (g_npu_proc) {
		pthread_join(g_npu_proc, NULL);
		g_npu_proc = 0;
	}

	// Destroy rknn memory
	if(network.input_mems[0] != NULL){
		rknn_destroy_mem(ctx, network.input_mems[0]);
	}
	
	for (uint32_t i = 0; i < network.io_num.n_output; ++i) {
		if(network.output_mems[i] != NULL){
			rknn_destroy_mem(ctx, network.output_mems[i]);
		}
        if(network.output_mems_nchw[i] != NULL){
			rknn_destroy_mem(ctx, network.output_mems_nchw[i]);
        }
	}
	printf("--------network deinit--------\n");

	rknn_destroy(ctx);

	if (g_input_data)
		free(g_input_data);
	/*if(network.input_attrs)
		free(network.input_attrs);
	if(network.output_attrs)
		free(network.output_attrs);*/
	printf("--------network deinit over--------\n");
}