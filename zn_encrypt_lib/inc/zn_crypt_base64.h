/** 
* @file zn_crypt_base64.h
* @brief 基于 linux  base64 API
* @author zhunian0322@163.com
* @date 16:55 2017/11/08
* @version 1
*/

#ifndef ZN_CRYPT_BASE64_H_
#define ZN_CRYPT_BASE64_H_

/** 
 *  @breif	对字符串进行base64编码 
 *  @param[in] in_str  	需要编码的字符串
 *  @param[in] in_len   字符串长度
 *  @param[out] out_str	编码后的值(缓冲区)
 *  @return 返回base64编码长度
 */
int base64_encode(char *in_str, int in_len , char *out_str);

/** 
 *  @breif	对字符串进行base64解码 
 *  @param[in] in_str  	需要解码的字符串
 *  @param[in] in_len   字符串长度
 *  @param[out] out_str	解码后的值(缓冲区)
 *  @return 返回base64解码长度
 */
int base64_decode(char *in_str, int in_len, char *out_str);

#endif /* ZN_CRYPT_BASE64_H_ */