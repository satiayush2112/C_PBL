#include<stdio.h>
#include<string.h>

int login() {
    char u[20], p[20];

    printf("Username: ");
    scanf("%s", u);
    printf("Password: ");
    scanf("%s", p);

    if(strcmp(u,"Ayush")==0 && strcmp(p,"2112")==0)
        return 1;
    else
        return 0;

}