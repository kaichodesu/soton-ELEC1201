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
#define POP_SIZE     50
#define MAX_GEN    10000
#define MUTATION_STRENGTH  0.5
#define RND_INIT           2
#define TRIALS 5
#define COMPARE_SIZE 3
#define FANS 5

unsigned long cpufreq = 2300000000;
float rnd();

void wait(float time){
    for(unsigned long long i = 0; i < (cpufreq*time); i++){}
}

void initpop(float *pop, int size){
    for(int i = 0; i < size; i++){
        pop[i] = rnd();
    }
}


void fans(float parent, float mutst, float *pop, int fannum){
    for(int i = 0; i < fannum; i++){
        pop[(int)floor(POP_SIZE * rnd())] = ( parent + ((1-parent)*(mutst * 2 * (rnd() - 0.5))) );
    }
}
// Randomly spreads fannum fans with mutst variations on the parent into the population

float rnd(){
    return rand()/(float) RAND_MAX;
}

float arrayavg(float *pop, int size){
    float sum = 0;
    for(int i = 0; i < size; i++){
        sum += pop[i];
    }
    sum /= size;
    return sum;
}

int main(){
    float population[POP_SIZE];
        initpop(population, POP_SIZE);
        int   gen = 0;
        float triple[COMPARE_SIZE];
        float triplediff[COMPARE_SIZE+1];
        while(gen <= 100){
            for(int i = 0; i < COMPARE_SIZE; i++){
                triple[i] = population[(int)floor(POP_SIZE * rnd())];
            }
            // choosing randoms from the population
            triplediff[0] = 2*triple[0]-triple[1]-triple[2];
            triplediff[1] = 2*triple[1]-triple[0]-triple[2];
            triplediff[2] = 2*triple[2]-triple[0]-triple[1];
            // summing their differences (yes i do regret using an array, now i cant have a variable group size as i was planning at first)
            for(int i = 0; i < COMPARE_SIZE; i++){
                if(triplediff[COMPARE_SIZE+1] < triplediff[i]){
                    triplediff[COMPARE_SIZE] = i;
                }
            }
            // setting the second to last value of the triplediff[] array to the array position in triple[] that has the fittest member.
            //for(int i = 0; i < POP_SIZE; i++){
            //    printf("%d, %f\n", gen, population[i]);
            //}
            printf("%d, %f\n", gen, arrayavg(population, POP_SIZE));
            // i am going to use the average of the array instead so i can fit the readings on my chart.
            gen++;
            fans(triple[(int)triplediff[COMPARE_SIZE]], MUTATION_STRENGTH, population, FANS);
            // now we spread in some fans
            //wait(0.01);
        }
        printf("\n");
    }

