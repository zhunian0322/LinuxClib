/*
 * tcpClient.c
 *
 *  Created on: Sep 29, 2017
 *      Author: gino
 */


#include "../inc/zn_tcp.h"

#define SERVER_HOSTNAME "localhost"
#define SERVER_PORT		3999

int main(){
	int fd = zn_tcpClient_init();
	zn_tcpClinet_connet(fd, SERVER_HOSTNAME, SERVER_PORT);
	zn_tcpSend(fd,"Hello World!",12);
	zn_tcpDestory(fd);
}
