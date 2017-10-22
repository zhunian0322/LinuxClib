/** 
* @file zn_udp.h
* @brief 基于 linux API 封装 UDP 接口
* @author zhunian0322@163.com
* @date 17:44 2017/10/21
* @version 1
*/


#ifndef ZN_UDP_H_
#define ZN_UDP_H_

#include <netinet/in.h>

/** 
 *  @breif	初始化一个 udp 服务端  
 *  @param[in] host  需监听的ip  
 *  @param[in] port  需监听的端口  
 *  @retval    < 0   初始化后的套接字文件描述符 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  socket 创建失败
 *  @retval    = -3  socket 绑定失败
 */
int zn_udpServer_init(const char *host, const int port);

/** 
 *  @breif	初始化一个 udp 客户端  
 *  @param[in] sHost  服务器地址，支持 ip 和 域名
 *  @param[in] sPort  服务器端口
 *  @param[out] serverAddr 用于填充服务器通信地址
 *  @retval    < 0   初始化后的套接字文件描述符 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  socket 创建失败
 */
int zn_udpClient_init(const char *sHost, const int sPort,
        struct sockaddr_in *serverAddr);
		
/** 
 *  @breif	初始化一个 udp 客户端 (广播) 
 *  @param[in] bHost  广播地址
 *  @param[in] bPort  广播端口
 *  @param[out] broadcastAddr 用于填充广播通信地址
 *  @retval    < 0   初始化后的套接字文件描述符 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  socket 创建失败
 *  @retval    = -3  设置socket属性为广播失败
 */		
int zn_udpBroadcast_init(const char *bHost, const int bPort,
        struct sockaddr_in *broadcastAddr);

/** 
 *  @breif	发送消息
 *  @param[in] sock  socket文件描述符
 *  @param[in] sendBuf  发送消息
 *  @param[in] len  	发送消息长度
 *  @param[in] to		接收方网络地址
 *  @param[in] addrlen	接收方网络地址长度
 *  @retval    < 0   发送消息长度 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  发送失败
 */
int zn_udpSend(int sock, void *sendBuf, int len, const struct sockaddr *to,
        int addrlen);

/** 
 *  @breif	接收消息
 *  @param[in] sock  socket文件描述符
 *  @param[out] recvBuf  接收消息缓冲区
 *  @param[in] len  	接收消息缓冲区最大长度
 *  @param[in] from		发送方网络地址
 *  @param[in] addrlen	发送方网络地址长度地址
 *  @retval    < 0   发送消息长度 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  接收
 */
int zn_udpRecv(int sock, void *recvBuf, int len, struct sockaddr *from,
        int *addrlen);

/** 
 *  @breif	关闭udp资源
 *  @param[in] sock  socket文件描述符
 *  @retval    = 0   成功 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  关闭失败
 */ 
int zn_udpDestory(const int sock);

#endif /* ZN_UDP_H_ */
