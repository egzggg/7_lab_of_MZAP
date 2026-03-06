#include <adc.h>


void InitADC(void) 
{
  ADMUX = (1 << MUX0);                // Align left, ADC1
  ADCSRB = (1 << ADTS2 | 1 << ADTS0); // Start on Timer1 COMPB
  // Enable, auto update, IRQ enable
  ADCSRA = (1 << ADEN | 1 << ADATE | 1 << ADIE);
}

void SendADC(void) 
{
    display_val = ADC;
}