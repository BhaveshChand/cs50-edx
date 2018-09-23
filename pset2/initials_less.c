#include<cs50.h>
#include<stdio.h>
#include<ctype.h>

int main(){
    string s=get_string();
    int i=0;
    printf("%c",toupper(s[0])); //print 1st char of 1st word 
    while(s[i+1]!=0){ //iterate through the string
        if(s[i]==' ') printf("%c",toupper(s[i+1])); //look for spaces and print the next char
        i++;
    }
    printf("\n");
}