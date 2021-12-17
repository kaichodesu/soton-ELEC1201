/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#define VREF 3.3
#define TRIGGER 1.5

void init_adc(void)
{
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
    // Writes to ADC_Enable and ADC_Prescaler is set to 64 to get 187.5kHz sample rate
    ADCSRA |= _BV(ADIE);
    // Sets ADC_Interrupt_Enable
    ADCSRA |= _BV(ADATE) | _BV(ADSC);
    // Sets ADC to free running mode and starts the ADC
    sei();
}

/*uint16_t read_adc(void)
{
    // assuming the ADC is already initialised
    uint16_t ADC;
    ADCSRA |= _BV(ADSC);
    while((ADCSRA | 0b01000000));
    // does a bitwise comparison and waits for it to go to 0
    ADC = ADCH;
    ADC = ADC << 8;
    ADC += ADCL;
	return ADC;
}*/

ISR(ADC){
    ADC = ADCH;
    ADC = ADC << 8;
    ADC += ADCL;

int main(void)
{
    DDRA = 0x00;
    // set port bank a as inputs
    PORTA = 0xFF;
    // enable pull up resistors
    DDRB = 0xFF;
    // set port bank b as outputs
    // ADMUX |= 0b000000 PINA0 is the input
	uint16_t result;
	double voltage;
	init_debug_uart0();
	init_adc();
	for (;;)
	{
		result = read_adc();
        voltage = result*VREF/1024;
        if(voltage <= TRIGGER){
            PINA |= _BV(PB0);
        }
        else{
            PINA &= ~_BV(PB0);
        }
	}
}
