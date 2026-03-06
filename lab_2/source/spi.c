#include "spi.h"

void InitSPI(void) {
  DDRB |= (1 << PINB3 | 1 << PINB5); // configure MOSI and CLK as out
  SPSR |= (1 << SPI2X);              // Fclk = Fosc/2
  // SPI enable, master mode, MSB first, CPOL = 0, CPHA = 0
  SPCR = (1 << SPE | 1 << MSTR);
  // init values - DAT low, CLK low
  PORTB &= ~(1 << PINB3 | 1 << PINB5);
}

