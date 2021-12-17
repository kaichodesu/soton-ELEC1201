#include <stdio.h>
#include <string.h>

typedef struct {
    // declare a new datatype called "Profile" (Capital letter convention) (well actually typedef is used to rename datatypes but here its essentially defining one called Profile)
    int age;       // this datatype will contain two int variables and a char string.
    char name[50];
    int id;
} Profile;

void idCalc(Profile *profile);

void main(){
    Profile user;
    Profile administrator;
    user.age = 54;
    strcpy(user.name, "Alan Peters");
    administrator.age = 63;
    strcpy(administrator.name, "Xandr Wayland");
    idCalc(&user);
    idCalc(&administrator);
    printf("%s's id is: %d \n", user.name, user.id);
    printf("%s's id is: %d \n", administrator.name, administrator.id);
}

void idCalc(Profile *p){
    int a = 0;
    for(int i = 0; i < strlen(p->name); i++){
        a += (char)p->name[i];
    }
    p->id = a*p->age;
}

