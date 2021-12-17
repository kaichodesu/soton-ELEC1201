#include <avr/io.h>
#include <avr/interrupt.h>

void init_adc(void)
{
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
    // Writes to ADC_Enable and ADC_Prescaler is set to 64 to get 187.5kHz sample rate
    ADCSRA |= _BV(ADIE);
    // Sets ADC_Interrupt_Enable
    ADCSRA |= _BV(ADATE) | _BV(ADSC);
    // Sets ADC to free running mode and starts the ADC
}

ISR(ADC_vect){PINB |= _BV(PB7);}

int main(void)
{
    DDRB = 0xFF;
    // set port bank b as outputs
	init_adc();
    sei();
	while(1);
}
