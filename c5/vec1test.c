#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void main(){
    Vector vec = {0, NULL};
    vec = createVectorFromFile("example1.vec");
    printVector(vec);
}
