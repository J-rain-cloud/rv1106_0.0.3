#ifndef __NPU_H__
#define __NPU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "video.h"
#include "rknn_api.h"
#include "im2d.h"
#include "im2d_type.h"

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define PERF_WITH_POST 1
#define _BASETSD_H

typedef struct _image_md_info
{
 int width;
 int height;
 int channel;

 MB_POOL pool;
 MB_BLK mb;
 RK_U64 phyAddr;
 RK_VOID *virAddr;
}image_md_info_s;

typedef struct _rga_info
{
    rga_buffer_t src;
	rga_buffer_t dst;
	im_rect src_rect;
	im_rect dst_rect;
    im_handle_param_t param;                                    // rga待导入图像缓冲区的参数
    im_rect image_box;                                          // rga 绘制框

    image_md_info_s image_md_info;                              // rga 映射的物理缓冲区
}rga_info_s;

int network_init(char * model_path);
void network_exit();
void recv_frame(RK_VOID *ptr, RK_U64 phy, int width, int height, int format, int fd);

#ifdef __cplusplus
}
#endif

#endif //__NPU_H__