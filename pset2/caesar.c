#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(int argc,string argv[]){
    if(argc!=2){    //error for invalid command line arg
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int k=0;
    for(int i=strlen(argv[1])-1,placeval=1;i>=0;i--,placeval*=10){  //generating integer from string
        k+=(argv[1][i]-48)*placeval;
    }
    printf("plaintext:  ");
    string s=get_string();  //taking input from user
    for(int i=0,len=strlen(s);i<len;i++){   //encrypting the string
        if(s[i]>='a'&&s[i]<='z') s[i]=(((int)s[i]-'a'+k)%26)+'a';
        else if(s[i]>='A'&&s[i]<='Z') s[i]=(((int)s[i]-'A'+k)%26)+'A';
    }
    printf("ciphertext: %s\n",s);
    return 0;
}