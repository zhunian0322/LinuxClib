/** 
* @file zn_base_time.c
* @brief 基于 linux API 封装时间相关接口
* @author zhunian0322@163.com
* @date 15:22 2017/10/22
* @version 1
*/

#include <time.h>

#include "../inc/zn_base_time.h"





int zn_base_getSystemNowTime(zn_time_info *zti) {
	return gettimeofday(&zti->tv, &zti->tz);
}

void zn_base_getSystenNowTime_format(char *result, int len, const char *format,
		zn_time_info zti) {
	if (result == NULL || len <= 0)
		return;

	struct tm *tm_now = localtime(&zti.tv.tv_sec);
	strftime(result, len, format, tm_now);
}

ZN_TIMEZONE zn_base_getSystemTimeZone(zn_time_info zti) {
	int timeDiff = zti.tz.tz_minuteswest / 60;
	return (ZN_TIMEZONE) (0 - timeDiff);
}
