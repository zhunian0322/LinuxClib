/*
 * udpBroadcast.c
 *
 *  Created on: Oct 9, 2017
 *      Author: gino
 */


#include <unistd.h>
#include <string.h>


#include "../inc/zn_udp.h"

#define BHOST "192.168.1.255"
#define BPORT 3890

#define BMSG "Broadcast Hello World!"
int main(){
	struct sockaddr_in bAddr;
	int fd = zn_udpBroadcast_init(BHOST,BPORT,&bAddr);

	int i = 3;

	while(i--){
		sleep(1);
		zn_udpSend(fd,BMSG,strlen(BMSG),(struct sockaddr *)&bAddr,sizeof(struct sockaddr));
	}

	zn_udpDestory(fd);
}
