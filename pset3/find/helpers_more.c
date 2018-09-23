/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

#define MAX 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	if(n<1) return false;
	int low=0,high=n-1,mid;
	bool flag=false;
	while(low<=high){
		mid=(low+high)/2;
		if(values[mid]==value){
		    flag=true;
		    break;
		}
		else if(values[mid]<value) low=mid+1;
		else high=mid-1;
	}
    return flag;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int count[MAX]={};
	for(int i=0;i<n;i++) count[values[i]]++;
	int i=0;
	for(int j=0;j<MAX;j++){
		while(count[j]!=0){
			values[i++]=j;
			count[j]--;
		}
	}
    return;
}
