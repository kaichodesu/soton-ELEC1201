#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void main(){
    Matrix mat;
    mat = createMatrixFromFile("example1.mat");
    printMatrix(mat);
    destroyMatrix(mat);
}
