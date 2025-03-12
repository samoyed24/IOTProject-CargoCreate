#include "string.h"
#include "stdio.h"
//#include "usart.h"
#include "wifi.h"
#include "stdint.h"
#include "Message/message.h"


WIFI_Struct deviceWifiStruct = {
		.password="samoyed24",
		.ssid="DESKTOP-C320M5B 0922"
};

//volatile uint8_t uart_rx_complete;
volatile IT_Status it_status = _NONE;
static char _buffer[650]; volatile uint16_t _buffer_ptr = 0;

extern uint8_t work;
extern uint8_t msg_to_handle;
extern uint32_t updateTime;
uint32_t startTime;
//uint8_t msg_receiving = 0;
MQTTRev_Struct mqttrev;

void WIFI_OPEN_RECEIVE() {
	HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer, 1);
}

uint8_t WIFI_CONNECT(const WIFI_Struct* const wifi) {
	_buffer_ptr = 0; it_status = _NONE;

	char total_str[160];
	sprintf((char*)total_str, "AT+CWJAP=\"%s\",\"%s\"\r\n", wifi->ssid, wifi->password);
	HAL_UART_Transmit(&huart1, (uint8_t*) total_str, strlen(total_str), 50);
//	HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1);
	startTime = HAL_GetTick();
	while (it_status == _NONE || it_status == WIFI_DISCONNECTED) {
		if (HAL_GetTick() - startTime > 10000) return 0;
	}

	if (it_status != _SUCCESS) return 0;
	it_status = _NONE;

	return 1;
}

uint8_t WIFI_MQTT_USERCFG(const MQTTUser_Struct* const mqttuser) {
	_buffer_ptr = 0; it_status = _NONE;
	while (huart1.gState != HAL_UART_STATE_READY);
	if (HAL_UART_Transmit(&huart1, (uint8_t*) "AT+MQTTCLEAN=0\r\n", strlen("AT+MQTTCLEAN=0\r\n"), 50) != HAL_OK)
		return 0;
	while (huart1.gState != HAL_UART_STATE_READY);
//	if (HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1) != HAL_OK)
//		return 0;
	startTime = HAL_GetTick();
	while (it_status == _NONE) {
		if (HAL_GetTick() - startTime > 10000) return 0;
	}
	it_status = _NONE;

	char usercfg_str[255]="";
	sprintf(usercfg_str,
			"AT+MQTTUSERCFG=0,%d,\"%s\",\"%s\",\"%s\",%d,%d,\"%s\"\r\n",
			mqttuser->scheme,
			mqttuser->client_id,
			mqttuser->username,
			mqttuser->password,
			mqttuser->cert_key_ID,
			mqttuser->CA_ID,
			mqttuser->path
	);
//	HAL_Delay(500);
	if (HAL_UART_Transmit(&huart1, (uint8_t*) usercfg_str, strlen(usercfg_str), 50) != HAL_OK)
		return 0;
//	if (HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1) != HAL_OK)
//		return 0;
	while (it_status == _NONE);
	if (it_status == _FAIL) return 0;
	it_status = _NONE;
	return 1;
}

uint8_t WIFI_MQTT_CONN(const MQTTConn_Struct * const mqttconn) {
	_buffer_ptr = 0; it_status = _NONE;


	char mqttconn_str[255];
	sprintf(
			mqttconn_str,
			"AT+MQTTCONN=0,\"%s\",%d,%d\r\n",
			mqttconn->host,
			mqttconn->port,
			mqttconn->reconnect
	);
	if (HAL_UART_Transmit(&huart1, (uint8_t*) mqttconn_str, strlen(mqttconn_str), 50) != HAL_OK)
		return 0;
//	if (HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1) != HAL_OK)
//		return 0;
	startTime = HAL_GetTick();
	while (it_status == _NONE)
		if (HAL_GetTick() - startTime > 6000) return 0;

	if (it_status != _SUCCESS) return 0;
	it_status = _NONE;

	return 1;
}

uint8_t WIFI_MQTT_MESSAGE_PUB(const MQTTPub_Struct* const mqttpub) {
	_buffer_ptr = 0; it_status = _NONE;
	char mqttpub_str[255];
	sprintf(
			mqttpub_str,
			"AT+MQTTPUB=0,\"%s\",\"%s\",%d,%d\r\n",
			mqttpub->topic,
			mqttpub->data,
			mqttpub->qos,
			mqttpub->retain
	);
	if (HAL_UART_Transmit(&huart1, (uint8_t*) mqttpub_str, strlen(mqttpub_str), 50) != HAL_OK)
		return 0;
//	if (HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1) != HAL_OK)
//		return 0;
	while (it_status == _NONE);
	if (it_status != _SUCCESS) return 0;
	it_status = _NONE;
	HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1);
	return 1;
}

uint8_t WIFI_MQTT_TOPIC_SUB(const MQTTSub_Struct* const mqttsub) {
	char mqttsub_str[255] = "";
	sprintf(
			mqttsub_str,
			"AT+MQTTSUB=0,\"%s\",%d\r\n",
			mqttsub->topic,
			mqttsub->qos
	);
	if (HAL_UART_Transmit(&huart1, (uint8_t*) mqttsub_str, strlen(mqttsub_str), 50) != HAL_OK)
		return 0;
//	if (HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer + 0, 1) != HAL_OK)
//		return 0;
	startTime = HAL_GetTick();
	while (it_status == _NONE)
		if (HAL_GetTick() - startTime > 5000) return 0;
	if (it_status != _SUCCESS) return 0;
	it_status = _NONE;

	return 1;
}

