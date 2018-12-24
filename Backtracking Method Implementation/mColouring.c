// Implement Graph Coloring problem using proper algorithm design technique.
// Shuvankar Roy    CSE/16/32   date : 18/11/2018   time : 18:12:10

#include <stdio.h>
#include <stdlib.h>

// declaring required variables
int nVertices, **graph,*x,totalColour,solutionNo = 1;

/*function prototype declaration*/
void input(); // take input from user
void make_zero_x(); // reset the solution vector x 
void print_graph(); // print the adjacency matrix
void printRes(); // function to print result
void mColouring(int); // recursive algortihm for mColouring which colours vertex k
void nextValue(int); // find the next possible value for vertex k

int main() {
	input(); 
	print_graph();
	make_zero_x();
	mColouring(1); // calling recursive mColouring() algorithm
	if(solutionNo == 1){
		printf("No solution possible for the graph with %d colour\n",totalColour);
	}

	/*free up allocated memory*/
	free(x);
	free(graph);
	return 0;
}

void input(){ // taking input from user
	int i,j;
	printf("Enter total number of colours available : ");
	scanf("%d",&totalColour);
	
	printf("Enter number of vertices to be coloured with %d colour : ",totalColour);
	scanf("%d",&nVertices);

	//dynamic memory allocation for graph and solution vector x;
	
	x = (int *)calloc(sizeof(int),nVertices+2);
	
	graph = (int **)calloc(sizeof(int),nVertices+1);
	for(i=0; i<=nVertices; i++){
		graph[i] = (int *)calloc(sizeof(int),nVertices+1);
	}
	
	// Taking adjacency matrix input from user
	printf("Enter the adjacency matrix representation of the graph :\n");
    printf("***Enter 0 in place of no connection***\n");
    for(i=1; i<=nVertices; i++){
        for(j=1; j<=nVertices; j++){
        	scanf("%d",&graph[i][j]);
       	}                  
    }
}


void print_graph(){ // printing the adjacency matrix provided by user
	int i,j;
	printf("The cost matrix is :\n");
	for(i=1; i<=nVertices; i++){
		for(j=1; j<=nVertices; j++){
			printf("%d\t",graph[i][j]);
		}
		printf("\n");
	}
}

void make_zero_x(){ // reset solution array
	int i;
	for(i=0; i<=nVertices; i++){
		x[i] = 0;
	}
}

void mColouring(int k){
	do{
		nextValue(k); // find next applicable colour code for vertex k
		if(x[k] == 0) // check if no possible colour is found
			return; // backtrack
		if(k == nVertices) // check if all vertices have been coloured
			printRes();
		else 
			mColouring(k+1); // recursive call to colour (k+1)th vertex
	}while(k <= nVertices); // while vertices left to colour
}

void nextValue(int k){
	int j;
	while(1){
		x[k] = (x[k]+1) % (totalColour+1); // next highest colour
		if(x[k] == 0)
			return; // all colour codes has been exhausted
		for(j=1; j<=nVertices; j++){ 
			// check if this colour is distinct from adjacent colours 
			if((graph[k][j]  != 0) && (x[k] == x[j])){
				// if(k,j) is an edge & if adjacent vertices have the same colour
				break;
			}
		}
		if(j == nVertices+1)
			return;
	}
}

void printRes(){ // print the solution
	int i;
	printf("Solution %d : ",solutionNo++);
	for(i=1; i<=nVertices;i++)
		printf("Vertex %d = C%d\t",i,x[i]);
	printf("\n");
}
