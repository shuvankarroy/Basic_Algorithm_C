// Program for Job Sequncing and to generate profit for corresponding profit
// Shuvankar Roy 	CSE/16/32	date : 14/09/2018 	time : 18:12:14

#include <stdio.h>
#include <stdlib.h>

int *activity, size, *solution, *start, *finish, solutionSize;

//function prototype declaration
void input(); // for taking input from user
void print(); // for printing all data
void activitySchedule(int *,int *,int *); // for scheduling job and return profit
void setSolution(); // set all location of solution array with -999 i.e free space
void bubbleSort(int *,int *,int *); // for sorting w.r.t profit
void swap(int *,int *,int *,int,int); // for qwapping required in sorting
int maxDeadline(); // extract maximum deadline from the input to intialize solution

int isEmpty(int,int);
void createSolution(); // create solution array
void printSolution(); // print solution array

int main() {
	int totalProfit;
	printf("Enter total number of Activity : ");
	scanf("%d",&size);
	
	// allocating memory dynamically
	activity = (int*)calloc(sizeof(int),size);
	start = (int*)calloc(sizeof(int),size);
	finish = (int*)calloc(sizeof(int),size);
	
	// taking input from user and showing their input
	input();
	printf("\nData provided by user :\n");
	print();

	// calling to schedule activity
	activitySchedule(finish,activity,start);
	return 0;
}

void input(){
	int i;
	printf("\nEnter the details of each job :\n");
	for(i=0; i<size; i++){
		printf("Enter Start & End time for Activity %d : ",i+1);
		scanf("%d %d",&start[i],&finish[i]);
		activity[i] = i+1;
	}
}

void print(){
	int i;
	for(i=0; i<size; i++){
		printf("Activity %d :\tStart : %d\tFinish : %d\t\n",activity[i],start[i],finish[i]);           
	}
}

void activitySchedule(int *target,int *aux1,int *aux2){
	bubbleSort(target,aux1,aux2);
	printf("\nCurrent Status of Activity list after sorting :\n");
	print();
	
	solutionSize = maxDeadline();
	printf("The maximum deadline is : %d\n ",solutionSize);
	solution = (int *)calloc(sizeof(int),solutionSize);
	
	setSolution();
	createSolution();
	printf("The optimum activity sequencing is :\n");
	printSolution();
}


void createSolution(){
	int i,j;
	for(i=0; i<size; i++){
		printf("for activity %d :\n",activity[i]);
		if(isEmpty(start[i],finish[i])){
			printSolution();
			for(j=start[i]; j<finish[i]; j++){
				solution[j] = activity[i];
			}
			printSolution();
		}
	}
}

int isEmpty(int begin,int end){
	int i,j;
	for(i=begin; i<end; i++){
		if(solution[i]!= -999)
			return 0;
	}
	return 1;
}

int maxDeadline(){
	int i;
	int max = finish[0];
	for(i=1;i<size;i++){
		if(max<finish[i])
			max = finish[i];
	}
	return max;
}

void bubbleSort(int *arr,int *aux1,int *aux2){
	int i,j;
	for(i=0; i<size-1; i++){
		for(j=0; j<size-i-1; j++){
			if(arr[j] > arr[j+1]) //for descending order sorting
				swap(arr,aux1,aux2,j,j+1);
		}
	}
}

void swap(int *arr,int *aux1,int *aux2,int i,int j){
	int temp;
	
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
	
	temp = aux1[i];
	aux1[i] = aux1[j];
	aux1[j] = temp;
	
	temp = aux2[i];
	aux2[i] = aux2[j];
	aux2[j] = temp;

}


void setSolution(){
	int i;
	for(i=0;i<solutionSize;i++)
		solution[i] = -999;
}

void printSolution(){
	int i;
	for(i=0; i<solutionSize; i++)
		printf("A%d\t",solution[i]);
	printf("\n");
}
