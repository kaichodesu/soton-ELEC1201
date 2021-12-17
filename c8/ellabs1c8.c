========================================================================================
Timers/Counters and Pulse-Width Modulation: C8 24/11/21

╔════════════╗
║Preparation:║
╚════════════╝

2.1.1 ["Tone Oscillator"]

1)  Counter 1 fed from Timer 1 can count up to 2^16 (65535).  We are running the Il Matto at 12MHz which means to reach a good standard audio sampling speed of around 48kHz we will need to divide F_CPU by 250.  In this case, this 16-bit counter can divide by 2^8 or 256, giving us an audio sampling speed of 46.875kHz which is still very good.  As we are running at these speeds, it would be good to have as many bits as possible to count up to.  Furthermore, only Timer 1 allows us to use the Frequency correct wave generation mode, making it more suited to producing melodic frequencies.

2)  To set the PWM modes for Timer 1, we need to edit two registers, TCCR1A and TCCR1B.  Across the two registers, there are four 'Wave Generation Mode' bits, WGM10:1 and WGM13:2, and these four bits WGM13:0 must be set to decimal value 1, 2, 3, 10 or 11.  We will be using decimal values of either 8 or 9 to select Phase and Frequency Correct PWM.
Minimum PWM resolution is 2-bit.

"Timer 1 Phase and Frequency Correct PWM Mode"

WGM13:0 = 8 or 9 (9, TOP = OCR1A : 8, TOP = ICR1)
We are going to choose mode 9 to allow us to use OC1A on Compare Match, and because OCR1A is better for changing TOP due to its double buffer.
TCCR1A |  XX = Default Value (0)

┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│COM1A1│COM1A0│COM1B1│COM1B0│XXXXXX│XXXXXX│WGM11 │WGM10 │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│   0  │   1  │  XX  │  XX  │  XX  │  XX  │  0   │   1  │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘

TCCR1B |  XX = Default Value (0)

┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│ICNC1 │ICES1 │XXXXXX│WGM13 │WGM12 │ CS12 │ CS11 │ CS10 │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│  XX  │  XX  │  XX  │   1  │   0  │   1  │   0  │   1  │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘

