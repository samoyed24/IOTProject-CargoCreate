#ifndef BUZZER_BUZZER_H
#define BUZZER_BUZZER_H

#include "main.h"

void BUZZER_SHORT(uint32_t buzz_time_ms);
void BUZZER_BUZZ_TWICE(uint32_t buzz_time_ms, uint32_t mid_time_ms);
void BUZZER_Success();
void BUZZER_Fail();

#endif
