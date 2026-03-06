#include <usart.h>

void InitUSART() 
{
  UCSR0B = (1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0);
  UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);
  UBRR0H = 0;
  UBRR0L = 0x0C;
}