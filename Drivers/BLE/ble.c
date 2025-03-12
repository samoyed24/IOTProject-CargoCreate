/*
 * ble.c
 *
 *  Created on: Sep 29, 2024
 *      Author: 16018
 */

#include "ble.h"
#include "cJSON/cJSON.h"
#include "stdint.h"
#include "Wifi/wifi.h"
#include "stdlib.h"
#include "User/user.h"


extern WIFI_Struct deviceWifiStruct;
extern MQTTUser_Struct mqttuser;
extern MQTTConn_Struct mqttconn;
extern char* topic_request_bind;
extern char* topic_receive_bind;
extern UART_HandleTypeDef huart2;

uint8_t BLE_buffer[1000];
uint32_t BLE_buffer_ptr = 0;
uint8_t* json_data;
cJSON* lastJson;

BLE_Status status = BLE_WAITING_FOR_CONNECTION;


uint8_t BLE_RECV_INIT() {
	if (HAL_UART_Receive_IT(&huart2, (uint8_t*)BLE_buffer, 1) != HAL_OK) return 0;
	BLE_SET_STATUS(status);
	return 1;
}

uint8_t BLE_INTERFACE_COMMAND() {
	cJSON* root = cJSON_Parse(json_data);
	free(json_data);
	if (root == NULL) {
		status = BLE_FATAL_ERROR;
		BLE_SET_STATUS();
		cJSON_Delete(root);
		return 0;
	}
	cJSON_Delete(lastJson);
	deviceWifiStruct.ssid = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(root, "wifi_ssid"));
	deviceWifiStruct.password = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(root, "wifi_password"));
	USER_SetUser(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(root, "user")));
	lastJson = root;
	return 1;
}

uint8_t BLE_SET_STATUS() {
    uint8_t status_to_send = (uint8_t)status;
    if (HAL_UART_Transmit(&huart2, &status_to_send, sizeof(status_to_send), 50) != HAL_OK) {
        return 0;  // 发送失败
    }
    return 1;  // 发送成功
}

uint8_t BLE_ChangeStatus(BLE_Status _status) {
	status = _status;
}

BLE_Status BLE_GetStatus() {
	return status;
}

void BLE_CALLBACK() {
	if (BLE_buffer[BLE_buffer_ptr] == '$') {
		BLE_buffer[BLE_buffer_ptr] = "\0";
		json_data = (uint8_t*)malloc(strlen(BLE_buffer) + 1);
		strcpy(json_data, BLE_buffer);
		BLE_INTERFACE_COMMAND();
		memset(BLE_buffer, 0, sizeof(BLE_buffer));
		status = BLE_TRY_CONNECTING;
		BLE_SET_STATUS();
		BLE_buffer_ptr = 0;
	} else if (BLE_buffer[BLE_buffer_ptr] == '\n'){
		if (strcmp(BLE_buffer, "+CONNECTED\r\n") == 0) {
			BLE_SET_STATUS();
		}
		memset(BLE_buffer, 0, sizeof(BLE_buffer));
		BLE_buffer_ptr = 0;
	} else
		BLE_buffer_ptr++;
	HAL_UART_Receive_IT(&huart2, (uint8_t*)BLE_buffer + BLE_buffer_ptr, 1);
}
