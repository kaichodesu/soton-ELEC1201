// evol.c
// ELEC1201 Lab C3: Operators and Arrays
// Evolutionary Computing
// KPZ 2018, MIT License
//
// Compile with math library:
//    gcc evol.c -lm -o evol


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define EQUATION   y = pow(x,3) - 10
// x^2 - 4
#define Y_TARGET   0.0

#define EPSILON    0.0001

#define POP_SIZE     100
#define MAX_GEN    10000

#define MUTATION_STRENGTH  0.1
#define RND_INIT           3


unsigned long cpufreq = 2300000000;
void wait(float time){
    for(unsigned long long i = 0; i < (cpufreq*time); i++){}
}
// the same wait function I made in c2 to make reading and debugging easier desu

void printheader(void);
float rnd(); // Random values 0.0 to 1.0

void initpop(float *pop, int size){
    for(int i = 0; i < size; i++){
        // pop[100] is the null value marking the end of the array.
        pop[i] = rnd();
        // printf("pop[%d] = %f\n", i, pop[i]);
        // wait(0.001);
    }
}
// *pop is a pointer to the memory location for the already initialised array population[], thus we can write into it with a for loop that sweeps through 0 and i, with i being set to a max value of the length of the previously defined array population[] B)

void offspring(float parent, float mutst, float *pop, int size){
    pop[0] = parent;
    // setting the first value of the array to the best value determined last time.
    for(int i = 1; i < size; i++){
        pop[i] = ( parent + (mutst * (rnd() - 0.5)) );
        // printf("pop[%d] = %f\n", i, pop[i]);
        // wait(0.001);
    }
}

int main(){
    float population[POP_SIZE];
    // Creates an float array of size POP_SIZE
    int   gen = 0;
    // Generation number
    float best_ifit = FLT_MAX;  // worst possible
    float best;
    float x, y;
    float ifit;   // inverse fitness

    srand(RND_INIT);
    initpop(population, POP_SIZE);
    printheader();

    int i;

    while((best_ifit > fabs(Y_TARGET - EPSILON)) && (gen < MAX_GEN)){
        printf("fabs(y) = %f, fabs(Y_TARGET - EPSILON) = %f\n", fabs(y), fabs(Y_TARGET - EPSILON));

        for(i=0; i < POP_SIZE; i++){
            // "natural selection"
            x = population[i];
            // sets x to each value of the array and tests it
            EQUATION;  // y = f(x)
            // that positions x is manipulated and then set to y
            ifit = fabs(y - Y_TARGET);
            // as y - Y_TARGET can be negative we take the abs
            printf("x= %f  =>  y=  %+f,    ifit = %f\n", x, y, ifit);
            // we print the x value and the resultant y value and then its fitness
            // wait(0.005);
            // Is there a better one?
            if( ifit <= best_ifit ){
                best_ifit = ifit;
                best = x;
                // best_ifit starts at a terrible value, however, if the new ifit is better than the previous best, we set the best_ifit to the current ifit
            }
        }
        x = best;
        // now the iteration is done, we can set the x value to the best one found in the for loop B)
        EQUATION;  // y = f(x)
        // run the x value through the equation
        printf("Generation %4d with best solution:  x= %f --> f(x)= %f\n\n",
                   gen++, best, y);
        // wait(0.1);
        // whats the point of this printf when you cant even read it without a pause ;>>
        offspring( best, MUTATION_STRENGTH, population, POP_SIZE);
    }
}



void printheader(){
    printf("\n\n");
    printf("###############\n");
    printf("## Evolution ##\n");
    printf("###############\n");
}


// Returns a random value between 0.0 and 1.0
float rnd(){
    return rand()/(float) RAND_MAX;
    // The type cast is needed here as the rand() function will produce an integer between 0 and the compiler defined valued RAND_MAX.  If RAND_MAX is an integer, the division will return either 0 or 1, but as we want a float between 0 and 1 inclusive, we need RAND_MAX to be a float
}
