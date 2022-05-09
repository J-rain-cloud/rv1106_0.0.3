// Copyright 2021 Rockchip Electronics Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "common.h"

typedef struct rk_signal_t {
	sem_t sem;
	int max_val;
} rk_signal_t;

/**
 * @brief 创建信号量
 *
 * @param defval 取值为0
 * @param maxval 取值为1
 *
 * @return 成功,返回信号量句柄; 否则,返回空值
 */
void *rk_signal_create(int defval, int maxval) {
	rk_signal_t *h = (rk_signal_t *)malloc(sizeof(rk_signal_t));

	if (h == NULL) {
		return NULL;
	}
	if (sem_init(&(h->sem), 0, defval) == -1) { /* 初始化信号量失败,失败原因见error */
		perror("sem_init: ");
		free(h);
		h = NULL;
	} else
		h->max_val = maxval;
	return h;
}

/**
 * @brief 销毁信号量
 *
 * @param signal 信号量句柄
 */
void rk_signal_destroy(void *sem) {
	if (sem == NULL) {
		return;
	}

	sem_destroy((sem_t *)sem);
	free(sem);
}

/**
 * @brief 等待信号量
 *
 * @param signal 信号量句柄
 * @param timeout -1表示无限等待;其他值表示等待的时间(ms)
 *
 * @return 成功,返回0; 否则,返回-1
 */
int rk_signal_wait(void *sem, int timeout) {
	struct timespec tv;

	if (sem == NULL) {
		return 0;
	}

	if (timeout < 0) { /* 需要判断返回值,因为如果信号量被destroy了也会返回的 */
		return sem_wait((sem_t *)sem) == 0 ? 0 : -1;
	} else {
		clock_gettime(CLOCK_REALTIME, &tv);

		tv.tv_nsec += (timeout % 1000) * 1000000;
		if (tv.tv_nsec >= 1000000000) {
			tv.tv_sec += 1;
			tv.tv_nsec -= 1000000000;
		}
		tv.tv_sec += timeout / 1000;
		if (sem_timedwait((sem_t *)sem, (const struct timespec *)&tv)) {
			return -1;
		}
		return 0;
	}
}

/**
 * @brief 释放信号量
 *
 * @param signal 信号量句柄
 */
void rk_signal_give(void *sem) {
	int val;

	if (sem == NULL) {
		return;
	}

	sem_getvalue((sem_t *)sem, &val);

	if (val < ((rk_signal_t *)sem)->max_val) {
		sem_post((sem_t *)sem);
	}
}

/**
 * @brief 重置信号量
 *
 * @param signal 信号量句柄
 */
void rk_signal_reset(void *sem) { rk_signal_give(sem); }

long long rkipc_get_curren_time_ms() {
	long long msec = 0;
	char str[20] = {0};
	struct timeval stuCurrentTime;

	gettimeofday(&stuCurrentTime, NULL);
	sprintf(str, "%ld%03ld", stuCurrentTime.tv_sec, (stuCurrentTime.tv_usec) / 1000);
	for (size_t i = 0; i < strlen(str); i++) {
		msec = msec * 10 + (str[i] - '0');
	}

	return msec;
}