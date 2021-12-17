#include <stdio.h>
#include <ctype.h>
#include <math.h>

char *filelocation = "3.1.txt";
char *encrypted = "4enc.txt";
char *decrypted = "4dec.txt";
char word[] = "TEST";
// 4 letter phrases only

void encipher(const char *p, char *c, const char *word);
void decipher(const char *c, char *p, const char *word);

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
    encipher(filelocation, encrypted, word);
    printf("\n\n");
    decipher(encrypted, decrypted, word);
}

void encipher(const char *p, char *c, const char *word){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    char a;
    int offset = 0;
    int pos = 0;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        switch (pos)
        {
            case 0:
                pos = 1;
                break;
            case 1:
                pos = 2;
                break;
            case 2:
                pos = 3;
                break;
            case 3:
                pos = 0;
                break;
        }
        offset = floor(word[pos]/4);
        printf("offset: %d\n", offset);
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

void decipher(const char *p, char *c, const char *word){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    int a;
    int offset = 0;
    int pos = 0;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        switch (pos)
        {
            case 0:
                pos = 1;
                break;
            case 1:
                pos = 2;
                break;
            case 2:
                pos = 3;
                break;
            case 3:
                pos = 0;
                break;
        }
        offset = floor(word[pos]/4);
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
