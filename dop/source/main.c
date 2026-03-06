#include <settings.h>
#include <lcd.h>
#include "spi.h"
#include <usart.h>
#include <adc.h>

void InitPorts(void);
void InitTimer1(void);
void SendData(uint8_t data);
void SendChar(char symbol);
void SendString(char *buffer);
void clear(volatile char *strings);
volatile uint8_t bcd_buffer[] = {0, 0, 0, 0};
volatile uint16_t display_val = 0;
volatile uint8_t flag= 0;
volatile char usart_string[8];
volatile uint8_t vol = 0;
volatile uint8_t flag_usart = 0;
volatile char strings[3] = {'\0', '\0', '\0'};


int main(void) 
{
  InitPorts();
  InitSPI();
  InitTimer1();
  EIMSK |= (1 << INT0);  // Enable INT0
  EICRA |= (1 << ISC01); // Trigger on falling edge of INT0
  InitADC();
  InitUSART();
  sei();                  // global interrupt enable
  PORTB &= ~(1 << PINB0); // OE = low (active)
  DisplayData(0);
  SendString("Hello\r\n");

  while (1) 
  {
    // DisplayData(display_val);
    // if (flag == (flag & 0x01))
    // {
    //   SendString("Value = ");
    //   SendChar(0x30 + bcd_buffer[3]);
    //   SendChar(0x30 + bcd_buffer[2]);
    //   SendChar(0x30 + bcd_buffer[1]);
    //   SendChar(0x30 + bcd_buffer[0]);
    //   SendString("\r\n");
    //   flag &= ~0x01;
    // }
    // if (flag == (flag & 0x02))
    // {
    //   SendString("Roger that\r\n");
    //   flag &= ~0x02;
    // }
    if (flag_usart == 0x01)  
    {
      if (usart_string[0] == 'g' &&  usart_string[1]== 't' && usart_string[2] == ' ')
        {
        uint16_t val = 0;

        for (int i = 3; i < 7; i++)
        {
            if (usart_string[i] >= '0' && usart_string[i] <= '9')
          {
              val = val * 10 + (usart_string[i] - '0');
          }
          else
          {
              val = 0;
              break;
          }
        }
        display_val = val;        // обновляем значение для дисплея
        DisplayData(display_val); // показываем на индикаторе
        flag_usart = 0;
        clear(usart_string);
      }
    
      flag_usart = 0;
      vol = 0;
      clear(usart_string);
    }
  }
}

//--------------------------------------------
ISR(TIMER1_COMPB_vect) {}
ISR(INT0_vect) 
{
  //flag |= 0x01;
  for (int i = 0; i < 8; i++)
  {
    usart_string[i] = '0';
  }
  flag_usart = 0x01;

}

ISR(ADC_vect) 
{ 
  SendADC();
}

ISR(USART_RX_vect) 
{

  char c = UDR0;

  if (c == '\r' || c == '\n')
  {
    flag_usart = 1;
    vol = 0;
    return;
  }
 if (vol < 7)
    {
        usart_string[vol++] = c;
    }
}
//--------------------------------------------
void InitPorts(void) 
{
  DDRB = (1 << PINB0 | 1 << PINB1 | 1 << PINB3 | 1 << PINB5);
  DDRD = (0 << PIND2);
  PORTD |= (1 << PIND2);
}

void InitTimer1(void) 
{
  TCCR1A = 0; // CTC mode - Clear Timer on Compare
  // prescaler = sys_clk/64
  TCCR1B = (1 << CS11 | 1 << CS10 | 1 << WGM12);
  TCNT1 = 0; // start value of counter
  TIMSK1 |= (1 << OCIE1B);
  OCR1A = 1562;
  OCR1B = 1562;
}

void SendChar(char symbol) 
{
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = symbol;
}

void SendString(char *buffer) 
{
  while (*buffer != 0) 
  {
    SendChar(*buffer++);
  }
}

void clear(volatile char *usart_string)
{
  for (int i = 0; i < 8; i++)
  {
    usart_string[i] = '\0';
  }

}