#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#define DEBUG_BAUD  9600

int main() {
    init_debug_uart0();
    DDRA = 0xFF;
    const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    int i = 0;
    char cont = 'a';
    while(1){
        PORTA = segments[i];
        fprintf(stdout, "%d", i);
        i++;
        _delay_ms(1000);
        if(i == 10){
            fprintf(stderr, "\n\rCount overflow\n\r");
            fprintf(stdout, "Press Y to continue...\n\r");
            while(!(cont == 'y')){
                cont = fgetc(stdin);
            }
            cont = 'a';
            i = 0;
        }
    }
    return 0;
}


