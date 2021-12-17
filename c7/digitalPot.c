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
    int i = 0;
    while(1){
        for(i = 0; i < 255; i++){
            incXpot();
            incYpot();
        }
        i = 0;
        setXpot(0b00000000);
        setYpot(0b00000000);
    }
    return 0;
}



























