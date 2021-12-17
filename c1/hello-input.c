/* hello-input.c */
/* Ask for input. */

#include <stdio.h>

#define SUCCESS 0
#define NAME_BUFFSIZE 5
#define DEBUG
#ifdef DEBUG
#define MARK printf("%d", __LINE__)
#else
#define MARK printf("")
#endif

int main() {
    char name[NAME_BUFFSIZE];

    printf("What is your name?  ");
    scanf("%s", name);
    printf("Hello %s!\n", name);
    MARK;
    return SUCCESS;
}
