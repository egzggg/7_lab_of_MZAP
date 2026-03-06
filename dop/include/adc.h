#pragma once

#include <settings.h>

void InitADC(void);
void SendADC(void);

extern volatile uint16_t display_val;