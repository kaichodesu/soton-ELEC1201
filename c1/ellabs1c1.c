===========================================================================================
Introduction to C Programming: Toolchain C1 07/10/21

╔════════════╗
║Preparation:║
╚════════════╝

LISTING 1: The closing */ in line 1 is missing:

┌────────────────────────────────────────────────┐
│/* hello.c                                      │
│/* A famous test for the C build process . */   │
│                                                │
│#include <stdio.h>                              │
│                                                │
│int main(){                                     │
│	printf("Hello world!");                      │
│	return 0;                                    │
│}                                               │
└────────────────────────────────────────────────┘

LISTING 2: The name of the library in line 4 has been changed:

┌────────────────────────────────────────────────┐
│/* hello.c */                                   │
│/* A famous test for the C build process . */   │
│                                                │
│#include <mystdio.h>                            │
│                                                │
│int main(){                                     │
│	printf("Hello world!");                      │
│	return 0;                                    │
│}                                               │
└────────────────────────────────────────────────┘

LISTING 3: The name of the function called in line 7 has been changed:

┌────────────────────────────────────────────────┐
│/* hello.c */                                   │
│/* A famous test for the C build process . */   │
│                                                │
│#include <mystdio.h>                            │
│                                                │
│int main(){                                     │
│	myprintf("Hello world!");                    │
│	return 0;                                    │
│}                                               │
└────────────────────────────────────────────────┘


                               │ Listing 1 │ Listing 2 │ Listing 3 │
───────────────────────────────┼───────────┼───────────┼───────────┤
No error message               │      X    │           │           │
───────────────────────────────┼───────────┼───────────┼───────────┤
An error from the preprocessor │           │     X     │           │
───────────────────────────────┼───────────┼───────────┼───────────┤
An error from the compiler     │           │           │           │
───────────────────────────────┼───────────┼───────────┼───────────┤
An error from the linker       │           │           │     X     │
───────────────────────────────┴───────────┴───────────┴───────────┘

Listing 1 is an example of a syntax error(?) and as such will produce a compiler error as the
code cannot be parsed.

Listing 2 is trying to call a library that does not exist, and as libraries are handled by the
preprocessor, will cause the preprocessor to provide an error.

Listing 3 is trying to call a function that is not defined anywhere in the program or libraries
and so will produce an error from the linker as the function cannot be found.

==============                                                                           

Variables:

Variables can take many different types, such as int, float/double and char (C handles strings as
an array of char)

When introducing a variable, they must be declared as being one of these types, i.e.

int integer;
float floatVariable, floatVariableTwo;
double doubleVariable;
char character, string[];

In this case, we have given each variable a "type" and a "name", however, their values have not yet
been defined.

"Values" can be defined when a variable is declared, for example:

int integer = 1984;
char string[] = "Hello World";
float floatVariable = 3.14;

However, as long as the variable has been defined, the value can be set at any point after the declaration:

integer = 2011;
character = "a";
floatVariable = 9.81;

===========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

==

The command "gcc hello.c -o hello" would not execute successfully if there was a space in the file name
or directory as this would likely cause the parts of the name/directory to be interpreted as different
arguments.  I believe this can be circumvented by placing the name/directory in quotation marks ("") but
I can't remember.

==

Executing "ls" reveals all the files in the directory:

    ~/Documents/[xxxxx]/ELEC1201/c1  ls                                                    ✔
hello  hello.c

==

If we repeat the same mistakes that were highlighted in the preparation work, we receive different errors as follows:

═══════════════════════════════════════════════════════════════════════════════════════════════════════
────────────────────────────────────────────────
/* hello.c
/* A famous test for the C build process. */

#include <stdio.h>

#define SUCCESS 0

