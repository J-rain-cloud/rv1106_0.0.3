// Copyright 2022 Rockchip Electronics Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// #include <locale.h>

#include "roi.h"
#include "common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "roi.c"

#define MAX_ROI_NUM 6

rk_roi_set_callback rk_roi_set_ = NULL;

void rk_roi_set_callback_register(rk_roi_set_callback callback_ptr) { rk_roi_set_ = callback_ptr; }

int rk_roi_set_all() {
	roi_data_s roi_data;
	char entry[128] = {'\0'};
	double x_rate, y_rate;
	int video_width, video_height;
	int normalized_screen_width = rk_param_get_int("osd.common:normalized_screen_width", -1);
	int normalized_screen_height = rk_param_get_int("osd.common:normalized_screen_height", -1);

	for (int id = 0; id < MAX_ROI_NUM; id++) {
		snprintf(entry, 127, "roi.%d:stream_type", id);
		roi_data.stream_type = rk_param_get_string(entry, "mainStream");
		if (!strcmp(roi_data.stream_type, "mainStream")) {
			video_width = rk_param_get_int("video.0:width", -1);
			video_height = rk_param_get_int("video.0:height", -1);
		} else if (!strcmp(roi_data.stream_type, "subStream")) {
			video_width = rk_param_get_int("video.1:width", -1);
			video_height = rk_param_get_int("video.1:height", -1);
		} else {
			video_width = rk_param_get_int("video.2:width", -1);
			video_height = rk_param_get_int("video.2:height", -1);
		}
		x_rate = (double)video_width / (double)normalized_screen_width;
		y_rate = (double)video_height / (double)normalized_screen_height;
		LOG_DEBUG("x_rate is %f, y_rate is %f\n", x_rate, y_rate);

		snprintf(entry, 127, "roi.%d:id", id);
		roi_data.id = rk_param_get_int(entry, -1);
		snprintf(entry, 127, "roi.%d:enabled", id);
		roi_data.enabled = rk_param_get_int(entry, -1);
		snprintf(entry, 127, "roi.%d:position_x", id);
		roi_data.position_x = UPALIGNTO16((int)(rk_param_get_int(entry, -1) * x_rate));
		snprintf(entry, 127, "roi.%d:position_y", id);
		roi_data.position_y = UPALIGNTO16((int)(rk_param_get_int(entry, -1) * y_rate));
		snprintf(entry, 127, "roi.%d:width", id);
		roi_data.width = UPALIGNTO16((int)(rk_param_get_int(entry, -1) * x_rate));
		snprintf(entry, 127, "roi.%d:height", id);
		roi_data.height = UPALIGNTO16((int)(rk_param_get_int(entry, -1) * y_rate));
		snprintf(entry, 127, "roi.%d:quality_level", id);
		roi_data.quality_level = rk_param_get_int(entry, -1);
		rk_roi_set_(&roi_data);
	}

	return 0;
}

// for socket server
// roi.x
int rk_roi_get_stream_type(int id, const char **value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:stream_type", id);
	*value = rk_param_get_string(entry, "mainStream");
	LOG_DEBUG("entry is %s, stream_type is %s\n", entry, *value);

	return 0;
}

int rk_roi_set_stream_type(int id, const char *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:stream_type", id);
	rk_param_set_string(entry, value);

	return 0;
}

int rk_roi_get_name(int id, const char **value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:name", id);
	*value = rk_param_get_string(entry, "test");

	return 0;
}

int rk_roi_set_name(int id, const char *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:name", id);
	rk_param_set_string(entry, value);

	return 0;
}

int rk_roi_get_id(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:id", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_id(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:id", id);
	rk_param_set_int(entry, value);

	return 0;
}

int rk_roi_get_enabled(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:enabled", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_enabled(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:enabled", id);
	rk_param_set_int(entry, value);

	return 0;
}

int rk_roi_get_position_x(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:position_x", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_position_x(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:position_x", id);
	rk_param_set_int(entry, value);

	return 0;
}

int rk_roi_get_position_y(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:position_y", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_position_y(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:position_y", id);
	rk_param_set_int(entry, value);

	return 0;
}

int rk_roi_get_height(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:height", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_height(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:height", id);
	rk_param_set_int(entry, value);

	return 0;
}

int rk_roi_get_width(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:width", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_width(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:width", id);
	rk_param_set_int(entry, value);

	return 0;
}

int rk_roi_get_quality_level(int id, int *value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:quality_level", id);
	*value = rk_param_get_int(entry, -1);

	return 0;
}

int rk_roi_set_quality_level(int id, int value) {
	char entry[128] = {'\0'};
	snprintf(entry, 127, "roi.%d:quality_level", id);
	rk_param_set_int(entry, value);

	return 0;
}
