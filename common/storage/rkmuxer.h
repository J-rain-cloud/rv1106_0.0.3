#ifndef __RKMUXER_H__
#define __RKMUXER_H__
#ifdef __cplusplus
extern "C" {
#endif

typedef struct StVideoParam {
	char format[24]; // NV12
	char codec[24];  // H.264, H.265
	int width;
	int height;
	int bit_rate;
	int profile; // h264 profile
	int level;   // h264 level
	int frame_rate_den;
	int frame_rate_num;
	int qp_min;
	int qp_max;
	int vir_width;
	int vir_height;
} VideoParam;

typedef struct StAudioParam {
	char format[24]; // S16,S32
	char codec[24];  // MP2
	int channels;
	int sample_rate;
	int frame_size;
} AudioParam;

int rkmuxer_init(int id, char *format, const char *file_path, VideoParam *video_param,
                 AudioParam *audio_param);
int rkmuxer_deinit(int id);
int rkmuxer_write_video_frame(int id, unsigned char *buffer, unsigned int buffer_size,
                              int64_t present_time, int key_frame);
int rkmuxer_write_audio_frame(int id, unsigned char *buffer, unsigned int buffer_size,
                              int64_t present_time);

#ifdef __cplusplus
}
#endif
#endif