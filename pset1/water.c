#include<stdio.h>
#include<cs50.h>

int main(){
    printf("Minutes: ");
    int x=get_int();
    printf("Bottles: %d\n",x*12);
}