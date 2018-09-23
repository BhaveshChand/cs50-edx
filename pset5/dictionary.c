/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include "dictionary.h"

node root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int i=0;
    node* temp=&root;
    while(word[i]!='\0'&&temp!=NULL){
        if(word[i]=='\'') temp=temp->letter[0];
        else if(word[i]>='A'&&word[i]<='Z') temp=temp->letter[word[i]-64];
        else if(word[i]>='a'&&word[i]<='z') temp=temp->letter[word[i]-96];
        else return false;
        i++;
    }
    if(word[i]=='\0'&&temp!=NULL) return temp->end;
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *fp=fopen(dictionary,"r");
    if(fp==NULL) return false;
    char word[LENGTH+1];
    while(fscanf(fp,"%s",word)!=EOF){
        int i=0;
        node* temp=&root;
        while(word[i]!='\0'){
            if(word[i]=='\'') word[i]=0;
            else word[i]-=96;
            if(temp->letter[(int)word[i]]==NULL){
                node *new=calloc(sizeof(node),1);
                if(new==NULL) return false;
                temp->letter[(int)word[i]]=new;
            }
            temp=temp->letter[(int)word[i]];
            i++;
        }
        temp->end=true;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
void count(node *,unsigned int *);
unsigned int size(void)
{
    unsigned int i=0;
    count(&root,&i);
    return i;
}
void count(node *temp,unsigned int *ptr){
    for(int i=0;i<27;i++){
        if(temp->letter[i]!=NULL) count(temp->letter[i],ptr);
    }
    if(temp->end==true) (*ptr)++;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool delete(node *);
bool unload(void)
{
    return delete(&root);
}
bool delete(node *temp){
    for(int i=0;i<27;i++){
        if(temp->letter[i]!=NULL){
            if(delete(temp->letter[i])==false) return false;
            free(temp->letter[i]);
            if(temp->letter[i]==NULL) return false;
        }
    }
    return true;
}
