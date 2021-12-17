========================================================================================
Analogue Input: C9 30/11/21

╔════════════╗
║Preparation:║
╚════════════╝

1)  The ADC has 10 bits of resolution at 15kHz sample rate.

2)  There are 8 single ended inputs built in, but these are multiplexed.  (These are on Port A pins 0-7)

3)  In the ADCSRA register, there are five bits, however for single ended inputs, we only need binary values from 0 to 7 - the rest are for differential signalling pairs. These five bits are written to ADMUX5:0, but we will only need ADMUX3:0

4)  With Vref at 3V3, the value 0x0FF will refer to a read voltage of 0V822.

5)  CLK/2, CLK/4, CLK/8, CLK/16, CLK/32, CLK/64, CLK/128 are the prescalers available.  For maximum precision, we can use 200kHz sampling, which would mean a prescaler of 64, giving us a sample rate of 187.5kHz.

6)  After the initialisation capture, the number of clock cycles for every proceeding capture will total 24.5 clock cycles (the falling edge of the 24th cycle).

7)
┌────────────────────────────────────────────────┐
void adcinit(){
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
    // Writes to ADC_Enable and ADC_Prescaler
}
└────────────────────────────────────────────────┘

8)
┌────────────────────────────────────────────────┐
void adcstartc(){
    // assuming the ADC is already initialised
    ADCSRA |= _BV(ADSC);
}
└────────────────────────────────────────────────┘

9)
┌────────────────────────────────────────────────┐
void adcendc(){
    while((ADCSRA | 0b01000000));
    // does a bitwise comparison and waits for it
    // to go to 0
}
└────────────────────────────────────────────────┘

10) When ADATE is set to 1 in ADCSRA, the ADC will start a conversion on the rising edge of its trigger signal, which is selected in ADCSRB, ADTS2:0.  We want to trigger on the interrupt, thus we need to set bit ADTS1 in ADCSRB to 1.
After we trigger off the interrupt signal, we need to set ADIF to 0 in the ADCSRA, as the interrupt doesn't actually get used by the CPU, we are just using it to trigger the next conversion.  Auto triggering supports Free Running (default), Analogue Comparator, External Interrupt, and multiple timer/counter inputs.

11) Free Running mode is enabled by default when ADATE is set to 1 (as it requires ADTS2:0 to be 0b000).  This mode will continuously keep sampling at the set speed after the trigger from ADIF is received (ADTS2:0 goes from 0b010 to 0b000).  Thus there are three stages to using Free Running mode.
    1)  Start the first conversion with ADSC set to 1
    2)  Set ADATE to 1 and set the trigger source to ADIF, the next conversion will happen immediately after the first has finished.
    3)  After the second conversion, the trigger source will switch to free running mode, and then start the third conversion.
    4)  The third conversion and onwards will run in free running mode.

========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Measuring Voltages"]
┌──────────────────────────────────────────────────────────────────────────────────────┐
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

└──────────────────────────────────────────────────────────────────────────────────────┘

My values shows the full range from 0 to 1023, however, if it didn't that would most likely be because of manufacturing imperfections with the potentiometer.  You could test it by directly connecting PA0 to GND or VCC.

For me, Vmax - Vmin is surprisingly 0, thus, @ 1.74990V, log2(3.3/1.7499) = 0.9152


3.2 ["Building a Proximity Detector"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
int main(void)
{
    DDRA = 0x00;
    // set port bank a as inputs
    DDRB = 0xFF;
    // set port bank b as outputs
    ADMUX |= 0b000000;
    // PINA0 is the input
	uint16_t result;
	double voltage;
	init_debug_uart0();
	init_adc();
	for (;;)
	{
		result = read_adc();
        voltage = result*VREF/1024;
        printf("%4d : %6.5fV\n", result, voltage);
        if(voltage <= TRIGGER){
            PORTB |= _BV(PB7);
            printf("TRIG\n");
        }
        else{
            PORTB &= ~_BV(PB7);
            printf("IDLE\n");
        }
		_delay_ms(200);
	}
}
└──────────────────────────────────────────────────────────────────────────────────────┘

3.3 ["Measuring your Heart Rate"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#define VREF 3.3
#define TRIGGER 0.4

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
    // set port bank a as inputs
    DDRB = 0xFF;
    // set port bank b as outputs
    ADMUX |= 0b000000;
    // PINA0 is the input
	uint16_t result;
	double voltage;
	init_debug_uart0();
	init_adc();
    unsigned long counter = 0;
    int measuring = 0;
	for (;;)
	{
		result = read_adc();
        if(result >= 5 || measuring == 0){
            measuring = 1;
        }
        if(measuring == 1 || result <= 2){
            while(result <= 2){
                counter++;
            }
            measuring = 0;
        }
        printf("BPM = %f\n", 60000/(counter*0.01));

	}
}
└──────────────────────────────────────────────────────────────────────────────────────┘