3)  T̶o̶ ̶c̶o̶v̶e̶r̶ ̶a̶ ̶f̶r̶e̶q̶u̶e̶n̶c̶y̶ ̶r̶a̶n̶g̶e̶ ̶b̶e̶t̶w̶e̶e̶n̶ ̶5̶0̶H̶z̶ ̶a̶n̶d̶ ̶5̶k̶H̶z̶,̶ ̶a̶ ̶s̶a̶m̶p̶l̶i̶n̶g̶ ̶r̶a̶t̶e̶ ̶o̶f̶ ̶a̶t̶ ̶l̶e̶a̶s̶t̶ ̶5̶0̶0̶0̶*̶(̶B̶i̶t̶ ̶D̶e̶p̶t̶h̶)̶ ̶s̶h̶o̶u̶l̶d̶ ̶b̶e̶ ̶u̶s̶e̶d̶ ̶t̶o̶ ̶p̶r̶o̶v̶i̶d̶e̶ ̶v̶o̶l̶u̶m̶e̶ ̶c̶o̶n̶t̶r̶o̶l̶ ̶t̶h̶r̶o̶u̶g̶h̶ ̶P̶W̶M̶ ̶a̶s̶ ̶t̶o̶ ̶a̶d̶j̶u̶s̶t̶ ̶t̶h̶e̶ ̶D̶u̶t̶y̶ ̶C̶y̶c̶l̶e̶ ̶o̶f̶ ̶t̶h̶e̶ ̶P̶W̶M̶ ̶s̶i̶g̶n̶a̶l̶,̶ ̶w̶e̶ ̶n̶e̶e̶d̶ ̶a̶ ̶h̶i̶g̶h̶e̶r̶ ̶r̶e̶s̶o̶l̶u̶t̶i̶o̶n̶ ̶t̶h̶a̶n̶ ̶t̶h̶e̶ ̶5̶k̶H̶z̶ ̶w̶a̶v̶e̶ ̶i̶t̶s̶e̶l̶f̶.̶ ̶ ̶A̶s̶ ̶w̶e̶ ̶a̶r̶e̶ ̶u̶s̶i̶n̶g̶ ̶1̶6̶-̶b̶i̶t̶ ̶r̶e̶g̶i̶s̶t̶e̶r̶s̶,̶ ̶w̶e̶ ̶s̶h̶o̶u̶l̶d̶ ̶a̶i̶m̶ ̶f̶o̶r̶ ̶a̶ ̶s̶a̶m̶p̶l̶i̶n̶g̶ ̶r̶a̶t̶e̶ ̶o̶f̶ ̶a̶r̶o̶u̶n̶d̶ ̶8̶0̶k̶H̶z̶ ̶f̶o̶r̶ ̶p̶e̶r̶f̶e̶c̶t̶ ̶v̶o̶l̶u̶m̶e̶ ̶c̶o̶n̶t̶r̶o̶l̶ ̶a̶t̶ ̶a̶l̶l̶ ̶f̶r̶e̶q̶u̶e̶n̶c̶i̶e̶s̶.̶ ̶ ̶B̶y̶ ̶u̶s̶i̶n̶g̶ ̶a̶ ̶p̶r̶e̶s̶c̶a̶l̶e̶r̶ ̶o̶f̶ ̶2̶5̶6̶,̶ ̶w̶e̶ ̶c̶a̶n̶ ̶a̶c̶h̶i̶e̶v̶e̶ ̶a̶ ̶s̶a̶m̶p̶l̶e̶ ̶r̶a̶t̶e̶ ̶o̶f̶ ̶4̶6̶.̶8̶7̶5̶k̶H̶z̶,̶ ̶w̶h̶i̶c̶h̶ ̶i̶s̶ ̶n̶o̶t̶ ̶f̶a̶r̶ ̶o̶f̶f̶ ̶t̶h̶e̶ ̶u̶s̶u̶a̶l̶ ̶4̶8̶k̶H̶z̶ ̶u̶s̶e̶d̶ ̶i̶n̶ ̶a̶u̶d̶i̶o̶ ̶(̶a̶l̶t̶h̶o̶u̶g̶h̶ ̶u̶s̶u̶a̶l̶l̶y̶ ̶w̶i̶t̶h̶ ̶a̶ ̶b̶i̶t̶ ̶d̶e̶p̶t̶h̶ ̶o̶f̶ ̶2̶4̶b̶i̶t̶s̶ ̶o̶r̶ ̶3̶2̶b̶i̶t̶s̶ ̶p̶e̶r̶ ̶c̶y̶c̶l̶e̶ ̶r̶a̶t̶h̶e̶r̶ ̶t̶h̶a̶n̶ ̶1̶ ̶b̶i̶t̶ ̶p̶e̶r̶ ̶c̶y̶c̶l̶e̶)̶.̶

For the Tone PWM Generator, we only need to sample up to 10kHz (2*5000).  As F_CPU is 12MHz, we can use a 1024 divider to sample at 11.71875kHz.

4)  Selecting the Wave Generation Mode and Prescaler.  We use mode 9 as its bit depth is controlled by the Input Comparison Register ICR1 which will represent the bit depth of the PWM signal with a duty cycle of 100%

┌────────────────────────────────────────────────┐
TCCR1A = 0;
TCCR1B = 0;
TCCR1A |= _BV(WGM10);
TCCR1B |= _BV(WGM13);
//  Sets to mode 9 (WGM13:0 = 0b1001)
TCCR1B |= _BV(CS12) | _BV(CS10);
//  Sets the prescaler to 1024 (CS12:0 = 0b101)
└────────────────────────────────────────────────┘

