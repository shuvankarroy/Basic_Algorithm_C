#include <stdio.h>
#include <stdlib.h>

typedef struct pair{
	int min;
	int max;
}tuple;

tuple* max_min_dc(int*,int ,int);
void printArr(int*,int,int);

int main(){
	int i,n,*Arr;
	tuple* result;
	printf("Enter number of elements :");
	scanf("%d",&n);
	Arr = (int *)calloc(n, sizeof(int));
	printf("Enter the elements of the array :\n");
	for(i=0;i<n;i++)
		scanf("%d",&Arr[i]);
	printf("The entered unsorted data is : \n");
	printArr(Arr,0,n);
	result = max_min_dc(Arr,0,n-1);
	printf("\nMaximum number : %d \nMinimum number : %d\n",result->max,result->min);
	free(Arr);
	return 0;
}

void printArr(int *Arr,int start,int end){
	int i;
	for(i=start;i<end;i++)
		printf("%d  ",Arr[i]);
}

tuple* max_min_dc(int *Arr,int start,int end){
	tuple *right,*left,*final;
	int mid;
	right = (tuple*)malloc(sizeof(tuple));
	left = (tuple*)malloc(sizeof(tuple));
	final = (tuple*)malloc(sizeof(tuple));
	if(start == end){
		final->max = Arr[start];
		final->min = Arr[start];
	}
	else if(end - start == 1){
		if(Arr[start] > Arr[end]){
			final->max = Arr[start];
			final->min = Arr[end];
		}
		else{
			final->max = Arr[end];
			final->min = Arr[start];
		}
	}
	else{
		mid = ( start + end ) / 2;
		left = max_min_dc(Arr,start,mid);
		right = max_min_dc(Arr,mid+1,end);
		if(right->min < left->min)
			final->min = right->min;
		else
			final->min = left->min;
		if(right->max > left->max)
			final->max = right->max;
		else
			final->max = left->max;
	}
	free(right);
	free(left);
	return final;
}