/*
 * zn_tcp.h
 *
 *  Created on: Sep 29, 2017
 *      Author: gino
 */

#ifndef ZN_TCP_H_
#define ZN_TCP_H_

#include <netinet/in.h>

int zn_tcpServer_init(const char *host, const int port, const int backlog);
int zn_tcpClient_init();
int zn_tcpClinet_connet(int sock, const char *host, const int port);
int zn_tcpServer_accept(int listenSock, struct sockaddr_in *clientAddr);
int zn_tcpSend(int sock, void *sendBuf, int len);
int zn_tcpRecv(int sock, void *recvBuf, int len, int timeout);
int zn_tcpDestory(const int sock);

#endif /* ZN_TCP_H_ */
