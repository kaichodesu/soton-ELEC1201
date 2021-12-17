========================================================================================
Data Structures and Dynamic Memory Allocation: C5 4/11/21

╔════════════╗
║Preparation:║
╚════════════╝

1)  Structs and Enum

["struct"]
A struct is a a method to introduce your own datatypes into your program, essentially allowing you to group together different types of datatypes into one so the set can be more efficiently accessed and transferred between functions.

for example, a quick program that has a struct for user profiles:
┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <string.h>

typedef struct {
    // declare a new datatype called "Profile" (Capital letter convention) (well actually typedef is used to rename datatypes but here its essentially defining one called Profile)
    int age;       // this datatype will contain two int variables and a char string.
    char name[50];
    int id;
} Profile;

void idCalc(Profile *profile);  // we give the function the memory address of the struct

void main(){
    Profile user;
    Profile administrator;
    user.age = 54;
    strcpy(user.name, "Alan Peters");  // wanted to DMA but didn't know how to orz
    administrator.age = 63;            // ...pointers are how but i cba to add them now
    strcpy(administrator.name, "Xandr Wayland");
    idCalc(&user);
    idCalc(&administrator);
    printf("%s's id is: %d \n", user.name, user.id);
    printf("%s's id is: %d \n", administrator.name, administrator.id);
}

void idCalc(Profile *p){
    // just a weird way of making an id based on the ascii value of the name characters and the profile age, demonstrating transferring blocks of variables very easily.
    int a = 0;
    for(int i = 0; i < strlen(p->name); i++){
        a += (char)p->name[i];
    }
    p->id = a*p->age;
}
└──────────────────────────────────────────────────────────────────────────────────────┘
Output:

    ~/Documents/[xxxxx]/ELEC1201/c5  ./prep1                                ✔
Alan Peters's id is: 56106
Xandr Wayland's id is: 79443

["enum"]
An enum datatype is used to assign more readable 'names' to integers, or 'enumerate' names.  This makes it more easy to keep track of values in a program.  A common use for this is to assign the names of days of the week to integer values.

typedef enum { // when left undefined they are automatically numbered.
      Monday,
      Tuesday,
      Wednesday,
      Thursday,
      Friday,
      Saturday,
      Sunday
} Day;

  Day today = Tuesday;  // This will set "today" to the value 1.

2)
typedef struct {
    int length;  // length of the array
    double *element; // this is just a 1d matrix... idk how its meant to be a vector
} Vector;

3)
typedef struct {
	int cols;
    int rows;
    double **element; // allows us to define a 2d matrix of malloc size later.
} Matrix;

4)  malloc and calloc

["malloc"]
malloc() is a function that allocates the number of bytes input as an argument at the memory address it returns.  In stlib.io, malloc is a void* datatype function, however this is because it can easily be changed with a typecast such as (int*) or (float*) depending on the required type.

>  malloc(numberOfElements*sizeof(char));

["calloc"]
calloc() is a function that operates very similarly to malloc, however, it also actually accesses the memory that it allocates and "clears" (hence calloc: clear-allocate) the memory at the address and replaces it with 0 data.  This is preferred if you will not be using all the memory allocated immediately or for very platform dependent scenarios that require actual data to be written for the OS to actually provide the memory to be used.  the function calloc also takes in one extra argument, however, it is essentially the same as malloc as this argument is the length of the memory that should be replaced with 0.

>  calloc(numberOfElements, sizeof(char));

5)  Memory that has been allocate can easily be freed using the free() command.
Depending on the use case, the order in which memory is freed is very important.

6)  Header files are included in the Source files.  By compiling the Source files (for example test.c), you combine the header and source files into an object file.

  $ gcc -c test.c

will output a file test.o

Once the object file has been created, it can be linked in the final compilation of the program

  $ gcc test.o program.c -o program

(program.c is the script that contains the only main() function)

7)  Arguments can easily be passed into the program at execution by included arguments in the main function.

>  void main(int argc, char* argv[])

argc is the number of arguments, the program name called when being executed is always the first argument.  Thus, if there are more than one arguments, argc will be > 1, and these arguments will be indexed in argv[], with argv[0] being the program name as as mentioned before, the first argument is always the program name.

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Vectors"]

