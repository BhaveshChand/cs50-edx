#include<stdio.h>
#define MAX 65536

int *bub_sort(int arr[],int n){
	int swapcounter=-1;
	for(int i=0;i<n-1;i++){
		swapcounter=0;
		for(int j=0;j<n-1-i;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				swapcounter++;
			}
		}
		if(!swapcounter) break;
	}
	return arr;
}

int *sel_sort(int arr[],int n){
	for(int i=0;i<n-1;i++){
		int min,j;
		for(min=i,j=i;j<n;j++){
			if(arr[min]>arr[j]) min=j;
		}
		if(min!=i){
			int temp=arr[min];
			arr[min]=arr[i];
			arr[i]=temp;
		}
	}
	return arr;
}

int *ins_sort(int arr[],int n){
	for(int i=1;i<n;i++){
		int temp=arr[i];
		int j;
		for(j=i-1;j>=0;j--){
			if(arr[j]>temp) arr[j+1]=arr[j];
			else break;
		}
		arr[j+1]=temp;
	}
	return arr;
}

int *mer_sort(int arr[],int low,int high){
	if(high-low<1) return arr;
	mer_sort(arr,low,(low+high)/2);
	mer_sort(arr,((low+high)/2)+1,high);
	int a[high-low+1],i,j,k;
	for(i=low,j=((low+high)/2)+1,k=0;(i<=((low+high)/2))&&(j<=high);){
		if(arr[i]<=arr[j]) a[k++]=arr[i++];
		else a[k++]=arr[j++];
	}
	if(j>high){
		for(;k<=high-low;){
			a[k++]=arr[i++];
		}
	}
	else if(i>((low+high)/2)){
		for(;k<=high-low;){
			a[k++]=arr[j++];
		}
	}
	for(i=low,k=0;i<=high;){
		arr[i++]=a[k++];
	}
	return arr;
}

int *count_sort(int arr[],int n){
	int count[MAX]={};
	for(int i=0;i<n;i++) count[arr[i]]++;
	int i=0;
	for(int j=0;j<MAX;j++){
		while(count[j]!=0){
			arr[i++]=j;
			count[j]--;
		}
	}
	return arr;
}

int lin_srch(int arr[],int n,int target){
	for(int i=0;i<n;i++){
		if(arr[i]==target) return i;
	}
	return -1;
}

int bin_srch(int arr[],int n,int target){
	int low=0,high=n-1,mid;
	while(low<=high){
		mid=(low+high)/2;
		if(arr[mid]==target) return mid;
		else if(arr[mid]<target) low=mid+1;
		else high=mid-1;
	}
	return -1;
}

int main(){
	int n;
	scanf("%d",&n);
	int a[n],b[n];
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	
	for(int i=0;i<n;i++) b[i]=a[i];
	bub_sort(b,n);
	for(int i=0;i<n;i++) printf("%d\n",b[i]);
	printf("\n");
	
	for(int i=0;i<n;i++) b[i]=a[i];
	sel_sort(b,n);
	for(int i=0;i<n;i++) printf("%d\n",b[i]);
	printf("\n");
	
	for(int i=0;i<n;i++) b[i]=a[i];
	ins_sort(b,n);
	for(int i=0;i<n;i++) printf("%d\n",b[i]);
	printf("\n");
	
	for(int i=0;i<n;i++) b[i]=a[i];
	mer_sort(b,0,n-1);
	for(int i=0;i<n;i++) printf("%d\n",b[i]);
	printf("\n");
	
	for(int i=0;i<n;i++) b[i]=a[i];
	count_sort(b,n);
	for(int i=0;i<n;i++) printf("%d\n",b[i]);
	printf("\n");
	
	printf("%d\n\n",lin_srch(a,n,23));
	
	printf("%d\n\n",lin_srch(a,n,1));
	
	printf("%d\n\n",bin_srch(b,n,23));
	
	printf("%d\n\n",bin_srch(b,n,1));
}