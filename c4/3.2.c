#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define OFFSET 20

char *filelocation = "3.1.txt";
char *encrypted = "3.2enc.txt";
char *decrypted = "3.2dec.txt";

void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);

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
    printf("\n\n");
    encipher(filelocation, encrypted, OFFSET);
    printf("\n\n");
    decipher(encrypted, decrypted, OFFSET);
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
