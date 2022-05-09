#include <getopt.h>

#include "audio.h"
#include "common.h"
#include "isp.h"
#include "log.h"
#include "osd.h"
#include "param.h"
#include "rockiva.h"
#include "server.h"
#include "storage.h"
#include "system.h"
#include "video.h"

#include <rk_mpi_sys.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "rkipc.c"

enum { LOG_ERROR, LOG_WARN, LOG_INFO, LOG_DEBUG };

int enable_minilog = 0;
int rkipc_log_level = LOG_DEBUG;

static int g_main_run_ = 1;
char *rkipc_ini_path_ = NULL;
char *rkipc_iq_file_path_ = NULL;

static void sig_proc(int signo) {
	LOG_INFO("received signo %d \n", signo);
	g_main_run_ = 0;
}

static const char short_options[] = "c:a:l:";
static const struct option long_options[] = {{"config", required_argument, NULL, 'c'},
                                             {"aiq_file", no_argument, NULL, 'a'},
                                             {"log_level", no_argument, NULL, 'l'},
                                             {"help", no_argument, NULL, 'h'},
                                             {0, 0, 0, 0}};

static void usage_tip(FILE *fp, int argc, char **argv) {
	fprintf(fp,
	        "Usage: %s [options]\n"
	        "Version %s\n"
	        "Options:\n"
	        "-c | --config      rkipc ini file, default is "
	        "/userdata/rkipc.ini, need to be writable\n"
	        "-a | --aiq_file    aiq file dir path, default is /etc/iqfiles\n"
	        "-l | --log_level   log_level [0/1/2/3], default is 2\n"
	        "-h | --help        for help \n\n"
	        "\n",
	        argv[0], "V1.0");
}

void rkipc_get_opt(int argc, char *argv[]) {
	for (;;) {
		int idx;
		int c;
		c = getopt_long(argc, argv, short_options, long_options, &idx);
		if (-1 == c)
			break;
		switch (c) {
		case 0: /* getopt_long() flag */
			break;
		case 'c':
			rkipc_ini_path_ = optarg;
			break;
		case 'a':
			rkipc_iq_file_path_ = optarg;
			break;
		case 'l':
			rkipc_log_level = atoi(optarg);
			break;
		case 'h':
			usage_tip(stdout, argc, argv);
			exit(EXIT_SUCCESS);
		default:
			usage_tip(stderr, argc, argv);
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char **argv) {
	LOG_INFO("main begin\n");
	signal(SIGINT, sig_proc);

	rkipc_get_opt(argc, argv);
	LOG_INFO("rkipc_ini_path_ is %s, rkipc_iq_file_path_ is %s, rkipc_log_level "
	         "is %d\n",
	         rkipc_ini_path_, rkipc_iq_file_path_, rkipc_log_level);

	// init
	rk_param_init(rkipc_ini_path_);
	rk_system_init();
#if 1
	rk_isp_group_init(0, rkipc_iq_file_path_);
#else
	rk_isp_init(0, rkipc_iq_file_path_);
	rk_isp_init(1, rkipc_iq_file_path_);
	rk_isp_init(2, rkipc_iq_file_path_);
	rk_isp_init(3, rkipc_iq_file_path_);
	rk_isp_init(4, rkipc_iq_file_path_);
	rk_isp_init(5, rkipc_iq_file_path_);
	// rk_isp_init(6, rkipc_iq_file_path_);
	// rk_isp_init(7, rkipc_iq_file_path_);
#endif
	// rk_isp_group_set_frame_rate(0, rk_param_get_int("isp.0.adjustment:fps", 30));
	RK_MPI_SYS_Init();
	rk_video_init();
	if (rk_param_get_int("audio.0:enable", 0))
		rkipc_audio_init();
	rkipc_server_init();
	rk_storage_init();
	if (rk_param_get_int("avs:enable_npu", 0))
		rkipc_rockiva_init();

	while (g_main_run_) {
		usleep(1000 * 1000);
	}

	// deinit
	rk_storage_deinit();
	rkipc_server_deinit();
	rk_system_deinit();
	if (rk_param_get_int("audio.0:enable", 0))
		rkipc_audio_deinit();
	rk_video_deinit();
	RK_MPI_SYS_Exit();
	rk_isp_group_deinit(0);
	if (rk_param_get_int("avs:enable_npu", 0))
		rkipc_rockiva_deinit();
	rk_param_deinit();

	return 0;
}
