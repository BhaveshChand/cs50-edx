#include<stdio.h>
#include<stdlib.h>

#define BLOCK_SIZE 512

int main(int argc,char *argv[]){
    if(argc!=2){
        fprintf(stderr,"Usage: ./recover image\n");
        return 1;
    }
    FILE *raw=fopen(argv[1],"r");
    if(raw==NULL){
        fprintf(stderr,"Could not open %s.\n",argv[1]);
        return 2;
    }
    int fileno=0;
    char name[8]="000.jpg";
    unsigned char *buffer=calloc(BLOCK_SIZE,1);
    int flag=0;
    FILE *jpg;
    fread(buffer,BLOCK_SIZE,1,raw);
    while(!feof(raw)){
        if(*buffer==0xff&&*(buffer+1)==0xd8&&*(buffer+2)==0xff&&(*(buffer+3))/0x10==0xe){
            flag=1;
            jpg=fopen(name,"w");
            fwrite(buffer,BLOCK_SIZE,1,jpg);
        }
        fread(buffer,BLOCK_SIZE,1,raw);
        if(flag) break;
    }
    while(!feof(raw)){
        if(*buffer==0xff&&*(buffer+1)==0xd8&&*(buffer+2)==0xff&&(*(buffer+3))/0x10==0xe){
            fclose(jpg);
            sprintf(name,"%03d.jpg",++fileno);
            jpg=fopen(name,"w");
        }
        fwrite(buffer,BLOCK_SIZE,1,jpg);
        fread(buffer,BLOCK_SIZE,1,raw);
    }
    free(buffer);
    fclose(jpg);
    fclose(raw);
}