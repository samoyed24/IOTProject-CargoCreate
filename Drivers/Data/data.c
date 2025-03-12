/*
 * data.c
 *
 *  Created on: Mar 10, 2025
 *      Author: 16018
 */

#include "data.h"
#include "User/user.h"

char* DATA_Get_CargoCreate(char card_uid[], double weight) {
	cJSON* json = cJSON_CreateObject();
	cJSON* content = cJSON_CreateObject();
	cJSON_AddStringToObject(content, "requestType", "CargoCreate");
	cJSON_AddStringToObject(content, "card_uid", card_uid);
	cJSON_AddNumberToObject(content, "weight", weight);
	User_TypeDef* user = USER_GetUser();
	cJSON_AddStringToObject(content, "created_by", user->username);
	cJSON_AddItemToObject(json, "content", content);
	char* json_string = cJSON_PrintUnformatted(json);
	cJSON_Delete(json);
	return json_string;
}
