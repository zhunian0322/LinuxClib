/** 
* @file zn_crypt_base64.c
* @brief 基于 linux  base64 API
* @author zhunian0322@163.com
* @date 16:55 2017/11/08
* @version 1
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>



int base64_encode(char *in_str, int in_len , char *out_str){
	BIO *b64 , *bio;
	BUF_MEM *bptr = NULL;
	size_t size = 0;

	if (in_str == NULL || out_str == NULL)
		return -1;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	BIO_write(bio, in_str, in_len);
	BIO_flush(bio);

	BIO_get_mem_ptr(bio, &bptr);
	memcpy(out_str, bptr->data, bptr->length);
	out_str[bptr->length - 1 ] = '\0';
	size = bptr->length -1;

	BIO_free_all(bio);
	return size;

}

int base64_decode(char *in_str, int in_len, char *out_str){
	BIO *b64, *bio;
	int size = 0;

	if (in_str == NULL || out_str == NULL)
		return -1;

	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	bio = BIO_new_mem_buf(in_str, in_len);
	bio = BIO_push(b64, bio);

	size = BIO_read(bio, out_str, in_len);
	out_str[size] = '\0';

	BIO_free_all(bio);
	return size;

}

