/** 
* @file zn_log.c
* @brief 基于 linux API 封装日志相关接口
* @author zhunian0322@163.com
* @date 19:22 2017/10/31
* @version 1
*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

#include "../inc/zn_log.h"

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

struct zn_log_configs {
	uint8_t *fileName;
	uint8_t saved;
	uint16_t logBufSize;
	uint8_t *pbuf;
};

static const char *zn_log_level_str[] = { [ZLL_DEBUG] = "DEBUG", [ZLL_WARNIG
        ] = "WARNIG", [ZLL_ERROR] = "ERROR" };

static char * getCurrentTime() {
	static char time_buf[1024];
	memset(time_buf, 0, 1024);
	time_t ts;
	time(&ts);
	ctime_r(&ts, time_buf);

	time_buf[strlen(time_buf) - 1] = '\0';

	return time_buf;
}

static void zn_log_print(zn_log_config *zlc) {
	printf("%s\n", zlc->pbuf);
}

static void zn_log_save_flash(zn_log_config *zlc) {
	FILE *pfile = NULL;
	pfile = fopen((char *) zlc->fileName, "a+");
	if (pfile == NULL) {
		pfile = fopen((char *) zlc->fileName, "w+");
		if (pfile == NULL) return;
	}

	fwrite("\n", strlen("\n"), 1, pfile);
	fwrite((char *) zlc->pbuf, strlen((char *) zlc->pbuf), 1, pfile);
	fclose(pfile);
}

zn_log_config * zn_log_init(uint8_t *fileName, ZN_LOG_SAVE_FLAG saveFlag,
        uint16_t logBufSize) {
	zn_log_config *zn = (zn_log_config *) malloc(sizeof(struct zn_log_configs));
	if (zn == NULL) return NULL;
	if (fileName != NULL) zn->fileName = (uint8_t *) strdup((char *) fileName);
	zn->saved = saveFlag;
	zn->logBufSize = logBufSize;
	zn->pbuf = (uint8_t *) malloc(sizeof(uint8_t) * zn->logBufSize);

	if (zn->fileName == NULL || zn->pbuf == NULL) zn_log_destory(&zn);

	return zn;
}

void zn_log(char *filename, int line, zn_log_config * zlc, uint8_t level,
        const uint8_t *tag, char *format, ...) {
	int log_len = 0;
	va_list args;

	pthread_mutex_lock(&log_mutex);

	memset(zlc->pbuf, 0, zlc->logBufSize);

	switch (level) {
	case ZLL_CUSTOM:
		snprintf((char *) zlc->pbuf, zlc->logBufSize, "[%s] [%s] [%u] (%s:%d) ",
		        tag, getCurrentTime(), (unsigned int) getpid(), filename, line);
		break;

	case ZLL_DEBUG:
	case ZLL_WARNIG:
	case ZLL_ERROR:
		snprintf((char *) zlc->pbuf, zlc->logBufSize, "[%s] [%s] [%u] (%s:%d) ",
		        zn_log_level_str[level], getCurrentTime(),
		        (unsigned int) getpid(), filename, line);
		break;
	}

	log_len = (int) strlen((char *) zlc->pbuf);

	va_start(args, format);
	vsnprintf((char *) zlc->pbuf + log_len, zlc->logBufSize - log_len - 1,
	        format, args);
	va_end(args);

	switch (zlc->saved) {
	case ZLSF_NOT:

		break;

	case ZLSF_PRINT:
		zn_log_print(zlc);
		break;

	case ZLSF_FLASH:
		zn_log_save_flash(zlc);
		break;

	case ZLSF_FULL:
		zn_log_print(zlc);
		zn_log_save_flash(zlc);
		break;
	}

	pthread_mutex_unlock(&log_mutex);
}

void zn_log_destory(zn_log_config ** logConfig) {
	if (*logConfig == NULL) return;

	if ((*logConfig)->fileName != NULL) {
		free((*logConfig)->fileName);
		(*logConfig)->fileName = NULL;
	}

	if ((*logConfig)->pbuf != NULL) {
		free((*logConfig)->pbuf);
		(*logConfig)->pbuf = NULL;
	}

	free(*logConfig);
	*logConfig = NULL;
}
