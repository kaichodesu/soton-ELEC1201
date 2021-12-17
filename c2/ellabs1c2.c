========================================================================================
Functions and Control Flow: C2 14/10/21

╔════════════╗
║Preparation:║
╚════════════╝

["Numerical Data Types"]
// https://docs.microsoft.com/en-us/cpp/c-language/storage-of-basic-types

Declaration    │ Size                         │ Format Specifier
───────────────┼──────────────────────────────┼─────────────────
int            │ 4 bytes                      │ %d
unsigned int   │ 4 bytes                      │ %u
short          │ 2 bytes                      │ %hd
unsigned short │ 2 bytes                      │ %hu
long           │ 8 bytes (only for x64 ISA)   │ %ld
unsigned long  │ 8 bytes (only for x64 ISA)   │ %lu
// The size depends on the compiler settings adjusted for the platform being compiled for

These different types exist for efficient memory management, as there is no reason to dedicate so many bytes to a value when you do not need to, especially for embedded systems that only have a few kilobytes of ram.

'signing' of a variable is how negative numbers are represented.  By default (depends on the compiler settings), all the variables are signed, allowing for a positive or negative number with a max size of half the range.  i.e. 4 bits would allow for 256 different values, but results in a signed range of -128 to 127 as there are only 256 different states it can take.

["Fixed Width Values"]
// http://www.cplusplus.com/reference/cstdio/printf/

printf() can be instructed to print with a fixed width by adding an asterisk to the format specifier (this asterisk can also just be replaced by an number representing the width if the width does not need to be changed), and also adding an argument.  The value for the fixed width must be declared as int if using this method.

┌────────────────────────────────────────────────┐
#include <stdio.h>

int width = 20;
unsigned long increasingNumber = 0;

void main(){
    for(int i = 0; i < 1000; ++i){
        printf("%*lu", width, increasingNumber);
        ++increasingNumber;
    }
}
└────────────────────────────────────────────────┘

["Endless Loops"]

A loop can very easily be created using a while() loop.

┌────────────────────────────────────────────────┐
void main(){
    while(1){
        dosomething();
    }
}
└────────────────────────────────────────────────┘

["C Math"]

// https://www.cplusplus.com/reference/cmath/
By including math.h, you gain access to functions such as sin(), cos(), trunc(), etc, which allow you to perform various mathematical operations in your program.

a = (sin(FREQ*b*(PI/180))/2)+0.5;
will "give you the sine of a value scaled to the range of 0 to 1"
It first converts variable b to radians by multiplying it by pi/180, there is also a scalar FREQ which increases the rate at which b changes to increase the angular velocity.
After this, the sin() function converts this to a value between -1 and 1, which is then scaled down to -0.5 and 0.5.  Then, it is offset by 0.5 to move the range from 0 to 1.

["plotval()"]

Requirements:
>Return nothing
>Print * with a position proportional to an variable relative to a constant.

┌──────────────────────────────────────────┐
void plotval(float yvalue, int width){
    int xpos = floor(a*width);
    for(int i = 0; i < (xpos + 1); i++){
        printf(" ");
    }
    printf("*\n");
}
└──────────────────────────────────────────┘

========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Part 1"]

┌──────────────────────────────────────────┐
#include <stdio.h>

void main(){                                // The program wont ever return anything
    unsigned long x = 0;                    // Creating a local unsigned long
    while(1){                               // A loop that will run while 1 = 1
        ++x;                                // Increments x by 1
        printf("%*lu\n", 20, x);            // Prints x with a fixed width of 20
    }
}
└──────────────────────────────────────────┘


┌──────────────────────────────────────────┐
#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 1

void main(){
    unsigned long x = 0;                    // Creating a local unsigned long
    float y = 0;                            // Creating a local float
    while(1){                               // A loop that will run while 1 = 1
        ++x;                                // Increments x by 1
        y = (sin(FREQ*x*(PI/180))/2)+0.5;   // Sets y to the values specified
        printf("%*lu  |%7.3f\n", 20, x, y); // Prints y with width 7 and 3 dp
    }
}
└──────────────────────────────────────────┘