int main() {
    /* A new-line control character (\n)   */
    /* is used here, in case the terminal  */
    /* collects complete lines before      */
    /* showing them.                       */
    printdf("Hello world!\n");
    return SUCCESS;
}
────────────────────────────────────────────────

     ~/Documents/[xxxxx]/ELEC1201/c1  gcc hello.c -o hello                                  ✔

      In this example, there is no error produced by the compiler and the command executes successfully.

═══════════════════════════════════════════════════════════════════════════════════════════════════════
────────────────────────────────────────────────
/* hello.c */
/* A famous test for the C build process.*/

#include <random.h>

#define SUCCESS 0

int main() {
    /* A new-line control character (\n)   */
    /* is used here, in case the terminal  */
    /* collects complete lines before      */
    /* showing them.                       */
    printdf("Hello world!\n");
    return SUCCESS;
}
────────────────────────────────────────────────

    ~/Documents/[xxxxx]/ELEC1201/c1  gcc hello.c -o hello1                             INT ✘
hello.c:4:10: fatal error: random.h: No such file or directory
    4 | #include <random.h>
      |          ^~~~~~~~~~
compilation terminated.

      In this example, we can see that we produced a preprocessor error by the phrase "No such file or directory".  This shows that the preprocessor was unable to find the library referenced in the program and as such did not bother to start compiling.

═══════════════════════════════════════════════════════════════════════════════════════════════════════
────────────────────────────────────────────────
/* hello.c */
/* A famous test for the C build process.*/

#include <stdio.h>

#define SUCCESS 0

int main() {
    /* A new-line control character (\n)   */
    /* is used here, in case the terminal  */
    /* collects complete lines before      */
    /* showing them.                       */
    printout("Hello world!\n");
    return SUCCESS;
}
────────────────────────────────────────────────

    ~/Documents/[xxxxx]/ELEC1201/c1  gcc hello.c -o hello1                             INT ✘
hello.c: In function ‘main’:
hello.c:13:5: warning: implicit declaration of function ‘printout’; did you mean ‘printf’? [-Wimplicit-function-declaration]
   13 |     printout("Hello world!\n");
      |     ^~~~~~~~
      |     printf
/usr/bin/ld: /tmp/ccj4MjwG.o: in function `main':
hello.c:(.text+0x14): undefined reference to `printout'
collect2: error: ld returned 1 exit status

      In this example, we can see that we produced a preprocessor error by the phrase "collect2: error: ld returned 1 exit status".  This shows that the linker was unable to find any reference to the function printout() in any of the libraries, causing the command to fail.

═══════════════════════════════════════════════════════════════════════════════════════════════════════

==

If we are to remove the "*/" from the second line instead of the first, as shown, we are given a vastly different result:

────────────────────────────────────────────────
/* hello.c */
/* A famous test for the C build process.

#include <stdio.h>

#define SUCCESS 0

int main() {
    /* A new-line control character (\n)   */
    /* is used here, in case the terminal  */
    /* collects complete lines before      */
    /* showing them.                       */
    printdf("Hello world!\n");
    return SUCCESS;
}
────────────────────────────────────────────────

    ~/Documents/[xxxxx]/ELEC1201/c1  gcc hello.c -o hello1                             INT ✘
hello.c:13:13: error: expected declaration specifiers or ‘...’ before string constant
   13 |     printdf("Hello world!\n");
      |             ^~~~~~~~~~~~~~~~
hello.c:14:5: error: expected identifier or ‘(’ before ‘return’
   14 |     return SUCCESS;
      |     ^~~~~~
hello.c:15:1: error: expected identifier or ‘(’ before ‘}’ token
   15 | }
      | ^

      In this example, we can see that we produced a compiler error by the phrase "expected declaration specifiers or ‘...’ before string constant".  This shows that the compiler was unable to parse the code and understand how to interpret it as the syntax was incorrect beyond an extent that the compiler could still understand - When the second "*/" is omitted, a majoirity of all the code is gone and we have a function which has not been declared in any scope.

==

Variable declaration and initialisation in the file:

char name[]="human";

My added variable declaration and initialisation:

