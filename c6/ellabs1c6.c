========================================================================================
Digital Input and Output: C6 11/11/21

╔════════════╗
║Preparation:║
╚════════════╝

1)  The required header is avr/io.h
    The port "x" can be configured as an output by using setting DDR"x" to an 8 bit value whose bits coincide with the states of the 8 pins on the port.  So for example, to set the entirety of port A as an output, you would use the command:

DDRA = 0xFF;
DDRA = 0b11111111;

2)  I = 10mA
    Source Voltage = 3v3
    Forward Voltage = 2v2 thus resistance per segment should be 110 Ohms.

3)  As the voltage remains the same, if only one resistor is used on the common ground,
    then as more and more LEDs are lit up, the brightness will decrease as the current will have to be shared between LEDs.

4)  USB 1.0/2.0 can provide 2.5W of power.  When all segments are lit, the total current d
    draw with nominal current of 10mA per segment will be 70mA, we can round that up to 100mA.  This means we will be using 330mW of power at 3.3V, which is far below the power delivery limits of the USB standard we are using.  100mA is also well within the limits of the linear voltage regulator we are using to decrease the voltage from 5v to 3.3v.  At most the thermal output would be 5 - 3.3 = 1.7, * 0.1 = 17mW of heat.

5)  0 = 0b11111100
    1 = 0b01100000
    2 = 0b11011010 11011010
    3 = 0b11110010
    4 = 0b01100110
    5 = 0b10110110
    6 = 0b10111110
    7 = 0b11100000
    8 = 0b11111110
    9 = 0b11110110 11110110

const uint8_t segments[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B}

6)  To set the pins on a port as inputs, we use the same instructions as before, but
    instead of setting the desired pins high, we set them low, so to set all 8 pins on port A as inputs, we can issue:

DDRA = 0x00;

7)  The internal pull up resistor stops the power supply being shorted out when the pin is
    pulled down to ground.  The internal pull up resistors can be enabled for port A for example, with command:

PORTA = 0xFF;

    The value of this internal pull up resistors range from around 20k to 50k ohms (stated in the 644p datasheet)

8)  Any signal below 0.99V will be interpreted as LOW
    Any signal above 1.98V will be interpreted as HIGH

9)  Switch bounce is a mechanical phenomenon which occurs when the metal contacts within
    a switch resonate after being pressed, causing multiple switching cycles to occur on a single switch press, albeit for a few microseconds.

10) Switch debouncing can be implemented in many different ways, in this example we will
    look at two, using an RC low pass filter and using simple wait commands in software.

    "RC Low Pass Filter"
    Using this technique requires extra passive components.  While it can effectively mitigate the high frequency switching from the bounce, it also introduces a lot of input delay depending on the implementation.  For example, when transitioning from HIGH to LOW, you must hold down the switch for as long as it takes for the capacitor to discharge to below 0.99V from 5V for a low input to be registered by the microcontroller.  Similarly, you will have to release the switch for long enough for a LOW to HIGH transition for the capcitor to charge up above 1.98V.  However, this can be somewhat mitigated by choosing capacitor values carefully.

    "Software wait"
    Using software wait functions to debounce removes the input latency, however, it produces software latency, as code execution must be paused while the single thread waits for the switch debounce to complete.  This can also reduce the frequency at which the switch can be pressed, and slow down code execution, however, once again this can be mitigated somewhat by tuning the delay to the specific switches bounce.

11) The rotary encoder we are using is a quadrature rotary encoder, which means there are
    two bits which are turned on and off in an order dependent on the direction of rotation.  By reading the order of switching we can determine the direction of rotation.

12) The speaker has an impedance of 100 ohms.  Using the minimum value of 80 ohms we can
    determine that at 3v3, the current will be 41mA in the absolute worst case scenario.  As the microcontroller can provide 40mA per pin, we will most likely be fine.

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Digital Output"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRA = 0xFF;
    const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    int i = 0;
    while(1){
        PORTA = segments[i];
        i++;
        _delay_ms(1000);
        if(i == 10){
            i = 0;
        }
    }
    return 0;
}
└──────────────────────────────────────────────────────────────────────────────────────┘

3.2 ["Digital Input"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
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

└──────────────────────────────────────────────────────────────────────────────────────┘

When the switch is pressed, the counter goes up by multiple values rather than just one.

3.3 ["Debounce"]

Hardware Debounce is done with an RC filter.

Software Debounce is below:
┌──────────────────────────────────────────────────────────────────────────────────────┐
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
        _delay_ms(100);
        while((PINC & _BV(PC7)) != 0);
        if(i == 10){
            i = 0;
        }
    }
    return 0;
}
└──────────────────────────────────────────────────────────────────────────────────────┘

3.4 ["Rotary Encoder"]

CW
00 = 0
10 = 2
11 = 3
01 = 1

CCW

00 = 0
01 = 1
11 = 3
10 = 2

┌──────────────────────────────────────────────────────────────────────────────────────┐
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
└──────────────────────────────────────────────────────────────────────────────────────┘















