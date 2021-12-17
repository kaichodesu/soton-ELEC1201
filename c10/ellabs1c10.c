========================================================================================
Interrupts: C10 09/12/21

╔════════════╗
║Preparation:║
╚════════════╝

1)  The Il Matto has many different types of interrupt sources, including Digital Input pins (external interrupt sources and pin change interrupts), Timer/Counter interrupts (such as COMPA or OVF), Serial interrupts and ADC interrupts.

2)  The volatile declaration tells the compiler to avoid the optimisation stage for that specific variable as within the ISR the variable may evaluate as being constant or unnecessary, resulting in the compiler inappropriately removing it.  An example of optimisation is as below:
┌────────────────────────────────────────────────┐
static int foo;

void unoptimised(void){
    foo = 0;
    while (foo != 255);
}

void compiler_optimised(void){
    foo = 0;
    while(1);
}
└────────────────────────────────────────────────┘

3)  Interrupts must be enabled locally within the hardware block being used first and then enabled using sei(); to enable interrupts globally.  For example, to enable interrupts from Timer 1, you would have to:
┌────────────────────────────────────────────────┐
TIMSK1 |= _BV(OCIE1A);
sei();
└────────────────────────────────────────────────┘

4)  To act on an ADC conversion complete event, you must first set the ADC Interrupt Enable flag in the ADC Control Register A, and then set the I-bit in SREG to high using sei();
┌────────────────────────────────────────────────┐
void main(){
    ADCSRA |= _BV(ADIE);
    sei();
    while(1);
}

ISR(ADC){
    /* Interrupt Code*/
}
└────────────────────────────────────────────────┘

5)  You would use interrupts whenever you have hardware events that you want to acknowledge immediately without having to expend CPU cycles to constantly poll for data.
========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Timer Interrupts"]
┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/interrupt.h>

volatile uint8_t count = 0;

void init_timer(void){
    //  We want clear timer on compare match (comparing to a specific time)
    TCCR1A |= 0;
    TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10);
    //  Enables CTC, TOP = OCRA and sets prescaler to 1024 desus
    TIMSK1 |= _BV(OCIE1A);
    //  Enables compare match A interrupt
}

void delay(uint16_t ms){OCR1A = (uint16_t) ((ms/1000) * F_CPU * (1/(2 * 1024))) - 1;}

ISR(TIMER1_COMPA_vect){count++; if(count >= 10){count = 0;}}

int main() {
    DDRA = 0xFF;
    const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    delay(1000);
    init_timer();
    sei();
    while(1){PORTA = segments[count];}
    return 0;
}
└──────────────────────────────────────────────────────────────────────────────────────┘

3.2 ["ADC Interrupts"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/interrupt.h>

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
└──────────────────────────────────────────────────────────────────────────────────────┘

3.3 ["External Interrupts"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/interrupt.h>

volatile uint8_t count = 0;

void init(void){
    EICRA |= _BV(ISC01) | _BV(ISC11);
    // Sets INT0 and INT1 to detect falling edges.
    EIMSK |= _BV(INT0) | _BV(INT1);
    // Enables INT0 and INT1
    DDRC = 0xFF;
    // Port C = output desu
}

void write(uint8_t c){
    cli();
    // Will output a binary sequence at Pin C0
    for(int i = 0; i <= 8; i++){
        if(0b10000000 & (c << i)){
            // Reads through the 8-bit integer from left to right
            PORTC |= _BV(PC0);
        }
        else{
            PORTC &= ~_BV(PC0);
        }
    }
    sei();
}

ISR(INT0_vect){write(++count);}

ISR(INT1_vect){write(--count);}

void main(){
    init();
    sei();
    while(1);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

4.1 [Multiple Interrupts"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/interrupt.h>

volatile uint8_t count = 0;

void init_timer(void){
    TCCR0A |= _BV(WGM01);
    //  Sets to CTC mode
    TCCR0B |= _BV(CS12) | _BV(CS10);
    //  Sets prescaler to 1024 desu
    TIMSK0 |= _BV(OCIE0A);
    //  Enables compare match A interrupt
}

void init_adj(void){
    EICRA |= _BV(ISC01) | _BV(ISC11);
    // Sets INT0 and INT1 to detect falling edges.
    EIMSK |= _BV(INT0) | _BV(INT1);
    // Enables INT0 and INT1
}

void init_adc(void)
{
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
    // Writes to ADC_Enable and ADC_Prescaler is set to 64 to get 187.5kHz sample rate
    ADCSRA |= _BV(ADIE);
    // Sets ADC_Interrupt_Enable
    ADCSRA |= _BV(ADATE);
    ADCSRB |= _BV(ADTS1) | _BV(ADTS0);
    ADCSRA |= _BV(ADSC);
    // Sets ADC to Timer 0 Compare Match and starts the ADC
}

ISR(INT0_vect){OCR0A = ++count;}

ISR(INT1_vect){OCR0A = --count;}

ISR(ADC_vect){PINB |= _BV(PB7);}

void main(){
    DDRB = 0xFF;
    // set port bank b as outputs
    init_timer();
    init_adj();
    init_adc();
    sei();
    while(1);
}
└──────────────────────────────────────────────────────────────────────────────────────┘
