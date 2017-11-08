/** 
* @file zn_crypt_MD5.c
* @brief 基于 linux  MD5 API
* @author zhunian0322@163.com
* @date 16:55 2017/11/08
* @version 1
*/



#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <unistd.h>

#include "zn_crypt_MD5.h"



#define BUF_MAX		4096

char * zn_crypt_md5_forStr(char *str, int strLen , char mdVal[], int mdValLen){
	unsigned char md[16];

	memset(mdVal,0,mdValLen);
	
	MD5((const unsigned char *)str, strLen, md);
	char tmp[3];
	for(int i = 0; i < 16; ++i){
		snprintf(tmp, 3, "%02x",md[i]);
		strcat(mdVal, tmp);
	}

	return mdVal;
}

char * zn_crypt_md5_forFile(char *filename,char mdVal[], int mdValLen){
	if(filename == NULL)
		return NULL;

	if(access(filename,F_OK))
		return NULL;

	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		return NULL;

	char buffer[BUF_MAX] = {'\0'};
	MD5_CTX ctx;
	unsigned char md[16];
	int len = 0;
	
	MD5_Init(&ctx);

	while((len = fread(buffer,1,BUF_MAX,fp)) > 0){
		MD5_Update(&ctx, buffer, len);
		memset(buffer,0,BUF_MAX);
	}

	MD5_Final(md, &ctx);

	memset(mdVal,0,mdValLen);
	char tmp[3];
	for(int i = 0; i < 16; ++i){
		snprintf(tmp, 3, "%02x",md[i]);
		strcat(mdVal, tmp);
	}

	return mdVal;
}


