#include <lcd.h>


uint8_t segments[] =
{
  // GFEDCBA
  0b00111111, // 0 - A, B, C, D, E, F
  0b00000110, // 1 - B, C
  0b01011011, // 2 - A, B, D, E, G
  0b01001111, // 3 - A, B, C, D, G
  0b01100110, // 4 - B, C, F, G
  0b01101101, // 5 - A, C, D, F, G
  0b01111101, // 6 - A, C, D, E, F, G
  0b00000111, // 7 - A, B, C
  0b01111111, // 8 - A, B, C, D, E, F, G
  0b01101111, // 9 - A, B, C, D, F, G
};

void Bin2Dec(uint16_t data) {
  bcd_buffer[3] = (uint8_t)(data / 1000);
  data = data % 1000;
  bcd_buffer[2] = (uint8_t)(data / 100);
  data = data % 100;
  bcd_buffer[1] = (uint8_t)(data / 10);
  data = data % 10;
  bcd_buffer[0] = (uint8_t)(data);
}

void DisplayData(uint16_t data) {
  Bin2Dec(data);
  PORTB &= ~(1 << PINB1); // clk_out = 0
  SendData(segments[bcd_buffer[0]]);
  SendData(segments[bcd_buffer[1]]);
  SendData(segments[bcd_buffer[2]]);
  SendData(segments[bcd_buffer[3]]);
  PORTB |= (1 << PINB1); // clk_out = 1
}

void SendData(uint8_t data) {
  SPDR = data;
  while (!(SPSR & (1 << SPIF)));
}