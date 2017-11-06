
#include <stdio.h>

#include "../inc/zn_base_system.h"


int main(){
	ZN_ETH_NAMES zen;

	zn_base_getSystemEthAllNames(&zen);

	zn_base_showSystemEthAll(&zen);



	char buf[1024];
	
	zn_base_getSystemEthMac("eth0",buf,1024,0);
	printf("Mac Address %s\n",buf);
	zn_base_getSystemEthMac("eth0",buf,1024,1);
	printf("Mac Address %s\n",buf);

	zn_base_getSystemEthIpAddrForStr("eth0",buf,1024);
	int res = zn_base_getSystemEthIpAddrForInt("eth0");
	printf("IP Address %d %s\n",res,buf);

	zn_base_getSystemEthNetMaskForStr("eth0",buf,1024);
	res = zn_base_getSystemEthNetMaskForInt("eth0");
	
	printf("NetMask Address %d %s\n",res,buf);
		
}
