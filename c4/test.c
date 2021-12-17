#include <stdio.h>

void main(){
    char a;
    FILE *file = fopen("test.txt", "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        printf("%c", a);
    }
    fclose(file);
}
