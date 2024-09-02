#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include "encrypt.h"
typedef struct account{
    char userName[60];
    int balance;
}account;
bool checkuser(char* userName,char* getpasw){
    FILE* fptr=fopen("user.txt","r");
    char usertemp[60];
    if(fptr!=NULL){
        while(fscanf(fptr,"%s %s %d",usertemp,getpasw)!=EOF){
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
        fprintf(fptr,"%s %s %d\n",userName,password,0);
    }
    fclose(fptr);
}
int getBalance(char* userName){
    FILE* fptr=fopen("user.txt","r");
    int balance=0;
    char usertemp[60];
    char password[60];
    if(fptr!=NULL){
        while(fscanf(fptr,"%s %s %d",usertemp,password,&balance)!=EOF){
            if(strcmp(usertemp,userName)==0){
                return balance;
            }
        }
    }
    return balance;
}
void addbalance(char* userName,int amount){
    FILE* fptr1=fopen("user.txt","r");
    FILE* fptr2=fopen("temp.txt","w");
    char* usertemp[60];
    char* password[60];
    int balance=0;
    if(fptr1!=NULL && fptr2!=NULL){
        while(fscanf(fptr1,"%s %s %d",usertemp,password,balance)!=EOF){
            if(strcmp(userName,usertemp)==0){
                fprintf(fptr2,"%s %s %d\n",usertemp,password,balance+amount);
            }else{
                fprintf(fptr2,"%s %s %d\n",usertemp,password,balance);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("user.txt");
    rename("temp.txt","user.txt");
}
void withdraw(char* userName,int amount){
    FILE* fptr1=fopen("user.txt","r");
    FILE* fptr2=fopen("temp.txt","w");
    char* usertemp[60];
    char* password[60];
    int balance=0;
    if(fptr1!=NULL && fptr2!=NULL){
        while(fscanf(fptr1,"%s %s %d",usertemp,password,balance)!=EOF){
            if(strcmp(userName,usertemp)==0){
                if(amount>balance){
                    printf("Insufficent Balance\n");
                    fprintf(fptr2,"%s %s %d\n",usertemp,password,balance);
                }else{
                    fprintf(fptr2,"%s %s %d\n",usertemp,password,balance-amount);
                }
            }else{
                fprintf(fptr2,"%s %s %d\n",usertemp,password,balance);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("user.txt");
    rename("temp.txt","user.txt");
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
                    sleep(2);
                    int choice2=1;
                    do{
                        printf("Login SuccessFull For %s\n",userName);
                        printf("Tell which operation you want to perform :\n");
                        printf("1 to add Balance\n");
                        printf("2 to Withdraw\n ");
                        printf("3 to Transfer\n");
                        printf("4 to Check Balance\n");
                        printf("5 to Exit\n");
                        scanf("%d",&choice2);
                        if(choice2==1){
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d",&amount);
                            addbalance(userName,amount);
                        }else if(choice2==2){
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d",&amount);
                            withdraw(userName,amount);
                        }else if(choice==3){


                        }else if(choice==4){
                            printf("The balance of the %s on %s : %d\n",userName,__DATE__,getBalance(userName));
                        }
                    }while(choice2!=5);
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