// evol.c
// ELEC1201 Lab C3: Operators and Arrays
// Evolutionary Computing
// KPZ 2018, MIT License
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define EQUATION   y = pow(x,3) - 10
#define Y_TARGET   0.0
#define EPSILON    0.0001
#define POP_SIZE     500
#define MAX_GEN    10000
#define MUTATION_STRENGTH  0.9
#define RND_INIT           2
#define TRIALS 5

unsigned long cpufreq = 2300000000;
int init[] = {1, 2, 3, 4, 5};
// random seed array
float rnd();

void wait(float time){
    for(unsigned long long i = 0; i < (cpufreq*time); i++){}
}

void initpop(float *pop, int size){
    for(int i = 0; i < size; i++){
        pop[i] = rnd();
    }
}

void offspring(float parent, float mutst, float *pop, int size){
    pop[0] = parent;
    for(int i = 1; i < size; i++){
        pop[i] = ( parent + (mutst * 2 * (rnd() - 0.5)) );
    }
}

float rnd(){
    return rand()/(float) RAND_MAX;
}

int main(){
    float population[POP_SIZE];
    for(int i = 0; i < TRIALS; i++){
        srand(init[i]);
        initpop(population, POP_SIZE);
        int   gen = 0;
        float best_ifit = FLT_MAX;
        float best;
        float x, y;
        float ifit;
        float fit;
        printf("RND_INIT = %d\n", init[i]);
        while((best_ifit > fabs(Y_TARGET - EPSILON)) && (gen < MAX_GEN)){
            for(int i = 0; i < POP_SIZE; i++){
                x = population[i];
                EQUATION;
                ifit = fabs(y - Y_TARGET);
                if( ifit <= best_ifit ){
                    best_ifit = ifit;
                    best = x;
                }
            }
            x = best;
            EQUATION;
            if(best_ifit > 0){
                fit = 1/best_ifit;
            }
            else{
                fit = -1;
            }
            printf("%d, %f\n",gen++, fit);
            offspring( best, MUTATION_STRENGTH, population, POP_SIZE);
        }
        printf("\n");
    }
}
