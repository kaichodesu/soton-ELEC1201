#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14
#define FREQ 5
#define PLOT_WIDTH 100
#define TERMINAL_WIDTH 200
#define INFO_WIDTH 35
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void plotval(float sineInput, int plottingWidth, short length, short freq, int line);
unsigned long cpufreq = 2300000000;
float time = 0.005;
int rainbow[] = {196, 202, 220, 40, 27, 99, 165};
int colour = 0;

void main(){
    unsigned long x = 0;
    float y = 0;
    while(1){
        ++x;
        y = ((sin(FREQ*x*(PI/180)))/2)+0.5;
        printf(WHT"\x1B[48;5;232m%*lu  |%7.3f  | ", 20, x, y);
        y2 = ((sin(500*x*(PI/180)))/2)+0.5;
        plotval(y, PLOT_WIDTH, 5, 10, x);
        for(unsigned long long i = 0; i < (cpufreq*time); i++){}
    }
}

void plotval(float a, int width, short len, short spa, int ln){
    short xpos = round(a*width);
     if(!(ln % spa == 0)){
        for(int i = 0; i < len; i++){
            printf(" ");
        }
        for(int i = 0; i < xpos; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
        }
    }
    else {
        for(int i = 0; i < len; i++){
            printf("-");
        }
        for(int i = 0; i < xpos; i++){
            printf("\x1B[48;5;%dm " RESET, rainbow[colour]);
        }
    }
    printf("\x1B[48;5;17m" RESET);
    ++colour;
    if(floor(((double)rand () / RAND_MAX)*10) % 7 == 1){
        for(int i = 0; i < round(((double)rand () / RAND_MAX)*(TERMINAL_WIDTH-INFO_WIDTH-xpos-len)); i++){
            printf("\x1B[48;5;17m "RESET);
        }
        printf(WHT "\x1B[48;5;17m★\n"RESET);
    }
    else {
        printf("\x1B[48;5;17m\n" RESET);
    }
    if(colour == 7){
        colour = 0;
    }
}
