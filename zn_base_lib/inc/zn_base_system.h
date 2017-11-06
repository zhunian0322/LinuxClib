/** 
* @file zn_base_time.h
* @brief 基于 linux API 封装系统相关接口
* @author zhunian0322@163.com
* @date 09:56 2017/11/06
* @version 1
*/

#ifndef ZN_BASE_SYSTEM_H_
#define ZN_BASE_SYSTEM_H_

/** 网卡名信息      */
typedef struct {
	int num;				/**< 网卡数量 */
	char names[24][64];		/**< 网卡接口名字 */
}ZN_ETH_NAMES;

/** 
 *  @breif	获取当前系统所有网卡名称。
 *  @param[out] zen  ZN_ETH_NAMES 结构体，存放获取的信息  
 *  @return 成功信息结构体指针，失败返回 NULL
 *  @warning  该函数只获取可用网卡(已连接网卡)   
 */
ZN_ETH_NAMES * zn_base_getSystemEthAllNames(ZN_ETH_NAMES *zen);


/** 
 *  @breif	获取当前系统指定网卡 MAC 地址。
 *  @param[in] name  网卡接口名
 *  @param[out] buf  存放结果缓存区
 *  @param[in] len   缓存区长度
 *  @param[in] flag  标识位，为0时mac字符为小写，非0 为大写
 *  @return 成功信息结构体指针，失败返回 NULL   
 */
char *zn_base_getSystemEthMac(const char *name,char buf[],int len, int flag);

/** 
 *  @breif	获取当前系统指定网卡IP地址，以字符串形式。
 *  @param[in] name  网卡接口名
 *  @param[out] buf  存放结果缓存区
 *  @param[in] len   缓存区长度
 *  @return 成功信息结构体指针，失败返回 NULL   
 */
char *zn_base_getSystemEthIpAddrForStr(const char *name, char buf[],int len);

/** 
 *  @breif	获取当前系统指定网卡子网掩码地址，以字符串形式。
 *  @param[in] name  网卡接口名
 *  @param[out] buf  存放结果缓存区
 *  @param[in] len   缓存区长度
 *  @return 成功信息结构体指针，失败返回 NULL   
 */
char *zn_base_getSystemEthNetMaskForStr(const char *name,char buf[],int len);

/** 
 *  @breif	获取当前系统指定网卡IP地址，以整数形式。
 *  @param[in] name  网卡接口名
 *  @return 成功返回 ip 对应整数值，失败返回值 < 0   
 */
int zn_base_getSystemEthIpAddrForInt(const char *name);

/** 
 *  @breif	获取当前系统指定网卡子网掩码地址，以整数形式。
 *  @param[in] name  网卡接口名
 *  @return 成功返回子网掩码     对应整数值，失败返回值 < 0  
 */
int zn_base_getSystemEthNetMaskForInt(const char *name);


/** 
 *  @breif	获取当前系统所有网卡名称。
 *  @param[in] zen  ZN_ETH_NAMES 结构体。
 *  @note   测试使用
 */
void zn_base_showSystemEthAll(ZN_ETH_NAMES *zen);

#endif /* ZN_BASE_SYSTEM_H_ */