///*
// * huawei.h
// *
// *  Created on: Oct 13, 2024
// *      Author: 16018
// */
//
#ifndef HUAWEI_HUAWEI_H_
#define HUAWEI_HUAWEI_H_
//
#include "Wifi/wifi.h"
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
#include "cJSON/cJSON.h"


typedef enum {
	SERVICE_UPLOAD,
	COMMAND_FROM_PLATFORM,
	COMMAND_TO_PLATFORM,
	SERVICE_RESP,
	SHADOW_GET_UP,
	SHADOW_GET_DOWN,
	MESSAGE_UP,
	MESSAGE_DOWN,
} HUAWEI_TopicType;

typedef struct {
	char* username;
	char* deviceType;
} DeviceInfo_Struct;

extern char* deviceUser;

uint8_t HUAWEI_INIT();
uint8_t HUAWEI_TEMPHUMID(int16_t temp, int16_t humid, uint8_t event, uint16_t hotFanSpeed, uint16_t coldFanSpeed);
uint8_t HUAWEI_WAKEUP(DeviceInfo_Struct* deviceInfo);
uint8_t HUAWEI_SUBSCRIBE_TOPICS();
uint8_t HUAWEI_SERVICE_RESP(char* requestID);
uint8_t HUAWEI_SEND_MESSAGE(char* data);



#endif /* HUAWEI_HUAWEI_H_ */
