#define _XOPEN_SOURCE
#include <unistd.h>
#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(int argc,string argv[]){
    if(argc!=2){    //error for no or >1 command line arg
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char salt[3]={argv[1][0],argv[1][1],0}; //assign salt
    char key[5]={64,64,64,'A',0};    //initialise key
    int keysize=1;
    while(keysize!=5){
        if(!(strcmp(argv[1],crypt(key+4-keysize,salt)))) break; //check for match
        key[3]++;   //start shift key by 1
        if(key[3]=='[') key[3]='a';
        else if(key[3]=='{'){
            key[3]='A';
            key[2]++;
            if(keysize<2) keysize=2;
            if(key[2]=='[') key[2]='a';
            else if(key[2]=='{'){
                key[2]='A';
                key[1]++;
                if(keysize<3) keysize=3;
                if(key[1]=='[') key[1]='a';
                else if(key[1]=='{'){
                    key[1]='A';
                    key[0]++;
                    if(keysize<4) keysize=4;
                    if(key[0]=='[') key[0]='a';
                    else if(key[0]=='{'){
                        keysize=5;
                    }
                }
            }
        }   //end shift key by 1
    }
    printf("%s\n",key+4-keysize); //print out correct key
    return 0;
}