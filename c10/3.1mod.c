#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t count = 0;
volatile const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};

void init_timer(void){
    //  We want clear timer on compare match (comparing to a specific time)
    TCCR1A |= 0;
    TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10);
    //  Enables CTC, TOP = OCRA and sets prescaler to 1024 desus
    TIMSK1 |= _BV(OCIE1A);
    //  Enables compare match A interrupt
}

ISR(TIMER1_COMPA_vect){
    count++; if(count >= 10){count = 0;}
    PORTA = segments[count];
}

int main() {
    DDRA = 0xFF;
    OCR1A = 11719;
    init_timer();
    sei();
    while(1){}
    return 0;
}