float floatVariable = 3.14;

My modified printf() function:

────────────────────────────────────────────────
/* helloyou.c */
/* Hello with text string. */

#include <stdio.h>

#define SUCCESS 0

char name[]="human";
float floatVariable = 3.14;

int main() {
    printf("pi is %f!\n", floatVariable);
    return SUCCESS;
}
────────────────────────────────────────────────

Output:

    ~/Documents/[xxxxx]/ELEC1201/c1  gcc helloyou.c -o helloyou                            ✔
    ~/Documents/[xxxxx]/ELEC1201/c1  ./helloyou                                            ✔
pi is 3.140000!

I used %f as the proceeding variable was a float. If I change this format specifier to mismatch then we receive errors as follows:

│ %d │ pi is 314495528! │
│ %x │ pi is ed4a4c98!  │
│ %c │ pi is h!         │

I believe this is happening because the variable is stored in memory as binary and the format specifier reads the memory address the variable points to "as is", causing the unique bits that would be used in each format to be misinterpreted when used in other formats, although I am not too sure why this would be as the variable was previously declared as being of one type.

==

    ~/Documents/[xxxxx]/ELEC1201/c1  gcc hello-input.c -o hello-input             ✔  12s 
    ~/Documents/[xxxxx]/ELEC1201/c1  ./hello-input                                         ✔
What is your name?  [xxxxx]
Hello [xxxxx]!

If the input surpasses the size of the array I would imagine the program would crash as it is would try to assign a value to the array which is not in memory.

==

With the array reduced to only 5 entries, we are given the error as follows:

    ~/Documents/[xxxxx]/ELEC1201/c1  ./hello-input                                        ✔
What is your name?  iouewrtyo
Hello iouewrtyo!
*** stack smashing detected ***: terminated
zsh: abort (core dumped)  ./hello-input

Surprisingly the program did not crash, however, it was forcibly terminated by Z shell for what I presume is because the program was writing to memory which it was not allocated, thus caused the OS/Shell to terminate it as accessing memory outside what has been allocated is a fairly common security exploit.

==
Optional Additional Work
==

Task as I understand it:

>There are constant defined implicitly by the compilier, one of them being "__LINE__" which I'd presume is used when error messages must be given pointing to the misbehaving line.
>I need to define a statement "MARK" which calls a printf() to print "__LINE__" all within the defintion.
>Define another label "DEBUG" which when set to a true state will cause "MARK" to be called, when it would otherwise be hidden (i.e. verbose)

Looking for what __LINE__ actually is
printf("%d", __LINE__)

>outputs the line number of that printf() function.

Defining MARK with a function rather than a value like __LINE__
#define MARK printf("%d", __LINE__)

Trying to compile:

int main() {
    char name[NAME_BUFFSIZE];

    printf("What is your name?  ");
    scanf("%s", name);
    printf("Hello %s!\n", name);
    MARK;
    return SUCCESS;
}

produces no compilation errors (thankfully) and the program outputs:
What is your name?  [xxxxx]
Hello [xxxxx]!
16%

(Note that MARK is called on line 16)

Now we can call a printf() to print __LINE__ we need to try to define "DEBUG"

#define DEBUG

And use the conditional syntax as documented "https://gcc.gnu.org/onlinedocs/gcc-3.0.1/cpp_4.html"

Final Code:

────────────────────────────────────────────────
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
────────────────────────────────────────────────

When DEBUG is NOT defined:

    ~/Documents/[xxxxx]/ELEC1201/c1  ./hello-input                                         ✔
What is your name?  [xxxxx]
Hello [xxxxx]!

When DEBUG is EXPLICITLY defined:

    ~/Documents/[xxxxx]/ELEC1201/c1  ./hello-input                                         ✔
What is your name?  [xxxxx]
Hello [xxxxx]!
21%

I presume this can be used in important threads to show you which lines of code are being executed or omitted, making debugging easier as you can follow the execution.

