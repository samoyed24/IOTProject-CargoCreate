/*
 * user.c
 *
 *  Created on: Mar 10, 2025
 *      Author: 16018
 */

#include "user.h"

User_TypeDef user;

uint8_t USER_SetUser(char* username) {
	user.username = username;
	return 1;
}

User_TypeDef* USER_GetUser() {
	return &user;
}
