/** 
* @file zn_crypt_MD5.h
* @brief 基于 linux  MD5 API
* @author zhunian0322@163.com
* @date 16:55 2017/11/08
* @version 1
*/

#ifndef ZN_CRYPT_MD5_H_
#define ZN_CRYPT_MD5_H_

/** 
 *  @breif	对字符串进行 md5 校验 
 *  @param[in] str  	需要校验的字符串
 *  @param[in] strLen   字符串长度
 *  @param[out] mdVal	md5 校验值存放区
 *  @param[in] mdLen    存放缓存区最大长度
 *  @return 返回 mdVal 地址
 */
char * zn_crypt_md5_forStr(char *str, int strLen , char mdVal[], int mdLen);

/** 
 *  @breif	对文件进行 md5 校验 
 *  @param[in] filename 需要校验的文件名
 *  @param[out] mdVal	md5 校验值存放区
 *  @param[in] mdLen    存放缓存区最大长度
 *  @return 返回 mdVal 地址
 */
char * zn_crypt_md5_forFile(char *filename,char mdVal[], int mdLen);

#endif /* ZN_CRYPT_MD5_H_ */