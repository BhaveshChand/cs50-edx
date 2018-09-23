/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

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
    int swapcounter=-1;
	for(int i=0;i<n-1;i++){
		swapcounter=0;
		for(int j=0;j<n-1-i;j++){
			if(values[j]>values[j+1]){
				int temp=values[j];
				values[j]=values[j+1];
				values[j+1]=temp;
				swapcounter++;
			}
		}
		if(!swapcounter) break;
	}
    return;
}
