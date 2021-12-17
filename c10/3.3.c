#include <avr/io.h>
#include <avr/interrupt.h>

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
    PINC |= _BV(PC0);
    PINC |= _BV(PC0);
    PINC |= _BV(PC0);
    // Denotes the start of the packet.
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

ISR(INT0_vect){count++; write(count);}

ISR(INT1_vect){count--; write(count);}

int main(){
    init();
    sei();
    while(1);
}
