// Program for Job Sequncing and to generate profit for corresponding profit
// Shuvankar Roy 	CSE/16/32	date : 18/11/2018 	time : 18:12:14

#include <stdio.h>
#include <stdlib.h>

int *job,size,*solution,*deadline,*profit,solutionSize;

//function prototype declaration
void input(); // for taking input from user
void print(); // for printing all data
int jobSchedule(int *,int *,int *); // for scheduling job and return profit
void setSolution(); // set all location of solution array with -999 i.e free space
int maxDeadline(); // extract maximum deadline from the input to intialize solution
void createSolution(); // create solution array
void printSolution(); // print solution array
void bubbleSort(int *,int *,int *); // for sorting w.r.t profit
void swap(int *,int *,int *,int,int); // for qwapping required in sorting
int calculateProfit(); // calculate total profit after creating job Sequnce

int main() {
	int totalProfit;
	// taking input from user and showing their input
	input();
	printf("\nData provided by user :\n");
	print();
	
	//calling function to schedule the job and to get corresponding profit
	totalProfit = jobSchedule(profit,deadline,job);
	printf("\nTotal profit due to the generated optimum job sequence : %d\n",totalProfit);
	
	// free dynamically allocated memory
	free(deadline);
	free(profit);
	free(job);
	free(solution);
	
	return 0;
}

void input(){
	int i;
	printf("Enter total number of jobs : ");
	scanf("%d",&size);
	
	// allocating memory dynamically
	deadline = (int*)calloc(sizeof(int),size);
	profit = (int*)calloc(sizeof(int),size);
	job = (int*)calloc(sizeof(int),size);
	printf("\nEnter the details of each job :\n");
	for(i=0; i<size; i++){
		printf("Enter profit & deadline for job %d : ",i+1);
		scanf("%d %d",&profit[i],&deadline[i]);
		job[i] = i+1;
	}
}

int jobSchedule(int *target,int *aux1,int *aux2){
	bubbleSort(target,aux1,aux2);
	
	solutionSize = maxDeadline();
	printf("The maximum deadline is : %d \n",solutionSize);
	
	solution = (int *)calloc(sizeof(int),solutionSize);
	setSolution();
	createSolution();
	printf("The optimum job sequencing is :\n");
	printSolution();
	return calculateProfit();
}

void bubbleSort(int *arr,int *aux1,int *aux2){
	int i,j;
	for(i=0; i<size-1; i++){
		for(j=0; j<size-i-1; j++){
			if(arr[j] < arr[j+1]) //for descending order sorting
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

void createSolution(){
	int i,r,x,k;
	for(i=0; i<size; i++){
		for(r = deadline[i]-1;r>=0;r--){
			if(!solution[r]){ // checking if time slot is empyty
				solution[r] = job[i]; // assigning job to that time slot
				break;
			}
		}
	}
}

int calculateProfit(){
	int i,total = 0;
	for(i=0;i<solutionSize;i++){
		if(solution[i]) // check if solution[i] has any job scheduled or default 0 value
			total += profit[i];
	}
	return total; // return the ttotal calculated profit
}

int maxDeadline(){
	int i;
	int max = deadline[0];
	for(i=1;i<size;i++){
		if(max<deadline[i])
			max = deadline[i];
	}
	return max; // return the max deadline value
}

void setSolution(){
	int i;
	for(i=0;i<size;i++)
		solution[i] = 0;
}

void print(){
	int i;
	for(i=0; i<size; i++){
		printf("job %d :\tprofit : %d\tdeadline : %d\t\n",job[i],profit[i],deadline[i]);           
	}
}

void printSolution(){
	int i;
	for(i=0; i<solutionSize; i++)
		printf("J%d\t",solution[i]);
	printf("\n");
}
