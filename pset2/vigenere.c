#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(int argc,string argv[]){
    if(argc!=2){    //error for no or >1 command line arg
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    bool flag=true;
    for(int i=0,len=strlen(argv[1]);i<len;i++){  
        if(argv[1][i]>='a'&&argv[1][i]<='z') argv[1][i]-=32;  //bringing all letters of key to upper case
        else if(!(argv[1][i]>='A'&&argv[1][i]<='Z')){   //checking for chars other than alphabet
            flag=false;
            break;
        }
    }
    if(!flag){  //error for invalid command line arg
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    printf("plaintext:  ");
    string s=get_string();  //taking input from user
    for(int i=0,j=0,len=strlen(s),keylen=strlen(argv[1]);i<len;i++){   //encrypting the string
        if(s[i]>='a'&&s[i]<='z') s[i]=(((int)s[i]-'a'+argv[1][(j++)%keylen]-'A')%26)+'a';
        else if(s[i]>='A'&&s[i]<='Z') s[i]=(((int)s[i]-'A'+argv[1][(j++)%keylen]-'A')%26)+'A';
    }
    printf("ciphertext: %s\n",s);
    return 0;
}