uint8_t WIFI_MQTT_PUBRAW(MQTTPubRaw_Struct* pubraw) {
	_buffer_ptr = 0; it_status = _NONE;
	char pubraw_buffer[256];
	sprintf(
			pubraw_buffer,
			"AT+MQTTPUBRAW=0,\"%s\",%d,%d,%d\r\n",
			pubraw->topic,
			pubraw->length,
			pubraw->qos,
			pubraw->retain
	);
	if (HAL_UART_Transmit(&huart1, (uint8_t*) pubraw_buffer, strlen(pubraw_buffer), 50) != HAL_OK)
		return 0;
	startTime = HAL_GetTick();
	while (it_status == _NONE)
		if (HAL_GetTick() - startTime > 5000) return 0;
	if (it_status != _SUCCESS) return 0;
	it_status = _NONE;

//	for (int i = 0; i < pubraw->length; i++) {
//		if (HAL_UART_Transmit(&huart1, (uint8_t*) pubraw->msg + i, 1, 50) != HAL_OK)
//			return 0;
//	}
	if (HAL_UART_Transmit(&huart1, (uint8_t*) pubraw->msg, pubraw->length, 50) != HAL_OK)
		return 0;
	startTime = HAL_GetTick();
	while (it_status == _NONE)
		if (HAL_GetTick() - startTime > 5000) return 0;
	if (it_status != PUBRAW_OK) return 0;
	it_status = _NONE;
	return 1;
}

char* WIFI_msg_buffer_GETTER() {
	return msg_buffer;
}

//void WIFI_RECEIVE_MSG() {
//	memset(_buffer, 0, 127); _buffer_ptr = 0; it_status = _NONE;
//	HAL_UART_Receive_IT(&huart1, (uint8_t*)_buffer, 1);
//}

// 这里用来停止信息接收中断，并非AT test，因为没有中断开启函数
//uint8_t WIFI_AT_CHECK() {
//	memset(_buffer, 0, 127); _buffer_ptr = 0; it_status = _NONE;
//	if (HAL_UART_Transmit(&huart1, (uint8_t*) "AT\r\n", strlen("AT\r\n"), 50) != HAL_OK)
//		return 0;
//	while (it_status == _NONE);
//	if (it_status != _SUCCESS) return 0;
//	it_status = _NONE;
//	return 1;
//}




uint8_t WIFI_DEVICE_WIFI_CONNECT() {
	return WIFI_CONNECT(&deviceWifiStruct);
}


// 当WIFI模块可能死机，执行RST重置WIFI模块
uint8_t WIFI_RST() {
	HAL_GPIO_WritePin (WIFI_RST_GPIO ,WIFI_RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin (WIFI_RST_GPIO ,WIFI_RST_PIN, GPIO_PIN_SET);
	return 1;
}

uint8_t WIFI_INIT() {
	uint8_t retry = 0;
	uint8_t connected = 0;
	while (!connected) {
		if (retry == 3) return 0;
		connected = WIFI_DEVICE_WIFI_CONNECT();
		if (!connected) {
			WIFI_RST();
			HAL_Delay(1000);
			retry++;
		}
	}
	return connected;
}

void WIFI_CALLBACK() {
//	if (strncmp(_buffer, "+MQTTSUBRECV:", strlen("+MQTTSUBRECV:")) == 0) {
	if (strstr(_buffer, "MQTTSUBRECV:") != NULL) {
		updateTime = HAL_GetTick();
		if (msg_ptr == 4000) msg_ptr = -1;
		if (msg_buffer[msg_ptr] != '\n') {
			msg_ptr++;
			HAL_UART_Receive_IT(&huart1, (uint8_t*) msg_buffer + msg_ptr, 1);
		}
		else {
			msg_is_checked = 0;
			_buffer_ptr = 0;
			msg_buffer[msg_ptr] = '^';
			msg_buffer[msg_ptr+1] = '\0';
			memset(_buffer, 0, 15);
			HAL_UART_Receive_IT(&huart1, (uint8_t*) _buffer + _buffer_ptr, 1);
		}
	} else if (_buffer[_buffer_ptr] == '\n') {
		if (strncmp(_buffer, "OK\r\n", strlen("OK\r\n")) == 0) { // 模块返回OK
			it_status = _SUCCESS;
		} else if (strncmp(_buffer, "ERROR\r\n", strlen("ERROR\r\n")) == 0) {
			it_status = _FAIL;
		} else if ((strncmp(_buffer, "WIFI DISCONNECT\r\n", strlen("WIFI DISCONNECT\r\n")) == 0)) {
			it_status = WIFI_DISCONNECTED;
			work = 0;
		} else if (strncmp(_buffer, ">+MQTTPUB:OK\r\n", strlen(">+MQTTPUB:OK\r\n")) == 0 ||
				strncmp(_buffer, "+MQTTPUB:OK\r\n", strlen("+MQTTPUB:OK\r\n")) == 0) {
			it_status = PUBRAW_OK;
		} else if (strncmp(_buffer, "+MQTTPUB:FAIL\r\n", strlen("+MQTTPUB:FAIL\r\n")) == 0) {
			it_status = PUBRAW_FAIL;
		}
		_buffer[_buffer_ptr+1] = '\0';
//		if (_buffer[1] == '+' && _buffer[2] == 'M' && _buffer[5] == 'S') {
//			printf(1);
//		}
		_buffer_ptr = 0;
		HAL_UART_Receive_IT(&huart1, (uint8_t*) _buffer + _buffer_ptr, 1);
	} else {
		_buffer_ptr++;
		HAL_UART_Receive_IT(&huart1, (uint8_t*) _buffer + _buffer_ptr, 1);
	}
}

