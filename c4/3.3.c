#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define TERMINALWIDTH 100
#define OFFSET 14

char *filelocation = "3.1.txt";
char *train1 = "data1.txt"; // An extract from through the looking glass, Lewis Carroll.
char *train2 = "data2.txt"; // I dwell in possibility, Emily Dickinson.
char *train3 = "data3.txt"; // Immanuel Kant, Critique of Pure Reason.
char *train4 = "data4.txt"; // Miyazawa Kenji, Night on the Galactic Railroad.
char *train5 = "data5.txt"; // SCA-DI, Sakura no Uta
char *encrypted = "3.4enc.txt";
char *decrypted = "3.4dec.txt";

void calculateHistogram(char *filename, int *alphabetarray);
void printValue(const int *alphanum);
void plot(const int *alphanum, int width);
void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);
void training(int *alphabet);
int calculateOffset(const int *test, const int *data);

void main(){
    char a;
    int trainingdata[26];
    int alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
        trainingdata[i] = 0;
    }
    encipher(filelocation, encrypted, OFFSET);
    calculateHistogram(encrypted, alphabet);
    training(trainingdata);
    printValue(trainingdata);
    printf("\n");
    printValue(alphabet);
    printf("\n");
    printf("%d", calculateOffset(alphabet, trainingdata));
    decipher(encrypted, decrypted, calculateOffset(alphabet, trainingdata));

}

int calculateOffset(const int *test, const int *data){
    int highesttest = 0;
    int highestlearned = 0;
    int testarraypos = 0;
    int learnedarraypos = 0;
    for(int i = 0; i < 26; i++){
        if(test[i] > highesttest){
            highesttest = test[i];
            testarraypos = i;
        }
        if(data[i] > highestlearned){
            highestlearned = data[i];
            learnedarraypos = i;
        }
    }
    return testarraypos - learnedarraypos;
}

void training(int *alphabet){
    char a;
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
    }
    calculateHistogram(train1, alphabet);
    calculateHistogram(train2, alphabet);
    calculateHistogram(train3, alphabet);
    calculateHistogram(train4, alphabet);
    calculateHistogram(train5, alphabet);
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

void encipher(const char *p, char *c, const unsigned int offset){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    char a;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        if(isalpha(a)){
            a = toupper(a);
            a += offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90-(65-a);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}

void decipher(const char *p, char *c, const unsigned int offset){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    int a;
    //int deoffset = -offset;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        // reads character from encrypted file
        if(isalpha(a)){
            a -= offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90+(a-64);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}
