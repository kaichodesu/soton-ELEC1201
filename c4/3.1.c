#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define TERMINALWIDTH 100

char *filelocation = "3.1.txt";

void calculateHistogram(char *filename, int *alphabetarray);
void printValue(const int *alphanum);
void plot(const int *alphanum, int width);

void main(){
    char a;
    int alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
    }
    FILE *file = fopen(filelocation, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            printf("%c", toupper(a));
        }
        else{
            printf("_");
        }
    }
    fclose(file);
    printf("\n");
    printf("\n");
    calculateHistogram(filelocation, alphabet);
    printf("\n");
    printf("\n");
    printValue(alphabet);
    printf("\n");
    printf("\n");
    plot(alphabet, TERMINALWIDTH);
}

void calculateHistogram(char *fn, int *arr){
    char a;
    FILE *file = fopen(fn, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            a = toupper(a);
            // printf("\n");
            //printf("%d, ", a);
            arr[a-65] += 1;
            //printf("%d, ", arr[a-65]);
        }
        else{}
    }
    fclose(file);
}

void printValue(const int *arr){
    for(int i = 0; i < 26; i++){
        printf("%d\n", arr[i]);
    }
}

void plot(const int *arr, int width){
    int maxnum = 0;
    float scale = 0;
    for(int i = 0; i < 26; i++){
        if(arr[i] > maxnum){
            maxnum = arr[i];
        }
        else{}
    }
    scale = ceil((float)width/maxnum);
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < floor(arr[i]*scale); j++){
            printf("█");
        }
        printf("\n");
    }
}



