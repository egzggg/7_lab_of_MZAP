#pragma once

#include <settings.h>

void Bin2Dec(uint16_t data);
void DisplayData(uint16_t data);
void SendData(uint8_t data);

extern volatile uint8_t bcd_buffer[4];
//extern volatile uint8_t segments[];
