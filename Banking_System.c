#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include "encrypt.h"
typedef struct account{
    char userName[50];
    char password[50];
    int balance;
}account;
int main(){
    int choice=1;
    printf("Welcome to Suri Banking system\n");
    printf ("Today is: %s\n", __DATE__);
    do{
        sleep(1);
        printf("Press One of The following Keys: \n");
        printf("1 For Login\n");
        printf("2 For Sign Up\n");
        printf("3 To Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d",&choice);
        if(choice==1){
            printf("hello\n");
            sleep(1);
        }else if(choice==2){
            printf("bye\n");
            sleep(1);
        }
    }while(choice!=3);
    return 0;
}