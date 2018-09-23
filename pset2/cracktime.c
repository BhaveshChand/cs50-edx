#define _XOPEN_SOURCE
#include <unistd.h>
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include <sys/resource.h>
#include <sys/time.h>

#undef calculate
#undef getrusage

double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc,string argv[]){
    struct rusage before, after;
    getrusage(RUSAGE_SELF, &before);
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
    getrusage(RUSAGE_SELF, &after);
    printf("TIME: %.2f\n", calculate(&before, &after));
    return 0;
}

double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}