5)  Only now did I realise that this lab wants us to use two PWM signals.  One PWM signal for the base frequency and the other PWM signal for the Duty Cycle to control the volume level.  Then we do a bit comparison between the the base frequency and the duty cycle to produce a duty cycle modulated signal at the base frequency.
    To output on Compare Match Channel A, we need to set bit COM1A0 to 1, giving us a
50% Duty Cycle.

The equation that relates the frequency to the registers is as follows:

Frequency = (ioclock) / (2 * 1024 * ICR1)

Thus to change the frequency, we must change the value stored in ICR1

ICR1 = (12000000) / (Frequency * 2 * 1024)
IRC1 = 5859.375 / Frequency

┌──────────────────────────────────────────────────────────────────────────────────────┐
void setPitch(unsigned float pitch){
    DDRD |= _BV(OC1A);     // Allows us to read the waveform on Pin D 5
    TCCR1A |= _BV(COM1A0);  // Sets the 6th bit of Control Register A to 1
                            // Giving us a 50% duty cycle.
    OCR1A = (5859.375/pitch);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

2.1.2 ["PWM Oscillator for Amplitude Control"]

1)  As we need two individually controllable outputs, we are forced to choose Timer 0 as Timer 2 is only a single channel counter.  However, Timer 0 does not have the prescaler we need of 128 to allow for it to run at 8 times the frequency of Timer 1 for 8 bit modulation.

2)   ̶I̶f̶ ̶w̶e̶ ̶w̶a̶n̶t̶ ̶8̶ ̶b̶i̶t̶s̶ ̶o̶f̶ ̶m̶o̶d̶u̶l̶a̶t̶i̶o̶n̶ ̶f̶o̶r̶ ̶t̶h̶e̶ ̶v̶o̶l̶u̶m̶e̶,̶ ̶w̶e̶ ̶w̶i̶l̶l̶ ̶n̶e̶e̶d̶ ̶t̶o̶ ̶s̶a̶m̶p̶l̶e̶ ̶a̶t̶ ̶a̶t̶ ̶l̶e̶a̶s̶t̶ ̶8̶ ̶t̶i̶m̶e̶s̶ ̶t̶h̶e̶ ̶s̶a̶m̶p̶l̶e̶ ̶r̶a̶t̶e̶ ̶o̶f̶ ̶t̶h̶e̶ ̶m̶a̶i̶n̶ ̶c̶l̶o̶c̶k̶ ̶w̶h̶i̶c̶h̶ ̶i̶s̶ ̶1̶1̶.̶7̶1̶8̶7̶5̶k̶H̶z̶.̶ ̶ ̶T̶h̶u̶s̶ ̶w̶e̶ ̶w̶i̶l̶l̶ ̶n̶e̶e̶d̶ ̶t̶o̶ ̶r̶u̶n̶ ̶a̶t̶ ̶9̶3̶.̶7̶5̶k̶H̶z̶.̶ ̶ ̶S̶t̶r̶i̶c̶t̶l̶y̶ ̶s̶p̶e̶a̶k̶i̶n̶g̶ ̶t̶h̶e̶ ̶f̶a̶s̶t̶e̶s̶t̶ ̶f̶r̶e̶q̶u̶e̶n̶c̶y̶ ̶w̶e̶ ̶c̶a̶n̶ ̶u̶s̶e̶ ̶w̶o̶u̶l̶d̶ ̶b̶e̶ ̶F̶_̶C̶P̶U̶/̶8̶ ̶w̶h̶i̶c̶h̶ ̶i̶s̶ ̶1̶.̶5̶M̶H̶z̶ ̶w̶h̶i̶c̶h̶ ̶i̶s̶ ̶f̶a̶r̶ ̶h̶i̶g̶h̶e̶r̶ ̶t̶h̶a̶n̶ ̶a̶n̶y̶o̶n̶e̶ ̶c̶a̶n̶ ̶h̶e̶a̶r̶ ̶s̶o̶ ̶t̶h̶e̶r̶e̶ ̶i̶s̶ ̶n̶o̶t̶ ̶m̶u̶c̶h̶ ̶o̶f̶ ̶a̶n̶ ̶i̶s̶s̶u̶e̶ ̶w̶i̶t̶h̶ ̶f̶r̶e̶q̶u̶e̶n̶c̶y̶ ̶l̶i̶m̶i̶t̶s̶.̶
 ̶A̶s̶ ̶w̶e̶ ̶w̶a̶n̶t̶ ̶a̶ ̶f̶r̶e̶q̶u̶e̶n̶c̶y̶ ̶o̶f̶ ̶9̶3̶.̶7̶5̶k̶H̶z̶,̶ ̶w̶e̶ ̶w̶i̶l̶l̶ ̶n̶e̶e̶d̶ ̶a̶ ̶p̶r̶e̶s̶c̶a̶l̶e̶r̶ ̶o̶f̶ ̶1̶2̶8̶.̶.̶.̶ ̶w̶h̶i̶c̶h̶ ̶T̶i̶m̶e̶r̶ ̶0̶ ̶d̶o̶e̶s̶ ̶n̶o̶t̶ ̶h̶a̶v̶e̶.̶ ̶ ̶H̶o̶w̶e̶v̶e̶r̶,̶ ̶i̶t̶ ̶h̶a̶s̶ ̶a̶ ̶p̶r̶e̶s̶c̶a̶l̶e̶r̶ ̶o̶f̶ ̶6̶4̶ ̶w̶h̶i̶c̶h̶ ̶w̶o̶u̶l̶d̶ ̶g̶i̶v̶e̶ ̶u̶s̶ ̶1̶6̶ ̶b̶i̶t̶s̶ ̶o̶f̶ ̶m̶o̶d̶u̶l̶a̶t̶i̶o̶n̶,̶ ̶a̶l̶t̶h̶o̶u̶g̶h̶ ̶w̶e̶ ̶w̶i̶l̶l̶ ̶o̶n̶l̶y̶ ̶b̶e̶ ̶u̶s̶i̶n̶g̶ ̶t̶h̶e̶m̶ ̶i̶n̶ ̶p̶a̶i̶r̶s̶ ̶t̶o̶ ̶m̶i̶m̶i̶c̶ ̶8̶ ̶b̶i̶t̶s̶.̶

