/** 
* @file zn_tcp.h
* @brief 基于 linux API 封装 TCP 接口
* @author zhunian0322@163.com
* @date 17:44 2017/10/21
* @version 1
*/

#ifndef ZN_TCP_H_
#define ZN_TCP_H_

#include <netinet/in.h>

/** 
 *  @breif	初始化一个 tcp 服务端  
 *  @param[in] host  需监听的ip  
 *  @param[in] port  需监听的端口  
 *  @param[in] backlog 监听客户端最大个数
 *  @retval    < 0   初始化后的套接字文件描述符 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  socket 创建失败
 *  @retval    = -3  socket 绑定失败
 *  @retval    = -4  socket 监听失败
 */
int zn_tcpServer_init(const char *host, const int port, const int backlog);

/** 
 *  @breif	初始化一个 tcp 客户端  
 *  @retval    < 0   初始化后的套接字文件描述符 
 *  @retval    = -1  socket 创建失败
 */
int zn_tcpClient_init();

/** 
 *  @breif	连接服务器 
 *  @param[in] sock  socket文件描述符 
 *  @param[in] host  服务器的ip  
 *  @param[in] port  服务器的端口  
 *  @retval    = 0 连接成功 
 *  @retval    = -1  连接失败
 */
int zn_tcpClinet_connet(int sock, const char *host, const int port);

/** 
 *  @breif	接入tcp客户端 
 *  @param[in] listenSock  监听的socket文件描述符 
 *  @param[out] clientAddr 连接的客户端ip   
 *  @retval    > 0 返回一个新的 socket 文件描述符 
 *  @retval    = -1  错误
 */
int zn_tcpServer_accept(int listenSock, struct sockaddr_in *clientAddr);

/** 
 *  @breif	发送消息  
 *  @param[in] sock  接收端socket文件描述符  
 *  @param[in] sendBuf  消息体  
 *  @param[in] len 消息长度
 *  @retval    < 0   成功发送消息长度
 *  @retval    = -1  参数值错误
 */
int zn_tcpSend(int sock, void *sendBuf, int len);

/** 
 *  @breif	接收消息  
 *  @param[in] sock  监听的socket文件描述符  
 *  @param[out] recvBuf  接收消息缓冲区  
 *  @param[in] len 接收消息缓冲区最大长度
 *  @param[in] timeout 接收阻塞超时时间，小于0，阻塞接收
 *  @retval    < 0   成功接收消息长度
 *  @retval    = -1  参数值错误
 *  @retval    = -2  接收错误
 */
int zn_tcpRecv(int sock, void *recvBuf, int len, int timeout);

/** 
 *  @breif	关闭tcp资源
 *  @param[in] sock  socket文件描述符
 *  @retval    = 0   成功 
 *  @retval    = -1  参数值错误
 *  @retval    = -2  关闭失败
 */ 
int zn_tcpDestory(const int sock);

#endif /* ZN_TCP_H_ */