3.2 ["Part 2"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
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
└──────────────────────────────────────────────────────────────────────────────────────┘

3.3 ["Part 3"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 3
#define TERMINAL_WIDTH 100

void plotval(float sineInput, int plottingWidth, short length, short freq, int line);
// Adding a few more arguments to make the plot more customisable

void main(){
    unsigned long x = 0;
    float y = 0;
    while(1){
        ++x;
        y = (sin(FREQ*x*(PI/180))/2)+0.5;
        printf("%*lu  |%7.3f  | ", 20, x, y);
        plotval(y, TERMINAL_WIDTH, 5, 10, x);
    }
}

void plotval(float a, int width, short len, short spa, int ln){
    short xpos = round(a*width);
    if(!(ln % spa == 0)){
        // When the spacing leaves a remainder, we print as usual
        for(int i = 0; i < (xpos + len); i++){
            printf(" ");
        }
    }
    else {
        // When the spacing divides perfectly into the line number, we print the gridline
        for(int i = 0; i < len; i++){
            printf("-");
        }
        for(int i = 0; i < xpos; i++){
            printf(" ");
        }
    }
    printf("*\n");
}
└──────────────────────────────────────────────────────────────────────────────────────┘

["Controlling Execution Speed"]

Assuming each instruction takes one clock cycle (which is not true for modern CPUs with high IPC counts), we could perhaps implement a delay using a for loop that will use the frequency of the processor it is running on to loop a pointless instruction until the desired amount of time has been reached.  Perhaps something like:

unsigned long cpufreq = 2300000000;
// On the verge of useable as an unsigned long would only let you reach 4.3GHz nowadays
// Fortunately I am using an older Xeon E5 2699v3 so the clock speed is much lower
// In reality I would have to set this value lower as the program will only run on one
// thread and modern CPUs would downclock for light loads like these.
float time = 1;
// In seconds
for(unsigned long long i = 0; i < (cpufreq*time); i++){}
// A long long will probably give you enough time (4294967297 seconds at least)

Testing it out:

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 3
#define TERMINAL_WIDTH 100

void plotval(float sineInput, int plottingWidth, short length, short freq, int line);
unsigned long cpufreq = 2300000000;
float time = 0.005;

void main(){
    unsigned long x = 0;
    float y = 0;
    while(1){
        ++x;
        y = (sin(FREQ*x*(PI/180))/2)+0.5;
        printf("%*lu  |%7.3f  | ", 20, x, y);
        plotval(y, TERMINAL_WIDTH, 5, 10, x);
        for(unsigned long long i = 0; i < (cpufreq*time); i++){}
    }
}

void plotval(float a, int width, short len, short spa, int ln){
    short xpos = round(a*width);
    if(!(ln % spa == 0)){
        for(int i = 0; i < (xpos + len); i++){
            printf(" ");
        }
    }
    else {
        for(int i = 0; i < len; i++){
            printf("-");
        }
        for(int i = 0; i < xpos; i++){
            printf(" ");
        }
    }
    printf("*\n");
}
└──────────────────────────────────────────────────────────────────────────────────────┘

The program actually works and delays the plotting enough so that you can see the sine graph being drawn out.

4 ["Optional Additional Work"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 5
#define TERMINAL_WIDTH 100

/*
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
We don't need this stackexchange answer anymore */

// \x1B is the escape key here
#define TEST "\x1B[38;5;28m"
// We can use 8-bit colours here instead of the ones in the stackexchange answer
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// 38;5;⟨n⟩m selects foreground colours
// 48;5;⟨n⟩m selects background colours

void plotval(float sineInput, int plottingWidth, short length, short freq, int line);
unsigned long cpufreq = 2300000000;
float time = 0.005;
int rainbow[] = {196, 202, 220, 40, 27, 99, 165};
int colour = 0;
// Creating an array of the correct ROYGBIV colours of the rainbow so we can scroll through them later
// Later we will use the colour variable to count through the array

void main(){
    unsigned long x = 0;
    float y = 0;
    while(1){
        ++x;
        y = ((sin(FREQ*x*(PI/180))/**sin(3*FREQ*x*(PI/180))*/)/2)+0.5;
        // printf("\x1B[38;5;%dm %*lu  |%7.3f  | ", 29, 20, x, y);
        // Here I discovered you could use the escape code with variables so I realised I could switch through them with the array
        printf("%*lu  |%7.3f  | ", 20, x, y);
        plotval(y, TERMINAL_WIDTH, 5, 10, x);
        for(unsigned long long i = 0; i < (cpufreq*time); i++){}
    }
}

void plotval(float a, int width, short len, short spa, int ln){
    short xpos = round(a*width);
    if(!(ln % spa == 0)){
        for(int i = 0; i < len; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
        }
        for(int i = 0; i < xpos; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
        }
    }
    else {
        for(int i = 0; i < len; i++){
            printf("\x1B[48;5;%dm-" RESET, rainbow[colour]);
        }
        for(int i = 0; i < xpos; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
        }
    }
    /*switch(ln % 10){
        case 1:
            printf(RED"*\n");
            break;
        case 2:
            printf(GRN"*\n");
            break;
        case 3:
            printf(YEL"*\n");
            break;
        case 4:
            printf(BLU"*\n");
            break;
        case 5:
            printf(MAG"*\n");
            break;
        case 6:
            printf(CYN"*\n");
            break;
        case 7:
            printf(WHT"*\n");
            break;
        case 8:
            printf(YEL"*\n");
            break;
        case 9:
            printf(YEL"*\n");
            break;
        case 0:
            printf(YEL"*\n");
            break;
        default:
            printf("*\n");
    }*/
    // Instead of this very clunky method we can use something more streamlined.
    printf("*\n" RESET);
    ++colour;
    if(colour == 7){
        colour = 0;
    }
}
└──────────────────────────────────────────────────────────────────────────────────────┘

["Final Code"] //-ish

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 5
#define PLOT_WIDTH 100
// Width I leave for my graph
#define TERMINAL_WIDTH 200
// Width of my terminal
#define INFO_WIDTH 35
// Width of the x and y values
#define TEST "\x1B[38;5;28m"
// We can use 8-bit colours here instead of the ones in the stackexchange answer
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// 38;5;⟨n⟩m selects foreground colours
// 48;5;⟨n⟩m selects background colours

void plotval(float sineInput, int plottingWidth, short length, short freq, int line, float stars);
unsigned long cpufreq = 2300000000;
float time = 0.005;
int rainbow[] = {196, 202, 220, 40, 27, 99, 165};
int colour = 0;
// Creating an array of the correct ROYGBIV colours of the rainbow so we can scroll through them later
unsigned long long tick = 0;
// Ticks used to space out the stars

void main(){
    unsigned long x = 0;
    float y = 0;
    float y2 = 0;
    while(1){
        ++x;
        y = ((sin(FREQ*x*(PI/180))/**sin(3*FREQ*x*(PI/180))*/)/2)+0.5;
        // printf("\x1B[38;5;%dm %*lu  |%7.3f  | ", 29, 20, x, y);
        // We can use vary the colour with a random variable
        printf(WHT"\x1B[48;5;232m%*lu  |%7.3f  | ", 20, x, y);
        y2 = ((sin(500*x*(PI/180)))/2)+0.5;
        // A really fast sine wave is basically random right
        plotval(y, PLOT_WIDTH, 5, 10, x, y2);
        for(unsigned long long i = 0; i < (cpufreq*time); i++){
            ++tick;
        }
    }
}

void plotval(float a, int width, short len, short spa, int ln, float b){
    short xpos = round(a*width);
     if(!(ln % spa == 0)){
        for(int i = 0; i < len; i++){
            printf(" ");
            //  Just printing empty characters where the line would be
        }
        for(int i = 0; i < xpos; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
            //  Now we print the coloured bars
        }
    }
    else {
        for(int i = 0; i < len; i++){
            printf("-");
            //  The line printed as usual
        }
        for(int i = 0; i < xpos; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
            //  More coloured bars
        }
    }
    printf("\x1B[48;5;17m" RESET);
    // This gives the end of the bar a dark blue "night sky" colour.
    // It was here that I realised this looked very familiar.
    // Perhaps it is time to add stars.
    // Stars would have to be placed at random between the end of the bar and the end of the terminal.
    // A random number of them spaced proportionally between that space.
    // However not all lines should have stars.
    // Maybe we can use the clock we inadvertantly made earlier to space out stars.
    // Ok this didn't work so maybe we use another sin() function with a really high frequency
    if(tick % 7 == 0){
        for(int i = 0; i < round(b*(TERMINAL_WIDTH-INFO_WIDTH-xpos-len)); i++){
            printf("\x1B[48;5;17m "RESET);
        }
        printf(WHT "\x1B[48;5;17m★\n"RESET);
    }
    else {
        printf("\x1B[48;5;17m\n" RESET);
    }
    ++colour;
    if(colour == 7){
        colour = 0;
    }
}
└──────────────────────────────────────────────────────────────────────────────────────┘

Now the code produces a rainbow sin graph with a dark blue background with white stars placed randomly on that background.

┌────────────────────────────────────────────────┐
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    printf("%f\n", ((double)rand () / RAND_MAX));
    return 0;
}
└────────────────────────────────────────────────┘

I was trying this earlier to produce random numbers however it wasn't working as at the time I didn't know I needed to include the stdlib header, but this can be used instead of the brute force sin function to produce the random positions for the stars.

　 ∧∧    ∩
　( ´∀｀)/　∧∧   ∩
 ⊂　　 ﾉ　( ´∀｀)/
　(つ ﾉ　　⊂　　 ﾉ　　  ∧∧   ∩
　 (ノ　　　(つ ﾉ 　　( ´∀｀)/
            (ノ　　  ⊂　　 ﾉ
　　　　　　　　　　　　 (つ ﾉ　  ∧ ∧  ∩
　　　　　　　　　　　　　(ノ　　( ´∀｀)/
　　　　　　　　　　　　　　　 ＿| つ／ヽ-、＿
　　　　　　　　　　　　　　／　 └-(＿＿＿_／
　　　　　　　　　　　　　　 ￣￣￣￣￣￣￣
                                           ／￣￣￣￣￣
                             ＜⌒／ヽ＿＿＿ ＜ もう寝るわ..
　　　　　　　　　　　　　　　　／＜_/＿＿＿＿／  ＼＿＿＿＿＿
　　　　　　　　　　　　　　　　￣￣￣￣￣￣￣
And now my work here is done.