Using Fast PWM mode has a 256 divisor on F_CPU, limiting us to 46.875kHz for a single 8 bit comparison.

Frequency = (ioclock) / 256


3)  "Timer 0 Fast PWM Mode 3"

TCCR0A |  XX = Default Value (0)

┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│COM0A1│COM0A0│COM0B1│COM0B0│XXXXXX│XXXXXX│WGM01 │WGM00 │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│  01  │  00  │  01  │  00  │  XX  │  XX  │  1   │   1  │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘

TCCR0B |  XX = Default Value (0)

┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│FOC0A │FOC0B │XXXXXX│XXXXXX│WGM02 │ CS02 │ CS01 │ CS00 │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│  XX  │  XX  │  XX  │  XX  │   0  │   0  │   0  │   1  │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘

CS02:0 = 0b001
//  Prescaler of 1
WGM02:0 = 0b011
//  Mode 3
COM0A1:0 = 0b10
//  Sets Output A to non inverting Compare Match
COM0B1:0 = 0b10
//  Sets Output B to non inverting Compare Match

Setting OCR0A and OCR0B allows you to control the Duty Cycle of the waveform.

2.2 ["Port/Pin Assignment"]

┌─────┬──────┬──────────────────┬──────────────┐
│ Pin │ Bank │ Function/Mapping │ Description  │
├─────┼──────┼──────────────────┼──────────────┤
│  3  │   B  │       OC0A       │ Volume Left  │
│  4  │   B  │       OC0B       │ Volume Right │
│  5  │   D  │       OC1A       │ Tone Output  │
└─────┴──────┴──────────────────┴──────────────┘
DDRB |= _BV(OC0A) | _BV(OC0A);
DDRD |= _BV(OC1A);

