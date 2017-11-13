/** 
* @file zn_mqtt.c
* @brief 基于第三方mqtt库封装
* @author zhunian0322@163.com
* @date 10:20 2017/11/13
* @version 1
*/



#include <stdint.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include <MQTTAsync.h>

#include "../inc/zn_mqtt.h"

static MQTTAsync MQTTHandle;
static MQTTAsync_connectOptions mqttConnectOptions = MQTTAsync_connectOptions_initializer;
static MQTTAsync_responseOptions mqttSubscribeResponseOptions = MQTTAsync_responseOptions_initializer;
static MQTTAsync_responseOptions mqttPublishResponseOptions = MQTTAsync_responseOptions_initializer;




#define _MQTT_QOS		2

static char *getMqttServerAddr(const char *sHost, unsigned short sPort){
	static char res[1024];
	snprintf(res,1024,"tcp://%s:%d",sHost,sPort);
	return res;
}



MQTTAsync_connectOptions *getMqttConnectOptions(){
	return &mqttConnectOptions;
}


bool zn_mqtt_connect(){
	int connectStatus = MQTTAsync_connect(MQTTHandle, &mqttConnectOptions);

	if(connectStatus != MQTTASYNC_SUCCESS){
		fprintf(stderr,"MQTTAsync_connect failed, status = %d\n",connectStatus);
		return false;
	}

	return true;
}




bool zn_mqtt_subscribe(const char *topic){
	if(MQTTAsync_subscribe(MQTTHandle, topic, _MQTT_QOS, &mqttSubscribeResponseOptions)!= MQTTASYNC_SUCCESS)
		return false;

	return true;
	
}


bool zn_mqtt_publish(const char *topic, const char *message,const int len){
	MQTTAsync_message mqttMessage = MQTTAsync_message_initializer;

	mqttMessage.payload = (char *)message;
	mqttMessage.payloadlen = len;
	mqttMessage.qos = _MQTT_QOS;
	mqttMessage.retained = 0;

	if(MQTTAsync_sendMessage(MQTTHandle, topic, &mqttMessage, &mqttPublishResponseOptions) != MQTTASYNC_SUCCESS)
		return false;

	return true;
}



void zn_mqtt_init(const char *sHost, unsigned short sPort, const char *clientId,MQTT_CALL_BASKS *mcb){
	MQTTAsync_create(&MQTTHandle, getMqttServerAddr(sHost, sPort), clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	MQTTAsync_setCallbacks(MQTTHandle,NULL,mcb->mqtt_connectionLost_callBack,mcb->mqtt_messageArrived_callBack,NULL);


	mqttConnectOptions.keepAliveInterval = 30;
	mqttConnectOptions.cleansession = 1;
	mqttConnectOptions.onSuccess = (MQTTAsync_onSuccess *)mcb->mqtt_connectSuccess_callBack;
	mqttConnectOptions.onFailure = (MQTTAsync_onFailure *)mcb->mqtt_connectFailure_callBack;
	mqttConnectOptions.context = MQTTHandle;

	mqttSubscribeResponseOptions.onFailure = (MQTTAsync_onFailure *)mcb->mqtt_subscribeFailure_callBack;
	mqttSubscribeResponseOptions.context = MQTTHandle;

	
	mqttPublishResponseOptions.onFailure = (MQTTAsync_onFailure *)mcb->mqtt_publishFailure_callBack;
	mqttPublishResponseOptions.context = MQTTHandle;
	
}

