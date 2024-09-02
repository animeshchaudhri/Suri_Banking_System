#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include "encrypt.h"
typedef struct account{
    char userName[60];
    char password[60];
    int balance;
}account;
bool checkuser(char* userName,char* getpasw){
    FILE* fptr=fopen("user.txt","r");
    char usertemp[60];
    if(fptr!=NULL){
        while(fscanf(fptr,"%s %s",usertemp,getpasw)!=EOF){
            if(strcmp(usertemp,userName)==0){
                fclose(fptr);
                return true;
            }
        }
    }
    fclose(fptr);
    return false;
}
void adduser(char* userName,char* password){
    FILE* fptr=fopen("user.txt","a");
    if(fptr!=NULL){
        fprintf(fptr,"%s %s\n",userName,password);
    }
    fclose(fptr);
}
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
        char userName[60];
        char password[60];
        if(choice==1){
            sleep(1);
            printf("Hello user Please Enter The Following Details: \n");
            printf("UserName: ");
            scanf("%s",userName);
            printf("Password: ");
            scanf("%s",password);
            sleep(1);
            char getpasw[60];
            if(checkuser(userName,getpasw)){
                sleep(1);
                if(strcmp(password,getpasw)==0){
                    printf("Login successFull\n");
                }else{
                    printf("wrong password\n");
                }
            }else{
                sleep(1);
                printf("User Doesn't Exsist\n");
            }
        }else if(choice==2){
            sleep(1);
            printf("Enter the following Details to add User\n");
            printf("UserName: ");
            scanf("%s",userName);
            char getpasw[60];
            if(checkuser(userName,getpasw)){
                sleep(1);
                printf("Sorry user already Exist\n");
            }else{
                printf("Password: ");
                scanf("%s",password);
                adduser(userName,password);
            }
        }
    }while(choice!=3);
    return 0;
}