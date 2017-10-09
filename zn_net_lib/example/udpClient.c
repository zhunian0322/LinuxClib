/*
 * udpClient.c
 *
 *  Created on: Oct 9, 2017
 *      Author: gino
 */


#include <netinet/in.h>
#include <string.h>

#include "../inc/zn_udp.h"


#define PORT	 3890
#define HOST	 "gino-virtual-machine"

#define MSG		"HelloWorld"

int main(){
	struct sockaddr_in sAddr;
	int fd = zn_udpClient_init(HOST,PORT,&sAddr);
	zn_udpSend(fd,MSG,strlen(MSG),(struct sockaddr *)&sAddr,sizeof(struct sockaddr));
	zn_udpDestory(fd);
}
