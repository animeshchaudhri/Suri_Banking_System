#include<ctype.h>
void encrypt(char* message,int key){
    for(int i=0;message[i]!='\0';i++){
        if(isalnum(message[i])){
            if(isupper(message[i])){
                message[i]=(message[i]-'A'+key)%26+'A';
            }
            else if(islower(message[i])){
                message[i]=(message[i]-'a'+key)%26+'a';
            }else if(isdigit(message[i])){
                message[i]=(message[i]-'0'+key)%10+'0';
            }
        }
    }
}
void decrypt(char* message,int key){
    for(int i=0;message[i]!='\0';i++){
        if(isalnum(message[i])){
            if(isupper(message[i])){
                message[i]=(message[i]-'A'-key+26)%26+'A';
            }else if(islower(message[i])){
                message[i]=(message[i]-'a'-key+26)%26+'a';
            }else if(isdigit(message[i])){
                message[i]=(message[i]-'0'-key+10)%10+'0';
            }
        }
    }
}