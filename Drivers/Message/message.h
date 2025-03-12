/*
 * message.h
 *
 *  Created on: Oct 22, 2024
 *      Author: 16018
 */

#ifndef MESSAGE_MESSAGE_H_
#define MESSAGE_MESSAGE_H_

#include <string.h>
#include "Wifi/wifi.h"
#include "cJSON/cJSON.h"

extern char msg_buffer[4000];
extern uint32_t updateTime;
extern volatile short msg_ptr;
extern uint8_t msg_is_checked;

void MESSAGE_CHECK_AND_CLEAR();
cJSON* MESSAGE_MERGER(char** _requestID);

#endif /* MESSAGE_MESSAGE_H_ */
