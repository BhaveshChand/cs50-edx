#include<stdio.h>
#include<cs50.h>

int main(){
    int x;
    do{
        printf("Height: ");
        x=get_int();
    }while(x<0||x>23);
    for(int i=1;i<=x;i++){
        for(int j=0;j<x-i;j++) printf(" ");
        for(int j=0;j<i;j++) printf("#");
        printf("  ");
        for(int j=0;j<i;j++) printf("#");
        printf("\n");
    }
}