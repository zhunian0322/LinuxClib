/*
 * udpServer.c
 *
 *  Created on: Oct 9, 2017
 *      Author: gino
 */

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "../inc/zn_udp.h"

#define PORT	 3890
#define HOST	 "0.0.0.0"



int main(){
	int fd = zn_udpServer_init(HOST,PORT);

	char buf[1024];
	struct sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);

	while(1){
		memset(buf,0,1024);
		memset(&fromAddr,0,addrLen);

		int ret = zn_udpRecv(fd,buf,1024,&fromAddr,&addrLen);
		if(ret > 0 )
		{
			printf("client addr %s\n",inet_ntoa(((struct sockaddr_in *)&fromAddr)->sin_addr));
			printf("clinet msg %s\n",buf);
		}

	}

	zn_udpDestory(fd);
}
