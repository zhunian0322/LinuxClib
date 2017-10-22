/** 
* @file zn_udp.c
* @brief 基于 linux API 封装 UDP 接口
* @author zhunian0322@163.com
* @date 17:44 2017/10/21
* @version 1
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>




int zn_udpServer_init(const char *host, const int port) {
	if (NULL == host || port <= 0) return -1;

	int sock = -1, ret = 0;
	struct sockaddr_in serverAddr;
	struct hostent *hostname = NULL;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) return -2;

	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	if ((hostname = gethostbyname(host)) == NULL)
		serverAddr.sin_addr.s_addr = inet_addr(host);
	else
		memcpy(&serverAddr.sin_addr, hostname->h_addr,hostname->h_length);

	if ((ret = bind(sock, (struct sockaddr *) &serverAddr,
	        sizeof(struct sockaddr))) < 0) {
		close(sock);
		return -3;
	}

	return sock;
}

int zn_udpClient_init(const char *sHost, const int sPort,
        struct sockaddr_in *serverAddr) {
	if (sHost == NULL || sPort <= 0 || serverAddr == NULL) return -1;

	int sock = -1;
	struct hostent *hostname = NULL;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) return -2;
	memset(serverAddr, 0, sizeof(struct sockaddr_in));

	serverAddr->sin_family = AF_INET;
	serverAddr->sin_port = htons(sPort);

	if ((hostname = gethostbyname(sHost)) == NULL)
		serverAddr->sin_addr.s_addr = inet_addr(sHost);
	else
		memcpy(&serverAddr->sin_addr, hostname->h_addr,hostname->h_length);

	return sock;
}

int zn_udpBroadcast_init(const char *bHost, const int bPort,
        struct sockaddr_in *broadcastAddr) {
	if (bHost == NULL || bPort <= 0 || broadcastAddr == NULL) return -1;
	int sock = -1, ret = 0;
	int boBroadcast = 1;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) return -2;
	memset(broadcastAddr, 0, sizeof(struct sockaddr_in));

	broadcastAddr->sin_family = AF_INET;
	broadcastAddr->sin_port = htons(bPort);

	broadcastAddr->sin_addr.s_addr = inet_addr(bHost);

	if ((ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &boBroadcast,
	        sizeof(boBroadcast))) < 0) return -3;

	return sock;
}

int zn_udpSend(int sock, void *sendBuf, int len, const struct sockaddr *to,
        int addrlen) {
	if (sock
	        <= 0|| sendBuf == NULL || len <= 0 || to == NULL || addrlen <= 0)
	    return -1;
	int ret = sendto(sock, sendBuf, len, 0, to, addrlen);
	return (ret > 0) ? ret : -2;

}

int zn_udpRecv(int sock, void *recvBuf, int len, struct sockaddr *from,
        int *addrlen) {
	if (sock <= 0 || recvBuf == NULL || len <= 0 || from == NULL
	        || addrlen == 0) return -1;
	int ret = recvfrom(sock, recvBuf, len, 0, from, (socklen_t *)addrlen);

	return (ret > 0) ? ret : -2;
}

int zn_udpDestory(const int sock) {
	if (sock <= 0) return -1;
	return (close(sock) == 0) ? 0 : -2;

}
