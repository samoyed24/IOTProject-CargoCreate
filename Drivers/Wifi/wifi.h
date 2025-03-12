/*
 * wifi.h
 *
 *  Created on: Sep 16, 2024
 *      Author: 16018
 */

#ifndef WIFI_WIFI_H_
#define WIFI_WIFI_H_

#include "stdint.h"
#include "main.h"

#define WIFI_RST_GPIO GPIOA
#define WIFI_RST_PIN GPIO_PIN_11

extern UART_HandleTypeDef huart1;


typedef enum {
	_NONE,
	_SUCCESS,
	_FAIL,
	WIFI_DISCONNECTED,
	MSG_RECEIVED,
	PUBRAW_OK,
	PUBRAW_FAIL
} IT_Status;

typedef struct {
	char* ssid;
	char* password;
} WIFI_Struct;

typedef struct {
	uint8_t scheme;
	char* client_id;
	char* username;
	char* password;
	uint8_t cert_key_ID;
	uint8_t CA_ID;
	char* path;
} MQTTUser_Struct;

typedef enum {
	NEVER_RECONNECT,
	AUTO_RECONNECT,
} RECONNECT;

typedef struct {
	char* host;
	uint16_t port;
	RECONNECT reconnect;
} MQTTConn_Struct;

typedef struct {
	char* topic;
	char* data;
	uint8_t qos;      // 0.最多一次 1.至少一次 2.仅一次
	uint8_t retain;
} MQTTPub_Struct;

typedef struct {
	char* topic;
	uint8_t qos;
} MQTTSub_Struct;

typedef struct {
	char topic[200];
	uint16_t length;
	char data[600];
} MQTTRev_Struct;

typedef struct {
	char* topic;
	uint32_t length;
	uint8_t qos;
	uint8_t retain;
	char* msg;
} MQTTPubRaw_Struct;

uint8_t WIFI_CONNECT(const WIFI_Struct* const wifi);
void WIFI_OPEN_RECEIVE();
uint8_t WIFI_MQTT_USERCFG(const MQTTUser_Struct* const mqttuser);
uint8_t WIFI_MQTT_CONN(const MQTTConn_Struct * const mqttconn);
uint8_t WIFI_MQTT_MESSAGE_PUB(const MQTTPub_Struct* const mqttpub);
uint8_t WIFI_MQTT_TOPIC_SUB(const MQTTSub_Struct* const mqttsub);
uint8_t WIFI_MQTT_PUBRAW(MQTTPubRaw_Struct* pubraw);
uint8_t WIFI_INIT();
uint8_t WIFI_RST();
char* WIFI_MSG_BUFFER_GETTER();
//void WIFI_RECEIVE_MSG();
//uint8_t WIFI_AT_CHECK();
void WIFI_CALLBACK();


// 分割

uint8_t WIFI_DEVICE_WIFI_CONNECT();
//uint8_t WIFI_DEVICE_MQTT_REGISTER();



// 一些可修改的写死在设备中的配置结构体





#endif /* WIFI_WIFI_H_ */
