#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include "encrypt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
typedef struct account{
    char userName[60];
    int balance;
}account;
bool checkuser(char* userName,char* getpasw){
    FILE* fptr=fopen("user.txt","r");
    char usertemp[60];
    int balance;
    if(fptr!=NULL){
        while(fscanf(fptr,"%s %s %d",usertemp,getpasw,&balance)!=EOF){
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
    char usertemp[60];
    char password[60];
    int balance=0;
    if(fptr1!=NULL && fptr2!=NULL){
        while(fscanf(fptr1,"%s %s %d",usertemp,password,&balance)!=EOF){
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
    char usertemp[60];
    char password[60];
    int balance=0;
    if(fptr1!=NULL && fptr2!=NULL){
        while(fscanf(fptr1,"%s %s %d",usertemp,password,&balance)!=EOF){
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
void transfer(char* userName){
    char user2[60];
    char usertemp[60];
    char pass[60];
    printf("Enter the userName to transfer to: ");
    scanf("%s",user2);
    int balance=0;
    int balance2=0;
    FILE* fptr=fopen("user.txt","r");
    bool flag=false;
    if(fptr!=NULL){
        while(fscanf(fptr,"%s %s %d",usertemp,pass,&balance)!=EOF){
            if(strcmp(userName,usertemp)==0){
                balance2=balance;
            }
            if(strcmp(user2,usertemp)==0){
                flag=true;
            }
        }
    }
    fclose(fptr);
    if(!flag){
        printf("%s Doesn't Exist's\n",user2);
        return;
    }
    int amount;
    printf("Enter The Amount to Transfer: ");
    scanf("%d",&amount);
    getchar();
    if(amount>balance2){
        printf("Insufficent Fund To Transfer\n");
        return;
    }
    fptr=fopen("user.txt","r");
    FILE* fptr2=fopen("temp.txt","w");
    if(fptr!=NULL && fptr2!=NULL){
        while(fscanf(fptr,"%s %s %d",usertemp,pass,&balance)!=EOF){
            if(strcmp(userName,usertemp)==0){
                fprintf(fptr2,"%s %s %d\n",usertemp,pass,balance-amount);
            }
            else if(strcmp(user2,usertemp)==0){
                fprintf(fptr2,"%s %s %d\n",usertemp,pass,balance+amount);
            }else{
                fprintf(fptr2,"%s %s %d\n",usertemp,pass,balance);
            }
        }
    }
    remove("user.txt");
    rename("temp.txt","user.txt");
    return;
}
int main(){
    mode_t old_umask = umask(0);
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
        getchar();
        char userName[60];
        char password[60];
        if(choice==1){
            sleep(1);
            printf("Hello user Please Enter The Following Details: \n");
            printf("UserName: ");
            scanf("%s",userName);
            char getpasw[60];
            if(checkuser(userName,getpasw)){
                printf("Password: ");
                scanf("%s",password);
                sleep(1);
                if(strcmp(password,getpasw)==0){
                    sleep(2);
                    int choice2=1;
                    do{
                        printf("Login SuccessFull For %s\n",userName);
                        printf("Tell which operation you want to perform :\n");
                        printf("1 to add Balance\n");
                        printf("2 to Withdraw\n");
                        printf("3 to Transfer\n");
                        printf("4 to Check Balance\n");
                        printf("5 to Check Logs\n");
                        printf("6 to Exit\n");
                        scanf("%d",&choice2);
                        getchar();
                        if(choice2==1){
                            sleep(1);
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d",&amount);
                            getchar();
                            addbalance(userName,amount);
                        }else if(choice2==2){
                            sleep(1);
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d",&amount);
                            getchar();
                            withdraw(userName,amount);
                        }else if(choice2==3){
                            sleep(1);
                            transfer(userName);
                        }else if(choice2==4){
                            sleep(1);
                            printf("The balance of the %s on %s : %d\n",userName,__DATE__,getBalance(userName));
                        }else if(choice2==5){
                            sleep(1);
                        }else if(choice2!=6){
                            printf("Please Enter correct value\n");
                        }
                    }while(choice2!=6);
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
        }else if(choice!=3){
            printf("Please Enter correct value\n");
        }
    }while(choice!=3);
    umask(old_umask);
    return 0;
}