========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Producing an Audio Frequency Square Wave"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
/*
 * Pinout:
 *┌─────┬──────┬──────────────────┬──────────────┐
 *│ Pin │ Bank │ Function/Mapping │ Description  │
 *├─────┼──────┼──────────────────┼──────────────┤
 *│  3  │   B  │      OCR0A       │ Volume Left  │
 *│  4  │   B  │      OCR0B       │ Volume Right │
 *│  5  │   D  │      OCR1A       │ Tone Output  │
 *└─────┴──────┴──────────────────┴──────────────┘
 */
#include <avr/io.h>
#include <util/delay.h>

#define TONE_OSC_PRESCALER 8UL
#define FREQ 262
unsigned long toneClock;   /* set at timer initialisation and used
                              to calculate TOP when setting frequency */

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();

    for (;;) tone(FREQ);

}
/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
    //DDRD = 0x00;
    // Set all pins as inputs
    DDRD |= _BV(PD5);
    // Bitmask to set Pin D5 as an output
    //TCCR1A = 0;
    //TCCR1B = 0;
    // Initialises control registers as 0
    TCCR1A |= _BV(WGM10) | _BV(COM1A0);
    // Sets to mode 9 (WGM13:0 = 0b1001) and sets duty cycle to 50% (COM1A1:0 = 1)
    TCCR1B |= _BV(WGM13) |  _BV(CS11) /*| _BV(CS12)*/;
    // Sets the prescaler to 1024 (CS12:0 = 0b101)
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
    OCR1A = (uint16_t)((F_CPU) / (TONE_OSC_PRESCALER * 2 * 2 * frequency));
    // Frequency = (ioclock) / (2 * 1024 * ICR1)
}
└──────────────────────────────────────────────────────────────────────────────────────┘

There is a small differnce in the frequency, around 30Hz.  This is caused because 262 doesnt divide perfectly into the sampling rate, thus it rounds to the closest frequency that can be sampled.  The frequency is 292Hz.

3.2 ["Generate a Tone Scale"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
/*
 * Pinout:
 *┌─────┬──────┬──────────────────┬──────────────┐
 *│ Pin │ Bank │ Function/Mapping │ Description  │
 *├─────┼──────┼──────────────────┼──────────────┤
 *│  3  │   B  │      OCR0A       │ Volume Left  │
 *│  4  │   B  │      OCR0B       │ Volume Right │
 *│  5  │   D  │      OCR1A       │ Tone Output  │
 *└─────┴──────┴──────────────────┴──────────────┘
 */
#include <avr/io.h>
#include <util/delay.h>
#include "et_scale.h"

#define TONE_OSC_PRESCALER 8UL

#define FREQ 262
unsigned long toneClock;   /* set at timer initialisation and used
                              to calculate TOP when setting frequency */

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {
    init_tone();
    int index = 0;
    int dir = 1;
    for (;;){
        //tone(400);
        index += dir;
        _delay_ms(50);
        tone(et_scale[index]);
        if(index  >= ET_SCALE_TOP){
            dir = -1;
        }
        if(index <= 0){
            dir = 1;
        }
    }
}
/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
    //DDRD = 0x00;
    // Set all pins as inputs
    DDRD |= _BV(PD5);
    // Bitmask to set Pin D5 as an output
    //TCCR1A = 0;
    //TCCR1B = 0;
    // Initialises control registers as 0
    TCCR1A |= _BV(WGM10) | _BV(COM1A0);
    // Sets to mode 9 (WGM13:0 = 0b1001) and sets duty cycle to 50% (COM1A1:0 = 1)
    TCCR1B |= _BV(WGM13) |  _BV(CS11) /*| _BV(CS12)*/;
    // Sets the prescaler to 1024 (CS12:0 = 0b101)
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
    OCR1A = (uint16_t)((F_CPU) / (TONE_OSC_PRESCALER * 2 * 2 * frequency));

}
└──────────────────────────────────────────────────────────────────────────────────────┘

