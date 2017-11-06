/** 
 * @file zn_base_time.c
 * @brief 基于 linux API 封装系统相关接口
 * @author zhunian0322@163.com
 * @date 09:56 2017/11/06
 * @version 1
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../inc/zn_base_system.h"

typedef enum {
	EIT_MAC_UPPER,
	EIT_MAC_LOWER,
	EIT_IP_STR,
	EIT_IP_INT,
	EIT_NETMASK_STR,
	EIT_NETMASK_INT
} ETH_INFO_TYPES;

static int zn_base_getSystemEthInfo(const char *name, char buf[], int len,
		ETH_INFO_TYPES eit) {

	if (name == NULL)
		return -1;

	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return -2;

	int res = 0;
	struct ifreq ifr;
	memset(buf, 0, len);
	memset(&ifr, 0, sizeof(struct ifreq));
	strncpy(ifr.ifr_name, name, IFNAMSIZ);

	switch (eit) {
	case EIT_MAC_UPPER:
	case EIT_MAC_LOWER:
		if (buf == NULL)
			goto buf_err_exit;

		if (ioctl(fd, SIOCGIFHWADDR, &ifr))
			goto ioctl_err_exit;

		if (eit == EIT_MAC_UPPER)
			snprintf(buf, len, "%02X%02X%02X%02X%02X%02X",
					(unsigned char) ifr.ifr_hwaddr.sa_data[0],
					(unsigned char) ifr.ifr_hwaddr.sa_data[1],
					(unsigned char) ifr.ifr_hwaddr.sa_data[2],
					(unsigned char) ifr.ifr_hwaddr.sa_data[3],
					(unsigned char) ifr.ifr_hwaddr.sa_data[4],
					(unsigned char) ifr.ifr_hwaddr.sa_data[5]);
		else
			snprintf(buf, len, "%02x%02x%02x%02x%02x%02x",
					(unsigned char) ifr.ifr_hwaddr.sa_data[0],
					(unsigned char) ifr.ifr_hwaddr.sa_data[1],
					(unsigned char) ifr.ifr_hwaddr.sa_data[2],
					(unsigned char) ifr.ifr_hwaddr.sa_data[3],
					(unsigned char) ifr.ifr_hwaddr.sa_data[4],
					(unsigned char) ifr.ifr_hwaddr.sa_data[5]);

		goto graceful_exit;
		break;

	case EIT_IP_STR:
	case EIT_IP_INT:
		if (ioctl(fd, SIOCGIFADDR, &ifr))
			goto ioctl_err_exit;

		if (eit == EIT_IP_INT)
			res = ((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr.s_addr;
		else {
			if (buf == NULL)
				goto buf_err_exit;
			snprintf(buf, len, "%s",
					inet_ntoa(
							((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr));
		}
	goto graceful_exit;

	break;

	case EIT_NETMASK_STR:
	case EIT_NETMASK_INT:
		if (ioctl(fd, SIOCGIFNETMASK, &ifr))
			goto ioctl_err_exit;

		if (eit == EIT_NETMASK_INT)
			res = ((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr.s_addr;
		else {
			if (buf == NULL)
				goto buf_err_exit;
			snprintf(buf, len, "%s",
					inet_ntoa(
							((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr));

		}
		goto graceful_exit;

		break;
	}

	buf_err_exit: close(fd);
	return -4;

	ioctl_err_exit: close(fd);
	return -3;

	graceful_exit: close(fd);
	return res;

}

ZN_ETH_NAMES * zn_base_getSystemEthAllNames(ZN_ETH_NAMES *zen) {
	if (zen == NULL)
		return NULL;

	struct ifconf ifc;
	struct ifreq buf[24];

	memset(zen, 0, sizeof(ZN_ETH_NAMES));
	memset(&buf, 0, sizeof(struct ifreq) * 24);

	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return NULL;

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t) buf;

	if (ioctl(fd, SIOCGIFCONF, &ifc)) {
		close(fd);
		return NULL;
	}

	zen->num = ifc.ifc_len / sizeof(struct ifreq);

	for (int i = 0; i < zen->num; ++i)
		strcpy(zen->names[i], buf[i].ifr_name);

	return zen;

}

char *zn_base_getSystemEthMac(const char *name, char buf[], int len, int flag) {
	ETH_INFO_TYPES
	EIT = flag == 0 ? EIT_MAC_LOWER : EIT_MAC_UPPER;
	if (zn_base_getSystemEthInfo(name, buf, len, EIT) < 0)
		return NULL;

	return buf;

}

char *zn_base_getSystemEthIpAddrForStr(const char *name, char buf[], int len) {
	if (zn_base_getSystemEthInfo(name, buf, len, EIT_IP_STR) < 0)
		return NULL;

	return buf;
}

char *zn_base_getSystemEthNetMaskForStr(const char *name, char buf[], int len) {
	if (zn_base_getSystemEthInfo(name, buf, len, EIT_NETMASK_STR) < 0)
		return NULL;

	return buf;
}

int zn_base_getSystemEthIpAddrForInt(const char *name) {
	return zn_base_getSystemEthInfo(name, NULL, 0, EIT_IP_INT);

}

int zn_base_getSystemEthNetMaskForInt(const char *name) {
	return zn_base_getSystemEthInfo(name, NULL, 0, EIT_NETMASK_INT);

}

void zn_base_showSystemEthAll(ZN_ETH_NAMES *zen) {
	printf("Total Number is %d\n", zen->num);
	for (int i = 0; i < zen->num; ++i)
		printf("%s\t", zen->names[i]);

	printf("\n");
}

