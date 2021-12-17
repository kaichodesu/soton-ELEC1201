/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#define VREF 3.3

void init_adc(void)
{
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
    // Writes to ADC_Enable and ADC_Prescaler
}

uint16_t read_adc(void)
{
    // assuming the ADC is already initialised
    ADCSRA |= _BV(ADSC);
    while((ADCSRA & 0b01000000));
    // does a bitwise comparison and waits for it to go to 0
    ADC = ADCH;
    ADC = ADC << 8;
    // each register is 8 bit, thus we need to shift by 8 bits before reading
    ADC += ADCL;
	return (uint16_t)ADC;
}

int main(void)
{
    DDRA = 0x00;
    // Sets Port A as an input
    ADMUX |= 0b000000; // PINA0 is the input
	uint16_t result;
	double voltage;
	
	init_debug_uart0();
	init_adc();

	for (;;) 
	{
		result = read_adc();
        voltage = result*VREF/1024;
		printf("%4d : %6.5fV\n", result, voltage);
		_delay_ms(200);
	}
}