3.3 ["Play a Tune"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
int main() {
    uint16_t f;

    DDRB |= _BV(PB7); /* LED */
    init_tone();

    for(;;){
    	melody2freq(melody);  /* initialise  */
    	while((f=melody2freq(NULL)) != M2F_END) {
    		if (f == M2F_UNKOWN) continue; /* skip unknown symnols */
    		tone(f);
    		_delay_ms(STEP_DELAY_MS);
		PORTB ^= _BV(PB7); /* toggle LED */
    	}
    	_delay_ms(STEP_DELAY_MS);
    	_delay_ms(STEP_DELAY_MS);
    }
}

void init_tone(void)
{
    //DDRD = 0x00;
    // Set all pins as inputs
    DDRD |= _BV(PD5);
    // Bitmask to set Pin D5 as an output
    //TCCR1A = 0;
    //TCCR1B = 0;
    // Initialises control registers as 0
    TCCR1A |= _BV(WGM10) | _BV(COM1A0);
    // Sets to mode 9 (WGM13:0 = 0b1001) and sets duty cycle to 50% (COM1A1:0 = 1)
    TCCR1B |= _BV(WGM13) |  _BV(CS11) /*| _BV(CS12)*/;
    // Sets the prescaler to 1024 (CS12:0 = 0b101)
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
    OCR1A = (uint16_t)((F_CPU) / (TONE_OSC_PRESCALER * 2 * 2 * frequency));
    PORTA |= _BV(PA7);
    _delay_ms(5);
    PORTA &= ~_BV(PA7);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

When a breif pulse is applied to the trigger, this will cause the capacitor to charge up very slightly.  This will cause the decay, or the falling edge of the square wave to be elongated and the gradient to be decreased, resulting in a reverb-like effect.  The diode is there to ensure that the capacitor does not discharge into the microcontroller's pin.

This was actually wrong.  The capacitor did not add decay, rather, it just added dynamics.  The pulse charges the capacitor, causing the voltage to be stay higher for longer, however, over time the capacitor discharges, causing the volume to decrease over time during the duration of the note.

As the trigger pulse decreases in length, the length of the decay decreases, but a slow negative ramp up is also introduced.

3.4 ["PWM Volume Control"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
int main() {
    uint16_t f;

    DDRB |= _BV(PB7); /* LED */
    init_tone();
    init_volume();
    uint8_t vol = 0;
    volume(vol);
    for(;;){
    	melody2freq(melody);  /* initialise  */
    	while((f=melody2freq(NULL)) != M2F_END) {
    		if (f == M2F_UNKOWN) continue; /* skip unknown symnols */
                volume(vol);
                tone(f);
    		_delay_ms(STEP_DELAY_MS);
            vol = vol + 20;
		PORTB ^= _BV(PB7); /* toggle LED */
    	}
    	_delay_ms(STEP_DELAY_MS);
    	_delay_ms(STEP_DELAY_MS);
    }
}

void init_volume(void)
{
    DDRB|= _BV(PB3) | _BV(PB4);
    TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(CS00);
}

void volume(uint8_t x){
    OCR0A = x;
}
└──────────────────────────────────────────────────────────────────────────────────────┘

When the maximum volume is reached, since we are using uint8_t, the value overflows back down to 0 and the volume falls again.

4 ["Optional Additional Work, Stereo Panning"]

Implementation in melody.c:

┌──────────────────────────────────────────────────────────────────────────────────────┐
void init_pan(void)
{
    DDRB|= _BV(PB3) | _BV(PB4);
    TCCR0A |= _BV(COM0A1) | _BV(COM0B1)| _BV(COM0B0) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(CS00);
}

void panning(uint8_t x){
    OCR0A = x;
    OCR0B = x - 127;
}
└──────────────────────────────────────────────────────────────────────────────────────┘

























