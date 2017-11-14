/** 
* @file zn_mqtt.h
* @brief 基于第三方mqtt库封装
* @author zhunian0322@163.com
* @date 10:20 2017/11/13
* @version 1
*/


#ifndef ZN_MQTT_H_
#define ZN_MQTT_H_

#include <MQTTAsync.h>
#include <stdbool.h>

/** MQTT 回调函数，需自行实现，参考示例 */
typedef struct {
	void  (* mqtt_connectionLost_callBack)(void *, char *);	/**< 意外断开链接时回调函数 */
	int (*mqtt_messageArrived_callBack)(void *,char *, int , MQTTAsync_message *); /**< 接收消息时回调函数 */
	void (*mqtt_connectSuccess_callBack)(void *, MQTTAsync_successData *); /**< 连接成功时的回调函数 */
	void (*mqtt_connectFailure_callBack)(void *, MQTTAsync_failureData *); /**< 连接失败时的回调函数 */
	void (*mqtt_subscribeFailure_callBack)(void *, MQTTAsync_failureData *); /**< 订阅失败时的回调函数 */
	void (*mqtt_publishFailure_callBack)(void *, MQTTAsync_failureData *); /**< 推送失败时的回调函数 */
}MQTT_CALL_BASKS;


/** 
 *  @breif	初始化	MQTT  
 *  @param[in] sHost  MQTT 服务端地址(ip 或 域名)
 *  @param[in] sPort  MQTT 服务端通信端口
 *  @param[in] clientId  MQTT 连接识别码
 *  @param[in] mcb 存放回调函数结构体
 *  @note 使用该函数必须实现 MQTT_CALL_BASKS 全部回调，并在调用之前将回调指向实现的函数
 */
void zn_mqtt_init(const char *sHost, unsigned short sPort, const char *clientId,MQTT_CALL_BASKS *mcb);


/** 
 *  @breif	连接mqtt服务器
 *  @return 返回值为布尔类型，成功返回 true 失败返回 false
 */
bool zn_mqtt_connect();



/** 
 *  @breif	订阅主题
 *  @return 返回值为布尔类型，成功返回 true 失败返回 false
 */
bool zn_mqtt_subscribe(const char *topic);


/** 
 *  @breif	推送消息
 *  @param[in] topic 推送消息主题
 *  @param[in] message 推送的消息
 *  @param[in] len 推送消息的长度
 *  @return 返回值为布尔类型，成功返回 true 失败返回 false
 */
bool zn_mqtt_publish(const char *topic, const char *message,const int len);


/** 
 *  @breif	获取mqtt连接选项  
 *  @return 返回mqtt连接选项
 */
MQTTAsync_connectOptions *getMqttConnectOptions(); 


#endif /* ZN_MQTT_H_ */

