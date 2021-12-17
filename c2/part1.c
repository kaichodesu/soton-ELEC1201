#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 1

void main(){                                      // Not like this program will ever return anything
    unsigned long x = 0;                          // Creating a local unsigned long
    float y = 0;                                  // Creating a local float
    while(1){                                     // A loop that will run while 1 = 1 i.e forever
        ++x;                                      // Increments x by 1 and sets x to that value
        y = (sin(FREQ*x*(PI/180))/2)+0.5;         // Sets Y to the value specified in the instructions
        printf("%*lu  |%7.3f\n", 20, x, y);       // Prints y with a width of 7 with 3 decimal places
    }
}
