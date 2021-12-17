#include <avr/io.h>
#include <util/delay.h>
#define _BV(bit) (1 << (bit))



int main() {
    DDRA = 0xFF;   //port a = output
    DDRC = 0x00;   //port c = input
    PORTC = 0xFF;  //enable pull ups
    const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    int i = 0;
    uint8_t lastA = 0b00000000;
    uint8_t lastB = 0b00000000;
    int dir = 0;
    while(1){
        PORTA = segments[i];

        lastA = (PINC & _BV(PC0));
        lastB = (PINC & _BV(PC1));
        // Save the current states for the inputs

        while(((PINC & _BV(PC0)) == 0) || ((PINC & _BV(PC1)) == 0)

        if(lastA == 0 && (PINC & _BV(PC0) != 0)){
            // Enters the loop once A changes
            if(lastB == 0){
                // If A changes to B, B was already on, thus we are going CCW
                dir = -1;
                i = i + dir;
                if(i == -1){
                    i = 9;
                }
                PORTA = segments[i];
            }
            else{
                dir = 1;
                i = i + dir;
                if(i == 10){
                    i = 0;
                }
                PORTA = segments[i];
            }
            _delay_ms(50);
        }


        //while((PINC & _BV(PC7)) == 0);
        //i = i + 1;
        //while((PINC & _BV(PC7)) != 0);
        //_delay_ms(100);

        /*while(((PINC & _BV(PC0)) == 0) || ((PINC & _BV(PC1)) == 0)){
            // while A OR B are 0, check for which updates first

            if((PINC & _BV(PC1)) != 0){
                dir = 1;
                i = i + dir;
                while((PINC & _BV(PC1)) != 0);
                // if B is 1, add one and wait until its 0
            }

            if((PINC & _BV(PC0)) != 0){
                dir = -1;
                i = i + dir;
                while((PINC & _BV(PC0)) != 0);
                // if Ais 1, minus one and wait until its 0
            }

            //while((PINC & _BV(PC0)) != 0);
        }*/
        /*
        if((PINC & _BV(PC1)) != 0){
            while(!(((PINC & _BV(PC1)) != 0) && ((PINC & _BV(PC0)) != 0)));
            dir = 1;
            i = i + dir;
            if(i == 10){
                i = 0;
            }
            while((PINC & _BV(PC1)) != 0);
            // if B is 1, add one and wait until its 0
        }
        else {}

        if((PINC & _BV(PC0)) != 0){
            //while((PINC & _BV(PC1)) == 0);
            while(!(((PINC & _BV(PC1)) != 0) && ((PINC & _BV(PC0)) != 0)));
            dir = -1;
            i = i + dir;
            if(i == -1){
                i = 9;
            }
            while((PINC & _BV(PC0)) != 0);
            // if Ais 1, minus one and wait until its 0
        }
        else {} */
        /*while((PINC & _BV(PC1)) == 0){
            if((PINC & _BV(PC0)) != 0){
                dir = -1;
                i = i + dir;
            }
            while((PINC & _BV(PC1)) != 0);
        }*/
    }
    return 0;
}


