#include<stdio.h>
#include<cs50.h>

int main(){
    float x;
    printf("O hai! ");
    do{
        printf("How much change is owed?\n");
        x=get_float();
    }while(x<0);
    int a,c=0;
    x*=100;
    a=(int)x;
    if(x-a>=0.5) a++;
    c+=a/25;
    a%=25;
    c+=a/10;
    a%=10;
    c+=a/5;
    a%=5;
    c+=a;
    printf("%d\n",c);
}