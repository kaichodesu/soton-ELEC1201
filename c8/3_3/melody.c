/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "et_scale.h"
#define TONE_OSC_PRESCALER 8UL
#define STEP_DELAY_MS 450
#define M2F_END    0
#define M2F_REST   1
#define M2F_UNKOWN 2
const char melody[] ="\
X:1\n\
T: Prelude from first Cello Suite\n\
C: J.S. Bach, here transposed for mandolin\n\
M: 4/4\n\
L: 1/16\n\
K:D\n\
(DAf)e fAfA (DAf)e fAfA | (DBg)f gBgB (DBg)f gBgB |\n\
(Dcg)f gcgc (Dcg)f gcgc | (Ddf)d fdfd (Ddf)d fdfd |\n\
(DBf)e fdcd Bdcd FA^GF  | (^Gde)d eded (^Gde)d eded |\n\
(cea)^g aede cede AcBA  | (B,Fd)c dFdF (B,Fd)c dFdF |\n\
(B,^GA)B AGFE (dcB)a ^gfed | (cBA)a eace (ABc)e dcBA |\n\
^d(A=cB) cAdA f(AcB) cAdA  | (GBe)f geBA (GBe)f ge^cB |\n\
^A(cAc) ecec A(cAc) ecec   | (dcB)d cdec dcBA GFED |\n\
CGAG AGAG CGAG AGAG | (DF=c)B cFcF (DFc)B cFcF |\n\
(DGB)A BGBG (DGB)A BGBG | (D^cg)f gcgc (Dcg)f gcgc |\n\
(DAf)e fdcB AGFE DCB,A, | ^G,(EBc) dBcd G,(EBc) dBcd |\n\
=G,(EAB) cABc =G,(EAB) cABc | G,(EAc) (e^g(a2) a)EF=G ABcd |\n\
%second part\n\
(ecA)B cdef (gec)d efga | _ba^ga a=gfg gec=B AEFG |\n\
A,(EAc) efge (fdA)G FDEF | A,DFA defe ^g=fef fe^de |\n\
e=dcd dB^GF EGBd e^gag | aecB ceAc EA^GF EDCB, |\n\
A,2 (=gf edcB A)(gfe dcBA | G)(fed cBAG F)(edc BAGF |\n\
F)(dcB) [cc]e[AA]e [BB]e[cc]e [dd]e[BB]e | [cc]e[AA]e [dd]e[BB]e [cc]e[AA]e [dd]e[BB]e |\n\
[cc]e[AA]e [BB]e[cc]e [dd]e[ee]e [ff]e[AA]e | [ee]e[ff]e [gg]e[AA]e [ff]e[gg]e [aa]e[ff]e |\n\
[gg]e[ff]e [gg]e[ee]e [ff]e[ee]e [ff]e[dd]e | [ee]e[dd]e [ee]e[cc]e [dd]e[cc]e [dd]e[BB]e |\n\
ceAB =cA^cA dA^dA eA=fA | ^fAgA ^gAaA ^bA=bA=c'A^c'A |\n\
d'(fAf) d'fd'f d'(fAf) d'fd'f | d'(eAe) d'ed'e d'(eAe) d'ed'e |\n\
c'(gAg) c'gc'g c'(gAg) c'gc'g | [D16Afd'] |]\
";
void init_tone(void);
void tone(uint16_t frequency);
void init_pan(void);
void panning(uint8_t x);
uint16_t melody2freq(const char *abc_melody);


int main() {
    uint16_t f;

    DDRB |= _BV(PB7); /* LED */
    init_tone();
    init_pan();
    uint8_t pan = 0;
    panning(pan);
    for(;;){
    	melody2freq(melody);  /* initialise  */
    	while((f=melody2freq(NULL)) != M2F_END) {
    		if (f == M2F_UNKOWN) continue; /* skip unknown symnols */
                panning(pan);
                tone(f);
    		_delay_ms(STEP_DELAY_MS);
            pan = pan + 10;
		PORTB ^= _BV(PB7); /* toggle LED */
    	}
    	_delay_ms(STEP_DELAY_MS);
    	_delay_ms(STEP_DELAY_MS);
    }
}

void init_pan(void)
{
    DDRB|= _BV(PB3) | _BV(PB4);
    TCCR0A |= _BV(COM0A1) | _BV(COM0B1)| _BV(COM0B0) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(CS00);
}
 b
void panning(uint8_t x){
    OCR0A = x;
    OCR0B = x - 127;
}

void init_tone(void)
{
    //DDRD = 0x00;
    // Set all pins as inputs
    DDRD |= _BV(PD5);
    DDRD |= _BV(PA7);
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

uint16_t melody2freq(const char *m) {
    static const char *melody;
    static uint16_t pos;
    static uint8_t scale_index;

    if(m != NULL){  /* initialization */
        melody = m;
        pos = 0;
        return M2F_END; /* to be ignored */
    }

    if(melody[++pos] == '\0') return M2F_END;


    switch( melody[pos] ) {
	case 'c':
	case 'C': {
	    scale_index = ET_SCALE_C;
	    break;
	}
	case 'd':
	case 'D': {
	    /* 2 semitones above C */
	    scale_index = ET_SCALE_C + 2;
	    break;
	}
	case 'e':
	case 'E': {
	    /* 4 semitones above C */
	    scale_index = ET_SCALE_C + 4;
	    break;
	}
	case 'f':
	case 'F': {
	    /* 5 semitones above C */
	    scale_index = ET_SCALE_C + 5;
	    break;
	}
	case 'g':
	case 'G': {
	    /* 7 semitones above C */
	    scale_index = ET_SCALE_C + 7;
	    break;
	}
	case 'a':
	case 'A': {
	    /* 9 semitones above C */
	    scale_index = ET_SCALE_C + 9;
	    break;
	}
        case 'b':
	case 'B': {
	    /* 11 semitones above C */
	    scale_index = ET_SCALE_C + 11;
	    break;
	}
        default:
	    { /* unknown symbol --> no change */
		return M2F_UNKOWN;
	    }
    }

    if(  melody[pos] > 'Z' ) {  /* lower case chars have higher ASCII codes than A-Z */
         scale_index += 12;     /* shift one octave up */
    }

    return et_scale[scale_index];
}
