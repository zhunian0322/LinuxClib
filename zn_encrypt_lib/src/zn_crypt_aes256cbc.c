/** 
* @file zn_crypt_aes256cbc.c
* @brief 基于 linux  aes 256 cbc   padding5 加解密
* @author zhunian0322@163.com
* @date 16:55 2017/11/08
* @version 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <openssl/aes.h>


#include "zn_crypt_aes256cbc.h"
#include "zn_crypt_base64.h"



#define IVEC 0x00

typedef struct{
	AES_KEY en_aesKey;
	AES_KEY de_aesKey;
}ZN_AES_KEY;


static  ZN_AES_KEY  zn_aes_key;

static uint8_t end_mark;

static char *toString(char *str, int len){
	for(int i = 0; i < len; ++i){
		if(str[i] == end_mark)
		{
			str[i] = '\0';
			break;
		}
	}

	return str;
}


static void safe_free(void *pst){
	if(pst){
		free(pst);
		pst = NULL;
	}
}




void aes256cbc_init(uint8_t *key){
	memset(&zn_aes_key.en_aesKey,0x00,sizeof(zn_aes_key.en_aesKey));
	memset(&zn_aes_key.de_aesKey,0x00,sizeof(zn_aes_key.de_aesKey));
	
	AES_set_encrypt_key(key, 256, &zn_aes_key.en_aesKey);
	AES_set_decrypt_key(key, 256, &zn_aes_key.de_aesKey);
}

char *aes256cbc_encrypt(const char *plaintext, char ciphertextBuf[], int ciphertextBufLen){
	uint8_t iv[16];
	int dataLen = strlen(plaintext);
	memset(ciphertextBuf,0,ciphertextBufLen);

	int setDataLen = ((dataLen / AES_BLOCK_SIZE ) + 1) * AES_BLOCK_SIZE;
	uint8_t *plaintextData = ( uint8_t *)calloc(setDataLen,sizeof( uint8_t));
	uint8_t *ciphertextData = ( uint8_t *)calloc(setDataLen,sizeof( uint8_t));

	if(plaintextData == NULL || ciphertextData == NULL)
		return NULL;

	uint8_t padding = 0x10 - (dataLen % AES_BLOCK_SIZE);
	end_mark = padding;
	memset(plaintextData, padding, setDataLen);
	memcpy(plaintextData, plaintext, dataLen);
	memset(iv, IVEC, 16);

	AES_cbc_encrypt(plaintextData, ciphertextData , setDataLen, &zn_aes_key.en_aesKey, iv, AES_ENCRYPT);

	//printf("ciphertext len %d\n",strlen(ciphertextData));
	char basestr[1024] = {'\0'};

	int baseLen = base64_encode((char *)ciphertextData, setDataLen, basestr);

	if(ciphertextBufLen > baseLen)
		memcpy(ciphertextBuf, basestr, baseLen);

	safe_free(plaintextData);
	safe_free(ciphertextData);

	return ciphertextBuf;
		
}

char *aes256cbc_decrypt(const char *ciphertext, char plaintextBuf[], int plaintextBufLen){
	uint8_t iv[16];
	memset(iv,IVEC,16);

	char outBuf[1024] = {'\0'};
	base64_decode((char *)ciphertext, strlen(ciphertext), outBuf);

	memset(plaintextBuf,0,plaintextBufLen);
	
	printf("ciphertext len %d\n",strlen(outBuf));
	AES_cbc_encrypt((const unsigned char *)outBuf, (unsigned char *)plaintextBuf, plaintextBufLen, &zn_aes_key.de_aesKey, iv, AES_DECRYPT);

	return toString(plaintextBuf,strlen(plaintextBuf));
}

