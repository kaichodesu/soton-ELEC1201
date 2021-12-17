#include <avr/io.h>
#include <util/delay.h>
#define _BV(bit) (1 << (bit))

int main() {
    DDRA = 0xFF;   //port a = output
    DDRC = 0x00;   //port c = input
    PORTC = 0xFF;  //enable pull ups
    const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    int i = 0;
    while(1){
        PORTA = segments[i];
        while((PINC & _BV(PC7)) == 0);
        i = i + 1;
        while((PINC & _BV(PC7)) != 0);
        // _delay_ms(1000);
        if(i == 10){
            i = 0;
        }
    }
    return 0;
}


