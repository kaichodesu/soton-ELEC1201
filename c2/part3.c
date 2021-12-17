#include <stdio.h>
#include <math.h>
#define PI 3.14
#define FREQ 5
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
