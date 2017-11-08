/** 
* @file zn_crypt_aes256cbc.h
* @brief 基于 linux  aes 256 cbc   padding5 加解密
* @author zhunian0322@163.com
* @date 16:55 2017/11/08
* @version 1
*/

#ifndef ZN_CRYPT_AES256CBC_H_
#define ZN_CRYPT_AES256CBC_H_

#include <stdint.h>

/** 
 *  @breif	初始化加解密  
 *  @param[in] key  加解密所用密钥
 */
void aes256cbc_init(uint8_t *key);

/** 
 *  @breif	加密  
 *  @param[in] plaintext  			需加密的明文
 *  @param[in] ciphertextBuf   		密文缓存区
 *  @param[out] ciphertextBufLen 	缓存区长度
 *  @return 成功返回密文base64的值，失败返回 NULL
 */
char *aes256cbc_encrypt(const char *plaintext, char ciphertextBuf[], int ciphertextBufLen);

/** 
 *  @breif	解密 
 *  @param[in] ciphertext  			需解密的密文base64的值
 *  @param[in] plaintextBuf   		明文缓存区
 *  @param[out] plaintextBufLen 	缓存区长度
 *  @return 成功返回明文的值，失败返回 NULL
 */
char *aes256cbc_decrypt(const char *ciphertext, char plaintextBuf[], int plaintextBufLen);

#endif /* ZN_CRYPT_AES256CBC_H_ */