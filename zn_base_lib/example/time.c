/*
 * time.c
 *
 *  Created on: Oct 22, 2017
 *      Author: gino
 */

#include <stdio.h>

#include "../inc/zn_base_time.h"

int main() {

	zn_time_info zti;
	zn_base_getSystemNowTime(&zti);

	printf("timezone is ");
	switch (zn_base_getSystemTimeZone(zti)) {
	case TZ_WEST_ELEVEN:
		printf("WEST_ELEVEN");
		break;

	case TZ_WEST_TEN:
		printf("WEST_TEN");
		break;

	case TZ_WEST_NINE:
		printf("WEST_NINE");
		break;

	case TZ_WEST_EIGHT:
		printf("WEST_EIGHT");
		break;

	case TZ_WEST_SEVEN:
		printf("WEST_SEVEN");
		break;

	case TZ_WEST_SIX:
		printf("WEST_SIX");
		break;

	case TZ_WEST_FIVE:
		printf("WEST_FIVE");
		break;

	case TZ_WEST_FOUR:
		printf("WEST_FOUR");
		break;

	case TZ_WEST_THREE:
		printf("WEST_THREE");
		break;

	case TZ_WEST_TWO:
		printf("WEST_TWO");
		break;

	case TZ_WEST_ONE:
		printf("WEST_ONE");
		break;

	case TZ_EAST_WEST_TWELVE:
		printf("EAST_WEST_TWELVE");
		break;

	case TZ_EAST_ONE:
		printf("EAST_ONE");
		break;

	case TZ_EAST_TWO:
		printf("EAST_TWO");
		break;

	case TZ_EAST_THREE:
		printf("EAST_THREE");
		break;

	case TZ_EAST_FOUR:
		printf("EAST_FOUR");
		break;

	case TZ_EAST_FIVE:
		printf("EAST_FIVE");
		break;

	case TZ_EAST_SIX:
		printf("EAST_SIX");
		break;

	case TZ_EAST_SEVEN:
		printf("EAST_SEVEN");
		break;

	case TZ_EAST_EIGHT:
		printf("EAST_EIGHT");
		break;

	case TZ_EAST_NINE:
		printf("EAST_NINE");
		break;

	case TZ_EAST_TEN:
		printf("EAST_TEN");
		break;

	case TZ_EAST_ELEVEN:
		printf("EAST_ELEVEN");
		break;
	}
	printf("\n");


	char result[1024] = {'\0'};
	// 2017-10-22 15:11:56
	zn_base_getSystenNowTime_format(result,1024,"%F %T",zti);
	printf("result = %s\n",result);

	/**
	 * result = 10/22/17 15:18:00
	 * 2017-10-22 15:18:00
	 * zone: CST
	 */
	zn_base_getSystenNowTime_format(result,1024,"%x %X %n%Y-%m-%d %H:%M:%S %nzone: %Z",zti);
	printf("result = %s\n",result);
}
