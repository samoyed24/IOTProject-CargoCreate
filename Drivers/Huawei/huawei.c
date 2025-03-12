/*
 * huawei.c
 *
 *  Created on: Oct 13, 2024
 *      Author: 16018
 */

#include "huawei.h"

//ControlPanel_Resp_TypeDef panelres;


//参数配置区域

MQTTUser_Struct deviceMqttUsercfg = {
		.CA_ID=0,
		.cert_key_ID=0,
		.client_id="67cd76148e04aa0690bbc845_0003_0_0_2025031213",
		.username="67cd76148e04aa0690bbc845_0003",
		.password="0769a4103d973ecfb63834ea1e8ee141c381bf2e4d324e615e19084b14d90fba",
		.path="",
		.scheme=1
};
MQTTConn_Struct deviceMqttConn = {
		.host="26e659c083.st1.iotda-device.cn-north-4.myhuaweicloud.com",
		.port=1883,
		.reconnect=NEVER_RECONNECT
};
DeviceInfo_Struct deviceInfo = {
		.deviceType="warehouse_cargo_create",
		.username="15241828456"
};

static uint8_t buffer[256];

// 固定函数定义区域

uint8_t HUAWEI_INIT() {
	if (WIFI_MQTT_USERCFG(&deviceMqttUsercfg) == 0)  return 0;
	if (WIFI_MQTT_CONN(&deviceMqttConn) == 0) return 0;
	if (HUAWEI_SUBSCRIBE_TOPICS() == 0) return 0;
	if (HUAWEI_WAKEUP(&deviceInfo) == 0) return 0;
	return 1;
}

//static void serviceCapsulation(cJSON* service, cJSON* root) {
//	if (!root) root = cJSON_Parse("{\"service\":[]}");
//	cJSON* serviceArr = cJSON_GetObjectItemCaseSensitive(root, "service");
//	cJSON_AddItemToArray(serviceArr, service);
//}
//
//static void generateService(cJSON* prop, char* serviceId, cJSON* service) {
//	cJSON* baseService = cJSON_Parse("{\"service_id\": \"%s\", \"properties\": {}}");
//	cJSON_AddItemToObject(baseService, "properties", prop);
//	service = baseService;
//}


char* HUAWEI_TOPIC_GETTER(HUAWEI_TopicType topicType) {
	char* returnTopic;
	if (topicType == SERVICE_UPLOAD) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/properties/report",
				deviceMqttUsercfg.client_id
		);
	} else if (topicType == COMMAND_FROM_PLATFORM) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/commands/#",
				deviceMqttUsercfg.client_id
		);
	} else if (topicType == COMMAND_TO_PLATFORM) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/commands/response/request_id=%s",
				deviceMqttUsercfg.client_id
		);
	} else if (topicType == SERVICE_RESP) {
		return "$oc/devices/%s/sys/properties/set/response/request_id=%s";
	} else if (topicType == SHADOW_GET_UP) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/shadow/get/request_id=1",
				deviceMqttUsercfg.client_id
		);
	} else if (topicType == SHADOW_GET_DOWN) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/shadow/get/response/#",
				deviceMqttUsercfg.username
		);
	} else if (topicType == MESSAGE_UP) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/messages/up",
				deviceMqttUsercfg.username
		);
	} else if (topicType == MESSAGE_DOWN) {
		sprintf(
				buffer,
				"$oc/devices/%s/sys/messages/down",
				deviceMqttUsercfg.username
		);

	}
	returnTopic = (char*)malloc(strlen(buffer) + 1);
	strcpy(returnTopic, buffer);
	return returnTopic;
}


uint8_t HUAWEI_MQTTPUB_JSON(HUAWEI_TopicType topicType, char* json) {
	char* topic = HUAWEI_TOPIC_GETTER(topicType);
	MQTTPubRaw_Struct pubraw = {
			.length=strlen(json),
			.msg=json,
			.qos=2,
			.retain=0,
			.topic=topic
	};
	uint8_t result = WIFI_MQTT_PUBRAW(&pubraw);
	free(topic);
	free(json);
	return result;
}

// 以下为自定义

static char* HUAWEI_SERVICE_ADD_WAKE_UP (DeviceInfo_Struct* deviceInfo) {
	cJSON* prop = cJSON_CreateObject();
	cJSON_AddStringToObject(prop, "username", deviceInfo->username);
	cJSON_AddStringToObject(prop, "deviceType", deviceInfo->deviceType);
	cJSON* service = cJSON_CreateObject();
	cJSON_AddStringToObject(service, "service_id", "DeviceWakeUp");
	cJSON_AddItemToObject(service, "properties", prop);
	cJSON* servicesArray = cJSON_CreateArray();
	cJSON_AddItemToArray(servicesArray, service);
	cJSON* root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "services", servicesArray);
	char* jsonStr = cJSON_PrintUnformatted(root);
	cJSON_Delete(root);
	return jsonStr;
}

uint8_t HUAWEI_WAKEUP(DeviceInfo_Struct* deviceInfo) {
	char* json = HUAWEI_SERVICE_ADD_WAKE_UP(deviceInfo);
	return HUAWEI_MQTTPUB_JSON(SERVICE_UPLOAD, json);
}

uint8_t HUAWEI_SUBSCRIBE_TOPICS() {
	MQTTSub_Struct mqttsub = {
			.qos=1
	};
//	mqttsub.topic = HUAWEI_TOPIC_GETTER(COMMAND_FROM_PLATFORM);
//	if (!WIFI_MQTT_TOPIC_SUB(&mqttsub)) return 0;
//	free(mqttsub.topic);
//	mqttsub.topic = HUAWEI_TOPIC_GETTER(SHADOW_GET_DOWN);
//	if (!WIFI_MQTT_TOPIC_SUB(&mqttsub)) return 0;
//	free(mqttsub.topic);
	mqttsub.topic = HUAWEI_TOPIC_GETTER(MESSAGE_DOWN);
	if (!WIFI_MQTT_TOPIC_SUB(&mqttsub)) return 0;
	free(mqttsub.topic);
	return 1;
}

uint8_t HUAWEI_SERVICE_RESP(char* requestID) {
	MQTTPubRaw_Struct pubraw;
	sprintf(
			buffer,
			HUAWEI_TOPIC_GETTER(SERVICE_RESP),
			deviceMqttUsercfg.username,
			requestID
	);
	char* topic = (char*)malloc(strlen(buffer) + 1);
	strcpy(topic, buffer);
	pubraw.topic = topic;
	pubraw.msg = "{\"result_code\":0,\"result_desc\":\"success\"}";
	pubraw.length = strlen(pubraw.msg);
	pubraw.retain = 0;
	pubraw.qos = 1;
	if (!WIFI_MQTT_PUBRAW(&pubraw)) return 0;
	free(topic);
	return 1;
}

uint8_t HUAWEI_SEND_MESSAGE(char* data) {
	HUAWEI_MQTTPUB_JSON(MESSAGE_UP, data);
	free(data);
	return 1;
}
