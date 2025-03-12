/*
 * message.c
 *
 *  Created on: Oct 22, 2024
 *      Author: 16018
 */

#include "message.h"
#include "cJSON/cJSON.h"

char msg_buffer[4000]; volatile int16_t msg_ptr = -1;
uint32_t updateTime = 0;
uint8_t msg_is_checked = 0;

void MESSAGE_CHECK_AND_CLEAR() {
	if (!msg_is_checked) return;
	if (HAL_GetTick() - updateTime > 500) {
		memset(msg_buffer, 0, 4000);
		msg_ptr = -1;
		updateTime = HAL_GetTick();
	}
}

cJSON* MESSAGE_MERGER(char** _requestID) {
	MQTTRev_Struct mqttrev;
	char str_result[4000];
	char buffer[2000];
	uint16_t buffer_ptr = 0;
	int msg_length = strlen(msg_buffer);
	str_result[0] = '\0';

	for (int i = 0; i < msg_length; i++) {
		buffer[buffer_ptr] = msg_buffer[i];
		if (buffer[buffer_ptr] == '^') {
			sscanf(
				buffer,
				"0,\"%128[^\"]\",%d,%700[^\r$]",
				mqttrev.topic,
				&mqttrev.length,
				mqttrev.data
			);
			strcat(str_result, mqttrev.data);
			buffer_ptr = 0;  // 复位buffer_ptr
		} else {
			buffer_ptr++;
			if (buffer_ptr >= sizeof(buffer)) {  // 防止buffer溢出
				return NULL;
			}
		}
	}
	cJSON* parsed_json = cJSON_Parse(str_result);
	if (!parsed_json) return NULL;
	const char* prefix = "request_id=";
	const char* requestID_Begin = strstr(mqttrev.topic, prefix);
	if (requestID_Begin) {
		char* head = requestID_Begin + strlen(prefix);
		char requestID[40]; uint8_t ptr = 0;
		while (*head != '\0' && *head != '/'){
			requestID[ptr++] = *head;
			head++;
		}
		requestID[ptr] = '\0';

		*_requestID = (char*)malloc(strlen(requestID) + 1);
		strcpy(*_requestID, requestID);
	} else *_requestID = NULL;
	msg_buffer[0] = '\0';
	memset(msg_buffer, 0, 4000);
	msg_ptr = -1;            // 已经解析到了JSON，将缓冲区清空，指针归零。
	return parsed_json;
}

uint8_t MESSAGE_Analyse(cJSON* json) {
	cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
	cJSON* _content = cJSON_Parse(content->valuestring);
	cJSON* status = cJSON_GetObjectItemCaseSensitive(_content, "status");
	uint8_t _status = cJSON_IsTrue(status);
	cJSON_Delete(_content);
	return _status;
}

