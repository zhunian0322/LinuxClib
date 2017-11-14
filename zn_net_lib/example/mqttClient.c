

#include <stdbool.h>
#include <unistd.h>
#include <string.h>



#include "../inc/zn_mqtt.h"

#define SERVER_HOST			"120.77.211.41"
#define MQTT_POST			1883

#define TOPIC_SUB	"dt2014/A09DC10A0244"
#define TOPIC_PUB	"dt2014/app/A09DC10A0244"

static bool mqttConnected = false;

/** 
 *	@breif	MQTT 意外断开链接时回调函数	
 *	@param[in] context 上下文
 *	@param[in] cause 断开原因
 */
void zn_mqtt_ConnectionLostCallBack(void *context, char *cause){
	getMqttConnectOptions()->cleansession = 1;
	mqttConnected = false;
	zn_mqtt_connect();
}

/** 
 *	@breif	MQTT 连接成功时回调函数
 *	@param[in] context 上下文
 *	@param[in] response 调用时返回的数据
 */
void zn_mqtt_ConnectSuccessCallBack(void* context, MQTTAsync_successData* response){
	mqttConnected = true;
	zn_mqtt_subscribe(TOPIC_SUB);
}

/** 
 *	@breif	MQTT 连接失败时回调函数
 *	@param[in] context 上下文
 *	@param[in] response 调用时返回的数据
 */
void zn_mqtt_ConnectFailureCallBack(void* context,  MQTTAsync_failureData* response){
	sleep(1);
	zn_mqtt_connect();
}	

/** 
 *	@breif	MQTT 订阅失败时回调函数
 *	@param[in] context 上下文
 *	@param[in] response 调用时返回的数据
 */
void zn_mqtt_SubscribeFailureCallBack(void* context,  MQTTAsync_failureData* response){
	if(!mqttConnected)
		zn_mqtt_connect();
}

/** 
 *	@breif	MQTT 推送失败时回调函数
 *	@param[in] context 上下文
 *	@param[in] response 调用时返回的数据
 */
void zn_mqtt_PublishFailureCallBack(void* context,  MQTTAsync_failureData* response){
	if(!mqttConnected)
		zn_mqtt_connect();
}

/** 
 *	@breif	MQTT 接收消息时回调函数  
 *	@param[in] context 上下文
 *	@param[in] topicName 接收到消息对应的主题名
 *	@param[in] topicLen 主题名长度
 *	@param[in] message 消息结构体， 成员payload为消息体，payloadlen为消息体长度
 *	@return 返回1 为已经接收消息，返回 0 表示存在问题
 */
int zn_mqtt_MessageArrivedCallBack(void* context, char* topicName, int topicLen, MQTTAsync_message* message){

	char buf[1024] = {'\0'};

	printf("主题名：%s\n",topicName);

	memcpy(buf,message->payload,message->payloadlen);
	printf("消息: %s\n",buf);
	printf("消息长度: %d\n",message->payloadlen);

	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topicName);

	return 1;
}


static char *getMqttClinetId(const char* macAddress){
	char *clientIdPrefix = "dtdev";  // 设备端
	int clientIdProductId = 2307;  // 网关产品

	static char clientID[1024];
	snprintf(clientID,1024,"%s/%d/%s",clientIdPrefix,clientIdProductId,macAddress);
	return clientID;
}

	


int main(){
	MQTT_CALL_BASKS  mqtt_function_calls;
	mqtt_function_calls.mqtt_connectFailure_callBack = zn_mqtt_ConnectFailureCallBack;
	mqtt_function_calls.mqtt_connectionLost_callBack = zn_mqtt_ConnectionLostCallBack;
	mqtt_function_calls.mqtt_connectSuccess_callBack = zn_mqtt_ConnectSuccessCallBack;
	mqtt_function_calls.mqtt_messageArrived_callBack = zn_mqtt_MessageArrivedCallBack;
	mqtt_function_calls.mqtt_publishFailure_callBack = zn_mqtt_PublishFailureCallBack;
	mqtt_function_calls.mqtt_subscribeFailure_callBack = zn_mqtt_SubscribeFailureCallBack;


	zn_mqtt_init(SERVER_HOST,MQTT_POST,getMqttClinetId("000C2910BAED"),&mqtt_function_calls);

	zn_mqtt_connect();
	int i = 0;
	char send_message[1024];
	while(1){
		memset(send_message,0,1024);
		sleep(5);
		snprintf(send_message,1024,"Hello World! %d",++i);
		zn_mqtt_publish(TOPIC_PUB,send_message,strlen(send_message));
	}
}

