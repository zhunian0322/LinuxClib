/*
 * zn_tcp.c
 *
 *  Created on: Sep 29, 2017
 *      Author: gino
 */

#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "zn_tcp.h"

int zn_tcpServer_init(const char *host, const int port, const int backlog) {
	if (NULL == host || port <= 0)
		return -1;

	int ret = 0, recvbuf = 128 * 1024, sendbuf = 128 * 1024;
	int listen_sock = 0;
	struct sockaddr_in sAddr;
	struct hostent *hostname = NULL;
	int readdr = 1;
	struct linger ling;
	ling.l_linger = 0;
	ling.l_onoff = 1;

	if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -2;

	memset(&sAddr, 0, sizeof(struct sockaddr_in));

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);

	if ((hostname = gethostbyname(host)) == NULL)
		sAddr.sin_addr.s_addr = inet_addr(host);
	else
		memcpy(&sAddr.sin_addr, hostname->h_addr,hostname->h_length);

	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &readdr, sizeof(int));
	setsockopt(listen_sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(int));
	setsockopt(listen_sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(int));
	setsockopt(listen_sock, SOL_SOCKET, SO_LINGER, (const char *) &ling,
			sizeof(struct linger));

	if ((ret = bind(listen_sock, (struct sockaddr *) &sAddr,
			sizeof(struct sockaddr_in))) < 0) {
		close(listen_sock);
		return -3;
	}

	if ((ret = listen(listen_sock, backlog)) < 0) {
		close(listen_sock);
		return -4;
	}

	return listen_sock;
}

int zn_tcpClient_init() {

	int sock = 0;
	struct linger ling;
	ling.l_linger = 0;
	ling.l_onoff = 1;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -2;

	setsockopt(sock, SOL_SOCKET, SO_LINGER, (const char *) &ling, sizeof(ling));

	return sock;
}

int zn_tcpClinet_connet(int sock, const char *host, const int port) {
	if (sock <= 0 || NULL == host || port <= 0)
		return -1;

	int ret = 0;
	struct sockaddr_in sAddr;
	struct hostent *hostname = NULL;

	memset(&sAddr, 0, sizeof(struct sockaddr_in));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);

	if ((hostname = gethostbyname(host)) == NULL)
		sAddr.sin_addr.s_addr = inet_addr(host);
	else
		memcpy(&sAddr.sin_addr, hostname->h_addr,hostname->h_length);

	ret = connect(sock, (struct sockaddr *) &sAddr, sizeof(struct sockaddr_in));

	return (ret < 0) ? ret : 0;
}

int zn_tcpServer_accept(int listenSock, struct sockaddr_in *clientAddr) {
	int clientSock = 0;
	int len = sizeof(struct sockaddr_in);
	clientSock = accept(listenSock, (struct sockaddr *) clientAddr, &len);

	return (clientSock < 0) ? -1 : clientSock;
}

int zn_tcpSend(int sock, char *sendBuf, int len) {
	if (sock <= 0 || NULL == sendBuf || len <= 0)
		return -1;

	int ret = 0;
	int dataLeft = len;
	int sendTotal = 0;
	while (dataLeft > 0) {
		ret = send(sock, sendBuf + sendTotal, dataLeft, 0);
		if (ret < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
				usleep(100 * 1000);
				ret = 0;
			}
		}

		sendTotal += ret;
		dataLeft = len - sendTotal;
	}

	return sendTotal;
}

int zn_tcpRecv(int sock, char *recvBuf, int len, int timeout) {
	if (sock <= 0 || NULL == recvBuf || len <= 0)
		return -1;

	int ret = 0;
	fd_set fds;
	struct timeval *interval = NULL, timeval;
	memset(recvBuf, 0, len);
	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	if (timeout >= 0) {
		timeval.tv_sec = timeout;
		timeval.tv_usec = 0;
		interval = &timeval;
	}

	ret = select(sock + 1, &fds, NULL, NULL, interval);
	if (FD_ISSET(sock, &fds))
		ret = recv(sock, recvBuf, len, 0);

	return (ret > 0) ? ret : -2;
}

int zn_tcpDestory(int sock) {
	int ret = 0;
	if (sock <= 0)
		return -1;
	ret = close(sock);
	return (ret == 0) ? 0 : 1;
}
