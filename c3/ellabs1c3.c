========================================================================================
Operators and Arrays: C3 21/10/21

╔════════════╗
║Preparation:║
╚════════════╝

["evol.c"] // https://secure.ecs.soton.ac.uk/notes/ellabs/1/c3/evol_sk.c

All the prep questions are answered in the modified code below

┌──────────────────────────────────────────────────────────────────────────────────────┐
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

#define EQUATION   y = pow(x,2) - 4
// x^2 - 4
#define Y_TARGET   0.0

#define EPSILON    0.0001

#define POP_SIZE     100
#define MAX_GEN    10000

#define MUTATION_STRENGTH  0.1
#define RND_INIT           2


unsigned long cpufreq = 2300000000;
void wait(float time){
    for(unsigned long long i = 0; i < (cpufreq*time); i++){}
}
// the same wait function I made in c2 to make reading and debugging easier desu

void printheader(void);
float rnd(); // Random values 0.0 to 1.0

void initpop(float *pop, int size){
    // since population[] is not declared in this scope, we are writing to the memory address marked with *
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
        pop[i] = ( pop[0] + (mutst * 2 * (rnd() - 0.5)) );
        // rnd() - 0.5 gives us a value between -0.5 and 0.5, but we want -1 and 1, so we multiply by 2
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
└──────────────────────────────────────────────────────────────────────────────────────┘

========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Part 1"]

#define EQUATION   y = pow(x,3) - 10

Run  │ RND_INIT  │ Generations │ Solution
─────┼───────────┼─────────────┼──────────
 1   │     2     │     38      │ 2.154431
 2   │     5     │     96      │ 2.154441
 3   │     1     │     47      │ 2.154433
 4   │    10     │    199      │ 2.154441
 5   │     3     │    252      │ 2.154437

The magnitude of the seed used has an essentially random effect on the random numbers assigned to the array - there is no visible correlation between the seed value and the spacing of the random numbers for example.

3.2 ["Part 2"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
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
#define RND_INIT           2


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
        pop[i] = ( parent + (mutst * 2 * (rnd() - 0.5)) );
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
    float fit;

    srand(RND_INIT);
    initpop(population, POP_SIZE);
    // printheader();

    int i;

    while((best_ifit > fabs(Y_TARGET - EPSILON)) && (gen < MAX_GEN)){
        //printf("fabs(y) = %f, fabs(Y_TARGET - EPSILON) = %f\n", fabs(y), fabs(Y_TARGET - EPSILON));

        for(i=0; i < POP_SIZE; i++){
            // "natural selection"
            x = population[i];
            // sets x to each value of the array and tests it
            EQUATION;  // y = f(x)
            // that positions x is manipulated and then set to y
            ifit = fabs(y - Y_TARGET);
            // as y - Y_TARGET can be negative we take the abs
            // printf("x= %f  =>  y=  %+f,    ifit = %f\n", x, y, ifit);
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
        if(best_ifit > 0){
            fit = 1/best_ifit;
        }
        else{
            fit = -1;
        }
        printf("%d, %f\n",gen++, fit);
        // wait(0.1);
        // whats the point of this printf when you cant even read it without a pause ;>>
        offspring( best, MUTATION_STRENGTH, population, POP_SIZE);
    }
}


/*
void printheader(){
    printf("\n\n");
    printf("###############\n");
    printf("## Evolution ##\n");
    printf("###############\n");
}
*/

// Returns a random value between 0.0 and 1.0
float rnd(){
    return rand()/(float) RAND_MAX;
    // The type cast is needed here as the rand() function will produce an integer between 0 and the compiler defined valued RAND_MAX.  If RAND_MAX is an integer, the division will return either 0 or 1, but as we want a float between 0 and 1 inclusive, we need RAND_MAX to be a float
}
└──────────────────────────────────────────────────────────────────────────────────────┘

At first, there is a very high frequency of small increments to the fitness, however, this quickly falls off, and the frequency eventually decreases drastically.  Towards the end as the population is nearing the desired value, there are very few values which have a higher fitness than the previous values, however, when there are values with better fitness, due to the fact the graph is 1/fitness, the change in fit is much greater than the small changes seen at the early generations.

3.3 ["Part 3"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
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
#define MUTATION_STRENGTH  0.1
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
└──────────────────────────────────────────────────────────────────────────────────────┘

Investigation:- "How different mutation strengths affect population evolution"

To ensure a valid testing, each mutation strength value will be ran through 5 tests, each with the same corresponding 5 seeds.  Then, each of the mutation strengths will have a graph produced that shows how the population evolution changed depending on the seed.  These graphs can then be compared against one another to see how the different mutation strengths affected each populations evolutions despite having the same seeds.

I expect to see that with higher mutation strengths, the evolution process should be faster and finish in fewer generations, as this model has no mechanism for devolution or negative progress.

["Results"]

As can be seen in the 5 graphs, there appears to be a diminishing returns with the mutation strength as it was incremented by 0.2.  The mutation strength that provided the fastest evolution across all seeds was strength 0.5, with each strength around 0.5 falling off in terms of effectiveness.

4 ["Optional Additional Work"]

1) Random population with values between 0 and 1
2) Read from population array in groups of 3
3) Find the three differences of the three possible pairs
4) Each member in the group of 3 will have 2 differences (from the other members) and the member with the largest sum of these differences are the "fittest"
5) The population array is then augmented with a few "followers" i.e. members with similar "fitness" values to the "fittest" member before.
6) These members are placed randomly in the population array.

I would expect that if this process were to continue indefinitely, the entire population would eventually reach a value of 1.

I am going to decrease population to 50 for ease of data processing later.

┌──────────────────────────────────────────────────────────────────────────────────────┐
// evol.c
// ELEC1201 Lab C3: Operators and Arrays
// Evolutionary Computing
// KPZ 2018, MIT License
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define POP_SIZE     50
#define MAX_GEN    10000
#define MUTATION_STRENGTH  0.5
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
        // making sure the values never exceed 1
    }
}
// Randomly spreads fannum fans with mutst variations on the parent into the population

float rnd(){
    return rand()/(float) RAND_MAX;
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
            for(int i = 0; i < POP_SIZE; i++){
                printf("%d, %f\n", gen, population[i]);
            }
            gen++;
            fans(triple[(int)triplediff[COMPARE_SIZE]], MUTATION_STRENGTH, population, FANS);
            // now we spread in some fans
            //wait(0.01);
        }
        printf("\n");
    }


└──────────────────────────────────────────────────────────────────────────────────────┘

Unfortunately I could not observe a trend very easily using my csv chart as I quickly reached the limit for the number of data points (256), however, looking through the console, it is clear that there is at least some trend in which the overall population starts to increase in "fashion" very quickly at first, but as more and more of the population start reaching higher and higher values, the growth slows down significantly.

However, if I bend the rules a bit and find the average instead -

float arrayavg(float *pop, int size){
    float sum = 0;
    for(int i = 0; i < size; i++){
        sum += pop[i];
    }
    sum /= size;
    return sum;
}

and put this inside main

printf("%d, %f\n", gen, arrayavg(population, POP_SIZE));

I can see the trend very clearly. (Final image in pdf)
