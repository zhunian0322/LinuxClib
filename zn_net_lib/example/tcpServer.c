/*
 * tcpServer.c
 *
 *  Created on: Sep 29, 2017
 *      Author: gino
 */

#include "../inc/zn_tcp.h"

#define SERVER_HOSTNAME "localhost"
#define SERVER_PORT		3999

int main() {
	int fd = zn_tcpServer_init(SERVER_HOSTNAME, SERVER_PORT, 10);

	struct sockaddr_in clientAddr;
	char recvBuf[1024];
	while (1) {
		memset(recvBuf, 0, 1024);
		int cfd = zn_tcpServer_accept(fd, &clientAddr);
		int size = zn_tcpRecv(cfd, recvBuf, 1024, -1);
		printf("recv sizeof : %d , msg : %s\n", size, recvBuf);

	}

	zn_tcpDestory(fd);
}
