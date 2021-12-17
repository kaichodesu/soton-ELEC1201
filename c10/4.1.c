#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t count = 0;

void init_timer(void){
    TCCR0A |= _BV(WGM01) | _BV(COM0A0);
    //  Sets to CTC mode
    TCCR0B |= _BV(CS12) | _BV(CS10);
    //  Sets prescaler to 1024 desu
    TIMSK0 |= _BV(OCIE0A);
    //  Enables compare match A interrupt
    ADCSRA |= _BV(ADSC);
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
    // Sets ADC to Timer 0 Compare Match and starts the ADC
}

ISR(INT0_vect){
    cli();
    ADCSRA &= ~_BV(ADSC);
    TCNT0 = 0x00;
    count++;
    for(int i = 0; i <= 8; i++){
        if(0x01 & (count >> i)){
            OCR0A |= 0x01 << i;
        }
    }
    sei();
    ADCSRA |= _BV(ADSC);
}

ISR(INT1_vect){
    cli();
    TCNT0 = 0x00;
    ADCSRA &= ~_BV(ADSC);
    count--;
    for(int i = 0; i <= 8; i++){
        if(0x01 & (count >> i)){
            OCR0A |= 0x01 << i;
        }
    }
    sei();
    ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect){PINB |= _BV(PB7);}

int main(){
    DDRB = 0xFF;
    // set port bank b as outputs
    init_timer();
    init_adj();
    init_adc();
    sei();
    while(1);
}
