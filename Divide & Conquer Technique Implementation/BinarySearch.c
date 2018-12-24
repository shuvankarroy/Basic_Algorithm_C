#include <stdio.h>
#include <stdlib.h>
int BinSearch(int arr[],int start,int end,int x)
{
	// Recursive Function for Binary Search
	int mid;
	if(start>end) // Condition to stop recursion
		return -1; // Return -1 if element not found
	else
	{
		mid = (start + end)/2;
		if(x == arr[mid])
			return mid;
		else if(x<arr[mid])
			return BinSearch(arr,start,mid-1,x); // Reducing to left half
		else
			return BinSearch(arr,mid+1,end,x); // Reducing to right half
	}
}
int main()
{
	int arr[100],size,i,search,loc;
	printf("Enter total number of elements :");
	scanf("%d",&size);
	printf("Enter %d Array Elements in Sorted Array :\n",size);
	// Taking Input from User
	for(i=0;i<size;i++)
		scanf("%d",&arr[i]);
	printf("Enter the element to search : ");
	scanf("%d",&search);
	// Calling Binary Search Function
	loc = BinSearch(arr,0,size-1,search);
	if(loc == -1)
		printf("The element %d is not present in the array",search);
	else
		printf("The element %d is present at location %d of the array ",search,loc+1);
	return 0;
}
