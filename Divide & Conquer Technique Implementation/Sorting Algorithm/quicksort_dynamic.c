#include <stdio.h>
#include <stdlib.h>
/*Program for quick sort */
int count = 0;
void Quick_Sort(int*,int,int);/*Function for quicksort*/
int partition(int*,int,int);/*Function for partitioning the array*/
void printArr(int*,int);/*Function for printing the array*/
int main() {
	int i,n,*Arr;
	printf("Enter number of elements :");
	scanf("%d",&n);
    Arr = (int *)calloc(n,sizeof(int));
	printf("Enter the elements of the array :\n");
	for(i=0;i<n;i++){
		scanf("%d",&Arr[i]);
	}
	printf("The entered unsorted data is : \n");
	printArr(Arr,n);
	Quick_Sort(Arr,0,n-1);
	printf("\nThe sorted data using Merge Sort is : \n");
	printArr(Arr,n);
	printf("\nNumber of steps required for Quick Sort : %d",count);	
}
void Quick_Sort(int *Arr,int start,int end){
	int p;
	if (start < end){
		count++;
		p = partition(Arr,start,end);
		Quick_Sort(Arr,start,p-1);
		Quick_Sort(Arr,p+1,end);
	}
}

int partition(int *Arr,int low,int high){
	int i,j,pivot,temp;
	i = low;
	j = high;
	pivot = Arr[low];
	while(i < j){
		while(pivot >= Arr[i])
			i++;
		while(pivot < Arr[j])
			j--;
		if(i < j){
			temp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = temp;
		}
	}
	temp = Arr[low];
	Arr[low] = Arr[j];
	Arr[j] = temp;
	return j;
}
void printArr(int *Arr,int n){
	int i;
	for(i=0;i<n;i++)
		printf("%d  ",Arr[i]);
}