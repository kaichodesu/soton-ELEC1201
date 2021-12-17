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


