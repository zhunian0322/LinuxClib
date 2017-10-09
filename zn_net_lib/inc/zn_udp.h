/*
 * zn_udp.h
 *
 *  Created on: Sep 30, 2017
 *      Author: gino
 */

#ifndef ZN_UDP_H_
#define ZN_UDP_H_

#include <netinet/in.h>

int zn_udpServer_init(const char *host, const int port);
int zn_udpClient_init(const char *sHost, const int sPort,
        struct sockaddr_in *serverAddr);
int zn_udpBroadcast_init(const char *bHost, const int bPort,
        struct sockaddr_in *broadcastAddr);
int zn_udpSend(int sock, void *sendBuf, int len, const struct sockaddr *to,
        int addrlen);
int zn_udpRecv(int sock, void *recvBuf, int len, struct sockaddr *from,
        int *addrlen);
int zn_udpDestory(const int sock);

#endif /* ZN_UDP_H_ */
