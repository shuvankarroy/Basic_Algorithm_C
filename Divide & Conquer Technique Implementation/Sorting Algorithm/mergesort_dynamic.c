#include <stdio.h>
#include <stdlib.h>
/*Program for merge sort */
int count = 0;

void Merge_Sort(int*,int,int,int*);/*Function for merge sort*/
void Merge(int*,int,int,int,int*);/*Function for merging*/
void printArr(int*,int);/*Function for printing array*/

int main() {
	int i,size,*Arr,*b;
	printf("Enter number of elements :");
	scanf("%d",&size);
	
	Arr = (int *)calloc(size, sizeof(int));
	b = (int *)calloc(size, sizeof(int));
	
	printf("Enter the elements of the array :\n");
	for(i=0 ; i<size ; i++){
		scanf("%d",&Arr[i]);
	}
	printf("The entered unsorted data is : \n");
	printArr(Arr,size);
	Merge_Sort(Arr,0,size-1,b);/*Calling Mergesort function*/
	printf("\nThe sorted data using Merge Sort is : \n");
	printArr(Arr,size);
	printf("\nNumber of steps required for Merge Sort : %d",count);	
	return 0;
}

void Merge_Sort(int* Arr,int start,int end,int* b){
	int mid = (start+end)/2;
	if (start<end){
		count++;
		Merge_Sort(Arr,start,mid,b);/*recursively calling mergesort function with first half*/  
		Merge_Sort(Arr,mid+1,end,b);/*recursively calling mergesort function with second half*/
		Merge(Arr,start,mid,end,b);
	} 
}

void Merge(int* Arr,int start,int mid,int end,int* b){
	int p,q,r,s;
	p = start;
	q = start;
	r = mid+1;
	while( p <= mid && r <= end){
		if( Arr[p] < Arr[r] )
			b[q++] = Arr[p++];
		else
			b[q++] = Arr[r++];
	}
	while(p <= mid){
		b[q++] = Arr[p++];
	}
	while(r <= end){
		b[q++] = Arr[r++];
	}
	s = start;
	while(s <= end){
		Arr[s] = b[s];
		s++;
	}
}

void printArr(int *x,int n){
	int i;
	for(i=0 ; i<n ; i++)
		printf("%d  ",x[i]);
}
