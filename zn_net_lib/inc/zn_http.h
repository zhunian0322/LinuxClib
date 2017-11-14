/** 
* @file zn_http.h
* @brief 基于libghttp二次封装
* @author zhunian0322@163.com
* @date 14:14 2017/11/14
* @version 1
*/

/** 
 *  @breif	下载文件  
 *  @param[in] uri  		URI 地址	
 *  @param[in] saveFileName   保持的文件
 *  @return   下载的文件字节数
 */
int zn_download(const char *uri, const char *saveFileName);

/** 
 *  @breif	GET 方式访问
 *  @param[in] uri  		URI 地址	
 *  @param[in] params   	URI地址后面的参数，不用时填 NULL
 *	@param[in] timeout		超时时间
 *  @param[out] result		返回数据缓存区
 *	@resultLen[in]	resultLen 传入缓冲区长度
 *  @return   返回数据的字节数
 */
int zn_get(const char *uri, const char *params, int timeout, char *result, int resultLen);

/** 
 *  @breif	POST 方式访问
 *  @param[in] uri  		URI 地址	
 *  @param[in] params   	表单参数(需要post提交的数据)
 *	@param[in] timeout		超时时间
 *  @param[out] result		返回数据缓存区
 *	@resultLen[in]	resultLen 传入缓冲区长度
 *  @return   返回数据的字节数
 */
int zn_post(const char *uri, const char *params, int timeout, char *result, int resultLen);

/** 
 *  @breif	将base64字符串转化成功post可提交的数据 
 *  @param[in] base64Str  base64字符串
 *  @param[in] resBuf     转换后的结果存放缓冲区
 *  @param[in] resBufLen  缓冲区长度
 *  @return  失败返回NULL，成功返回 resbuf首地址
 */
char *zn_base64_post_convert(char *base64Str,char resBuf[], int resBufLen);

