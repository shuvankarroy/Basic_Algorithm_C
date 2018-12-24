#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* function prototype declaration */
int *solution,count = 1;
void nQueen(int,int);
int Place(int,int);
void printSol(int);

int main() {
	int n;
	
	/*taking input from user*/
	printf("Enter number of Queens : ");
	scanf("%d",&n);
	
	/*dynamically allocating memory*/
	solution = (int *)calloc(sizeof(int),n+1);
	/*calling method nQueen*/
	nQueen(1,n);
	/*free allocated memory*/
	free(solution);
	return 0;
}

void nQueen(int k,int n){
	int i;
	for(i=1; i<=n; i++){
		if(Place(k,i)){
			solution[k] = i;
			if(k == n){
				printSol(n);
			}
			else{
				nQueen(k+1,n);
			}
		}
	}
}

int Place(int k,int i){
	int j;
	for(j=1; j<k; j++){
		if((solution[j] == i) || (abs(solution[j]-i) == abs(j-k))){
			return 0;
		}
	}
	return 1;
}

void printSol(int n){
	int i,j;
	printf("\nThe solution %d on checkboard is : \n",count++);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(solution[i] == j)
				printf("%d\t",i);
			else
				printf("*\t");
		}
		printf("\n");
	}
}
