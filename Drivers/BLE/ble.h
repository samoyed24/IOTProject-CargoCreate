/*
 * ble.h
 *
 *  Created on: Sep 29, 2024
 *      Author: 16018
 */

#ifndef BLE_BLE_H_
#define BLE_BLE_H_
#include "stdint.h"



typedef enum {
	BLE_WAITING_FOR_CONNECTION = 0x01,
	BLE_CONNECTED = 0x02,
	BLE_TRY_CONNECTING = 0x03,
	BLE_WORKING = 0x04,
	BLE_CONNECTION_FAILED = 0x05,
	BLE_FATAL_ERROR = 0x06
} BLE_Status;


uint8_t BLE_RECV_INIT();
uint8_t BLE_INTERFACE_COMMAND();
uint8_t BLE_SET_STATUS();
uint8_t BLE_ChangeStatus(BLE_Status _status);
BLE_Status BLE_GetStatus();
void BLE_CALLBACK();

#endif /* BLE_BLE_H_ */
