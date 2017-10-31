/*
 * log_test.c
 *
 *  Created on: Oct 31, 2017
 *      Author: gino
 */

#include <stdio.h>

#include "../inc/zn_log.h"

int main(){

	zn_log_config * zlcs = zn_log_init((uint8_t *)"/tmp/test.log",ZLSF_FULL,4096);
	ZNLOG_DEBUG(zlcs,"%s\n","hello");
	ZNLOG_CUSTOM(zlcs,(uint8_t *)"TEST","%s\n","HELLO");
}
