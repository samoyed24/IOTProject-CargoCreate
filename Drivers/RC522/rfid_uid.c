/*
 * rfid_uid.c
 *
 *  Created on: Sep 27, 2024
 *      Author: 16018
 */
#include "RC522/rc522.h"



uint8_t lastCardUid[4];

uint8_t RFID_GET_UUID(char uid[]) {
	PCD_Reset();
	uint8_t card_type[2];
	uint8_t pSnr[4];
	if (PCD_Request(PICC_REQALL, card_type) == PCD_OK) {
		if (PCD_Anticoll(pSnr) == PCD_OK) {
			uint8_t sameBit = 0;
			for (int i = 0; i < 4; i++) if (pSnr[i] == lastCardUid[i]) sameBit++;
			if (sameBit < 4) {
				BUZZER_BUZZ_TWICE(100, 100);
				for (int i = 0; i < 4; i++) lastCardUid[i] = pSnr[i];
				sprintf(
					uid,
					"%02X%02X%02X%02X",
					pSnr[0], pSnr[1], pSnr[2], pSnr[3]
				);
				return 1;
			}
		}
	}
	return 0;
}
