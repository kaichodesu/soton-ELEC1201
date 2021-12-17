#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 1
#define TERMINAL_WIDTH 60

void plotval(float a, int width){
    int xpos = round(a*width);
    // A int xpos is created as characters are discreet.
    // We round the sine value by the width to produce an approximation of the position.
    for(int i = 0; i < xpos; i++){
        printf(" ");
        // A for loop prints spaces until the desired x position is reached.
    }
    printf("*\n");
    // Once the x position is reached, we print an asterisk and end the line.
}

void main(){
    // Not like this program will ever return anything.
    unsigned long x = 0;
    // Creating a local unsigned long.
    float y = 0;
    // Creating a local float.
    while(1){
        ++x;
        // Increments x by 1 and sets x to that value.
        y = (sin(FREQ*x*(PI/180))/2)+0.5;
        // Sets Y to the value specified in the instructions.
        printf("%*lu  |%7.3f  | ", 20, x, y);
        // Prints x with a width 20 and prints y with a width of 7 with 3 decimal places.
        // We do not end the line here.
        plotval(y, TERMINAL_WIDTH);
        // Here the plotval() function is called.
    }
}