"vec1test.c"
┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void main(){
    Vector vec = {0, NULL};
    // initialising
    vec = createVectorFromFile("example1.vec");
    printVector(vec);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

"vector.c"
┌──────────────────────────────────────────────────────────────────────────────────────┐
Vector createVector(const unsigned int nLength)
{
    Vector vec = {nLength, NULL};
    vec.element = (double*) calloc(nLength, sizeof(double));
    return vec;
}

void destroyVector(Vector vec)
{
	free(vec.element);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

"vector.h"
┌──────────────────────────────────────────────────────────────────────────────────────┐
typedef struct {
    int length;
    double *element;
} Vector;
└──────────────────────────────────────────────────────────────────────────────────────┘

    ~/Documents/[xxxxx]/ELEC1201/c5  ./vec1test                         127 ✘
[0] = 2.300000
[1] = 4.500000

3.2 ["Matricies"]

"mat1test.c"
┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void main(){
    Matrix mat = {0, 0, NULL};
    mat = createMatrixFromFile("example1.mat");
    printMatrix(mat);
    destroyMatrix(mat);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

"matrix.c"
┌──────────────────────────────────────────────────────────────────────────────────────┐
Matrix createMatrix(const unsigned int nRows, const unsigned int nCols)
{
	Matrix mat = {nRows, nCols, NULL};
    // We are gonna initialise the rows first.
    // ..or not, looking at the code below it wants us to initialise the columns first.
    mat.element = (double**) calloc(nCols, sizeof(double*));
    for(int i = 0; i < nCols; i++){
        mat.element[i] = (double*) calloc(nRows, sizeof(double));
    }
    return mat;
}

void destroyMatrix(Matrix mat)
{
	for(int i = 0; i < mat.cols; i++){
        free(mat.element[i]);
    }
    free(mat.element);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

"vector.h"
┌──────────────────────────────────────────────────────────────────────────────────────┐
typedef struct {
	int cols;
    int rows;
    double **element;
} Matrix;
└──────────────────────────────────────────────────────────────────────────────────────┘

    ~/Documents/[xxxxx]/ELEC1201/c5  ./mat1test                             ✔
[0][0] = 2.300000
[1][0] = 4.500000
[2][0] = 2.400000
[3][0] = 6.300000

This result did concern me at the time but as it compiled and executed successfully I left it and continued with the work... although it would come back to make things difficult later.

3.3.1 ["Circuit Simulation"]

┌────────────────────────────────────────────────┐
/* Data Structures */

typedef enum {
    resistor,
    voltage,
    current,
} CompType;

typedef struct {
    char *name;
    unsigned int n1;
    unsigned int n2;
    double value;
    CompType type;
} Component;

typedef struct {
    int nC;  // Number of components
    int nN;  // Number of nodes
    int nV;  // etc..
    int nI;
    int nR;
    Component* comp;
} Circuit;
└────────────────────────────────────────────────┘

3.3.2 ["Analyse.c"]

┌────────────────────────────────────────────────┐
#include <stdio.h>
#include <stdlib.h>
#include "circuit.h"

int main(int argc, char *argv[])
{
	Circuit c;

	if (argc == 2)
	{
		c = createCircuitFromFile(argv[1]);
        analyseCircuit(c);
        destroyCircuit(c);
	}
	else
		printf("Syntax: %s <filename>\n", argv[0]);

	return EXIT_SUCCESS;
}
└────────────────────────────────────────────────┘

3.3.3 ["Testing"]

    ~/Documents/[xxxxx]/ELEC1201/c5  ./analyse example1.cir          1 ✘  
----------------------------
 Voltage sources: 0
 Current sources: 0
       Resistors: 0
           Nodes: 1
----------------------------
 Node   0 =   0.000000 V
----------------------------

Problems...
The program doesnt seem to be operating correctly in
Matrix createMatrixFromFile()
on lines

while(fscanf(fPtr, "%lf", &d) != EOF) {
    m.cols++;
    while((c = fgetc(fPtr)) == ' ');
    if ((c == '\n') || (c == EOF))
        break;
    ungetc(c, fPtr);
}

trying to change the characters used from ' ' to 'x' and replacing them in the mat file and replacing the '\n' with 'o' or another character to show a new line does not have any affect either.  There seems to be some issue with how the files are being read.

Another odd behaviour is that, once '\n' has been replaced by something else, I cannot type '\n' back into the program to return functionality, instead the program fails to execute and is stuck in a loop.
