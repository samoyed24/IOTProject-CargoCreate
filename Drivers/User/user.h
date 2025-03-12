/*
 * user.h
 *
 *  Created on: Mar 10, 2025
 *      Author: 16018
 */

#ifndef USER_USER_H_
#define USER_USER_H_

#include <stdint.h>

typedef struct {
	char* username;
} User_TypeDef;

uint8_t USER_SetUser(char* username);
User_TypeDef* USER_GetUser();

#endif /* USER_USER_H_ */
