========================================================================================
Digital Input and Output: C7 18/11/21

╔════════════╗
║Preparation:║
╚════════════╝

1)  UART stands for Universal Asynchronous Receiver-Transmitter

2)  UART supports baud rates up to 2M, while the exact value does not technically matter as long as all the devices are using the same baud rate, the standard baud rates are usually some value of (2^n * 16).

3)  A UART packet has no set length, however, there is a data frame limit of 384 bits (excluding the parity bit).  In the case of sending an 8-bit ASCII character, as long as both devices are set up to accept data frames of length 8 bits, the packet will consist of 11 or 12 bits:

      1    |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |    11    |      12
 Start bit | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 | P1 | Stop Bit | (Stop Bit 2)

4)  As UART is not a data bus, one UART interface can only support communication between two devices.

5)  SPI stands for Serial Peripheral Interface

6)  SPI supports clock rates up to 100MHz

7)  As SPI is a clock synchronous communication protocol, there is no need for a start or stop bit like there is in UART.  A single packet can consist of the full 8 bits being completely used to transfer data.

8)  SPI has no theoretical limit to the number of devices that can be connected.

9)  I2C stands for Inter-Integrated Circuit and is a communication protocol intended for communication between ICs (no surprise)

10) Speed is typicaly around 400kbits/s, but can reach as high as 3.14Mbits/s, however, I2C is very succeptible to external EMI thus speed and distance can be severely limited depending on the application.

11) As I2C supports up to 127 devices, there are 128 addresses which must be accounted for by 7 bits after the start bit.  After the start bit the master must send a bit to determine whether it is writing to the slave or reading from the slave.  After which there is a pause (acknowledge bit) and then the single byte packet is sent.  After one byte, there is another ACK bit.  In this case as we are only sending one ASCII character there will be no data packets sent after the ACK bit, so we send a stop bit.  In total this resulted in 20 bits of data being sent:

Start Bit | 0 1 2 3 4 5 6 | R/W | ACK | 0 1 2 3 4 5 6 7 | ACK | Stop Bit

12) 128 devices including the master.

========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Using the UART as a debugging aid for embedded programming"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#define DEBUG_BAUD  9600

int main() {
    init_debug_uart0();
    // initialise UART
    DDRA = 0xFF;
    const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    int i = 0;
    while(1){
        PORTA = segments[i];
        fprintf(stdout, "%d", i);
        // debug.h takes the stdout stream and outputs via UART
        i++;
        _delay_ms(1000);
        if(i == 10){
            i = 0;
        }
    }
    return 0;
}
└──────────────────────────────────────────────────────────────────────────────────────┘

On the terminal, we can see that the microcontroller outputs a constant stream of integers counting from 0 to 9 in a loop, with a 1 second gap between each post.










┌──────────────────────────────────────────────────────────────────────────────────────┐
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
└──────────────────────────────────────────────────────────────────────────────────────┘

3.2 ["Connecting a digital potentiometer using the SPI"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "spi.h"

void init_pot(void)
{
    // Initialise Pots as 0, This is a 16 bit command so we send two 8 bit-byte packets.
    init_spi_master();
}

void decXpot(void)
{
    // Decreasing pots requires an 8 bit command
    spi_tx(0b00001000);
}

void incXpot(void)
{
    spi_tx(0b00000100);
}

void decYpot(void)
{
    spi_tx(0b00011000);
}

void incYpot(void)
{
    spi_tx(0b00010100);
}

void setXpot(uint8_t x)
{
    spi_tx(0b00000000);
    // Selects Pot A
    spi_tx(x);
    // Sets Pot A to uint8_t x
}

void setYpot(uint8_t y)
{
    spi_tx(0b00010000);
    // Selects Pot B
    spi_tx(y);
    // Sets Pot A to uint8_t y
}

int main(){
    init_pot();
    setXpot(0b00000000);
    setYpot(0b00000000);
    while(1){
        for(int i = 0; i < 255; i++){
            incXpot();
            incYpot();
        }
    }
    return 0;
}
└──────────────────────────────────────────────────────────────────────────────────────┘




