#include<stdio.h>
#include<cs50.h>

int checksum(int arr[],int dig);

int main(){
    printf("Number: ");
    long long card=get_long_long();
    int arr[16]={};
    long long temp=card;
    int dig=0;
    while(temp!=0){
        arr[dig]=temp%10;
        temp/=10;
        dig++;
    }
    if(!checksum(arr,dig)){
        if(dig==15&&arr[dig-1]==3&&(arr[dig-2]==4||arr[dig-2]==7)) printf("AMEX\n");
        else if(dig==16&&arr[dig-1]==5&&(arr[dig-2]>0&&arr[dig-2]<6)) printf("MASTERCARD\n");
        else if((dig==16||dig==13)&&arr[dig-1]==4) printf("VISA\n");
        else printf("INVALID\n");
    }
    else printf("INVALID\n");
}

int checksum(int arr[],int dig){
    int sum=0;
    for(int i=0;i<dig;i++){
        if(i%2==0) sum+=arr[i];
        else{
            if(arr[i]<5) sum+=arr[i]*2;
            else sum+=(1+((arr[i]*2)%10));
        }
    }
    return sum%10;
}