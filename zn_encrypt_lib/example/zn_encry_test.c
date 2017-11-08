
#include <stdio.h>
#include <string.h>

#include "../inc/zn_crypt_aes256cbc.h"
#include "../inc/zn_crypt_base64.h"
#include "../inc/zn_crypt_MD5.h"



int main(){
	char *testStr = "mac=usO8uB6glgOIL8jkFr+UXg==&rtime=1502813082&uuid=010107E1061B00000033&key=YVMvKL0obbRlPjde1g1FzrsQSSiTU3id";
	char *testFileName = "OpenSSL.rar";
	
	// md5 测试

	/**
		在shell 中调用 md5sum 命令即可测试结果
		字符串的 md5 校验命令如下
		echo -n "string" | md5sum
		文件的md5 校验如下
		md5sum filename

	*/
	char md5Res[33];
	zn_crypt_md5_forStr(testStr,(int)strlen(testStr),md5Res,33);
	printf("str md5 value %s\n",md5Res);

	zn_crypt_md5_forFile(testFileName,md5Res,33);
	printf("file md5 value %s\n",md5Res);


	// base64 测试
	/**
		针对目前编写的这个base64库，计算结果，与Linux base64 指令结果是有所差异的，时间因素没有细究。不过与公司服务器的base64是可以验证通过
		http://192.168.1.205:8080/aes256/index.html
	*/
	char *str = "helloworldhelloworld";
	char base64enRes[1024];
	char base64deRes[1024];
	int c = base64_encode(str,strlen(str),base64enRes);
	printf("base64 encode len %d values %s\n",c,base64enRes);

	c = base64_decode(base64enRes,strlen(base64enRes),base64deRes);
	printf("base64 decode len %d values %s\n",c,base64deRes);
	

	// aes 测试

	char *aesTestStr = "helloworldhelloworldhelloworldhelloworld";
	uint8_t key[32] = "idU3iTSSsQzr1F1gdePjRlbb0oKLMvYV";
	char ciphertext[1024];
	char plaintext[1024];
	aes256cbc_init(key);
	aes256cbc_encrypt(aesTestStr,ciphertext,1024);

	printf("encrypt string %s\n",ciphertext);

	aes256cbc_decrypt(ciphertext,plaintext,1024);

	printf("decrypt string %s\n",plaintext);	
	
}
