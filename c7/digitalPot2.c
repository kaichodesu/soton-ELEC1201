/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "spi.h"

void init_pot(void)
{
    // Initialise Pots as 0, This is a 16 bit command so we send two 8 bit-byte packets.

    spi_tx(0b00000100);
    // Selects Pot A
    spi_tx(0b00000000);
    // Sets Pot A to 0

    spi_tx(0b00001100);
    // Selects Pot B
    spi_tx(0b00000000);
    // Sets Pot B to 0;
}

void decXpot(void)
{
    // Decreasing pots requires an 8 bit command
    spi_tx(0b00100000);
}

void incXpot(void)
{
    spi_tx(0b00010000);
}

void decYpot(void)
{
    spi_tx(0b00101000);
}

void incYpot(void)
{
    spi_tx(0b00011000);
}

void setXpot(uint8_t x)
{
    spi_tx(0b00000100);
    // Selects Pot A
    spi_tx(x);
    // Sets Pot A to uint8_t x
}

void setYpot(uint8_t y)
{
    spi_tx(0b00001100);
    // Selects Pot B
    spi_tx(y);
    // Sets Pot A to uint8_t y
}

int main(){
    init_pot();
    while(1){
        for(int i = 0; i < 255; i++){
            incXpot();
            incYpot();
        }
        setXpot(0b00000000);
        setYpot(0b00000000);
    }
    return 0;
}



























