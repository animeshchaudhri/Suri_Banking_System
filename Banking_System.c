#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "encrypt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

typedef struct account
{
    char userName[60];
    int balance;
} account;

bool checkuser(char *userName, char *getpasw)
{
    FILE *fptr = fopen("user.txt", "r");
    char usertemp[60];
    int balance;
    bool found = false;
    if (fptr != NULL)
    {
        while (fscanf(fptr, "%s %s %d", usertemp, getpasw, &balance) != EOF)
        {
            if (strcmp(usertemp, userName) == 0)
            {
                found = true;
                break;
            }
        }
        fclose(fptr);
    }
    return found;
}

void adduser(char *userName, char *password)
{
    FILE *fptr = fopen("user.txt", "a");
    if (fptr != NULL)
    {
        fprintf(fptr, "%s %s %d\n", userName, password, 0);
        fclose(fptr);
    }
    else
    {
        perror("Error opening file for adding user");
    }
}

int getBalance(char *userName)
{
    FILE *fptr = fopen("user.txt", "r");
    int balance = 0;
    char usertemp[60];
    char password[60];
    if (fptr != NULL)
    {
        while (fscanf(fptr, "%s %s %d", usertemp, password, &balance) != EOF)
        {
            if (strcmp(usertemp, userName) == 0)
            {
                fclose(fptr);
                return balance;
            }
        }
        fclose(fptr);
    }
    else
    {
        perror("Error opening file for getting balance");
    }
    return balance;
}

void updateUserFile(char *operation, char *userName, int amount)
{
    FILE *fptr1 = fopen("user.txt", "r");
    FILE *fptr2 = fopen("temp.txt", "w");
    char usertemp[60];
    char password[60];
    int balance = 0;
    if (fptr1 != NULL && fptr2 != NULL)
    {
        while (fscanf(fptr1, "%s %s %d", usertemp, password, &balance) != EOF)
        {
            if (strcmp(userName, usertemp) == 0)
            {
                if (strcmp(operation, "add") == 0)
                {
                    fprintf(fptr2, "%s %s %d\n", usertemp, password, balance + amount);
                }
                else if (strcmp(operation, "withdraw") == 0)
                {
                    if (amount > balance)
                    {
                        printf("Insufficient Balance\n");
                        fprintf(fptr2, "%s %s %d\n", usertemp, password, balance);
                    }
                    else
                    {
                        fprintf(fptr2, "%s %s %d\n", usertemp, password, balance - amount);
                    }
                }
            }
            else
            {
                fprintf(fptr2, "%s %s %d\n", usertemp, password, balance);
            }
        }
        fclose(fptr1);
        fclose(fptr2);

        // File locking and atomic rename
        int fd = open("user.txt", O_RDWR);
        if (fd == -1)
        {
            perror("Error opening file for locking");
            return;
        }

        struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};
        if (fcntl(fd, F_SETLKW, &fl) == -1)
        {
            perror("Error locking file");
            close(fd);
            return;
        }

        if (rename("temp.txt", "user.txt") != 0)
        {
            perror("Error renaming file");
        }

        fl.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &fl) == -1)
        {
            perror("Error unlocking file");
        }

        close(fd);
    }
    else
    {
        if (fptr1) fclose(fptr1);
        if (fptr2) fclose(fptr2);
        perror("Error opening files for updating user data");
    }
}

void addbalance(char *userName, int amount)
{
    updateUserFile("add", userName, amount);
}

void withdraw(char *userName, int amount)
{
    updateUserFile("withdraw", userName, amount);
}

void transfer(char *userName)
{
    char user2[60];
    printf("Enter the userName to transfer to: ");
    scanf("%s", user2);
    
    if (!checkuser(user2, NULL))
    {
        printf("%s Doesn't Exist\n", user2);
        return;
    }

    int amount;
    printf("Enter The Amount to Transfer: ");
    scanf("%d", &amount);
    getchar();

    int balance = getBalance(userName);
    if (amount > balance)
    {
        printf("Insufficient Fund To Transfer\n");
        return;
    }

    withdraw(userName, amount);
    addbalance(user2, amount);
}

int main()
{
    mode_t old_umask = umask(0);
    int choice = 1;
    printf("Welcome to Suri Banking system\n");
    printf("Today is: %s\n", __DATE__);
    do
    {
        sleep(1);
        printf("Press One of The following Keys: \n");
        printf("1 For Login\n");
        printf("2 For Sign Up\n");
        printf("3 To Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        getchar();
        char userName[60];
        char password[60];
        if (choice == 1)
        {
            sleep(1);
            printf("Hello user Please Enter The Following Details: \n");
            printf("UserName: ");
            scanf("%s", userName);
            char getpasw[60];
            if (checkuser(userName, getpasw))
            {
                printf("Password: ");
                scanf("%s", password);
                sleep(1);
                if (strcmp(password, getpasw) == 0)
                {
                    sleep(2);
                    int choice2 = 1;
                    do
                    {
                        printf("Login SuccessFull For %s\n", userName);
                        printf("Tell which operation you want to perform :\n");
                        printf("1 to add Balance\n");
                        printf("2 to Withdraw\n");
                        printf("3 to Transfer\n");
                        printf("4 to Check Balance\n");
                        printf("5 to Check Logs\n");
                        printf("6 to Exit\n");
                        scanf("%d", &choice2);
                        getchar();
                        if (choice2 == 1)
                        {
                            sleep(1);
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d", &amount);
                            getchar();
                            addbalance(userName, amount);
                        }
                        else if (choice2 == 2)
                        {
                            sleep(1);
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d", &amount);
                            getchar();
                            withdraw(userName, amount);
                        }
                        else if (choice2 == 3)
                        {
                            sleep(1);
                            transfer(userName);
                        }
                        else if (choice2 == 4)
                        {
                            sleep(1);
                            printf("The balance of the %s on %s : %d\n", userName, __DATE__, getBalance(userName));
                        }
                        else if (choice2 == 5)
                        {
                            sleep(1);
                            // Implement log checking functionality here
                        }
                        else if (choice2 != 6)
                        {
                            printf("Please Enter correct value\n");
                        }
                    } while (choice2 != 6);
                }
                else
                {
                    printf("wrong password\n");
                }
            }
            else
            {
                sleep(1);
                printf("User Doesn't Exist\n");
            }
        }
        else if (choice == 2)
        {
            sleep(1);
            printf("Enter the following Details to add User\n");
            printf("UserName: ");
            scanf("%s", userName);
            char getpasw[60];
            if (checkuser(userName, getpasw))
            {
                sleep(1);
                printf("Sorry user already Exist\n");
            }
            else
            {
                printf("Password: ");
                scanf("%s", password);
                adduser(userName, password);
            }
        }
        else if (choice != 3)
        {
            printf("Please Enter correct value\n");
        }
    } while (choice != 3);
    umask(old_umask);
    return 0;
}
