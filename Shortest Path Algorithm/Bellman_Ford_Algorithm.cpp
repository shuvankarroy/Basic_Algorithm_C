// Program for Bellman–Ford algorithm for Single Source Shortest Path where negative Edge-Weight is allowed
// Shuvankar Roy 	CSE/16/32	date : 17/11/2018 	time : 15:10:14
//Implement Single Source Shortest Path problem, where negative Edge-Weight is allowed using proper algorithm design technique.
//Mention the Compiler used in your program. Mention the complexity value of your algorithm.



# include <stdio.h>
# include <stdlib.h>
# define INF 99999
# define true 1
# define false 0

/*function prototype declaration*/
void input(); // Function for taking user input and Dynamic memory allocations
void Initialize_Single_Src(); 
void print_graph(); // Print the cost matrix provided by user
void Relax(int, int); // Function for Relaxation
int BellmanFord();
void printRes(int);

// required variable declaration
int **graph, *d, *pi, *path, nVertices, startVertex, flag;

int main(){

	input();
	print_graph();
	printRes(BellmanFord());

	/*free allocated memory*/
	free(d);
	free(pi);
	free(path);
	free(graph);
	return 0;
}

void input(){  // Function for taking user input and Dynamic memory allocations
	int i,j,k;
	printf("Enter number of vertices : ");
	scanf("%d",&nVertices);
	printf("Enter starting vertex : ");
    scanf("%d",&startVertex);
	
	//dynamic memory allocation for graph[1:nVertices][1:nVertices], d[1:nVertices], pi[1:nVertices], path[1:nVertices];
	
	d = (int *)calloc(sizeof(int),nVertices+1);
    pi = (int *)calloc(sizeof(int),nVertices+1);
	path = (int *)calloc(sizeof(int),nVertices+1);

	graph = (int **)calloc(sizeof(int),nVertices+1);
	for(i=0; i<=nVertices; i++){
		graph[i] = (int *)calloc(sizeof(int),nVertices+1);
	}
	printf("Enter the cost or weight matrix representation of the graph :\n");
    printf("***Enter 0 in place of no connection***\n");
    for(i=1; i<=nVertices; i++){
        for(j=1; j<=nVertices; j++){
        	scanf("%d",&graph[i][j]);
            if(graph[i][j] == 0){ // making no connection as infinity
                graph[i][j] = INF;
       	    }                  
        }
    }
}

void print_graph(){ // Print the cost matrix provided by user
	int i,j;
	printf("The cost matrix is :\n");
	for(i=1 ;i<=nVertices ;i++){
		for(j=1;j<=nVertices;j++){
			printf("%d\t",graph[i][j]);
		}
		printf("\n");
	}
}

void Initialize_Single_Src(){
    int i;
    for (i=1; i<= nVertices; i++){
		d[i] = INF; // in algorithm : v.d = INF 
		pi[i] = 0; // in algorithm : v.pi = NIL
	}
	d[startVertex] = 0;
}

void Relax(int u, int v){ // Function for Relaxation
	if(d[v] > d[u] + graph[u][v]) { // condition to check if relaxation is possible
		d[v] = d[u] + graph[u][v]; // updating distance of v
		pi[v] = u; // updating adjacent vertev of v
		flag = 1;
	}
}

int BellmanFord(){ // Algorithm Bellman Ford implementation
	int u,v,counter,i,j,k;
	Initialize_Single_Src();
	for(i=1; i<nVertices; i++){
		// relax each edge (u,v) belongs to G.E
		flag = 0;
		for(u=1; u<=nVertices; u++){
			for(v=1; v<=nVertices; v++){
				if(graph[u][v] < INF) // if condition is true then (u,v) is an edge
					Relax(u,v);
			}
		}
		if(flag == 0)  // to stop the loop from execution if no relaxation happens
			break;
	}

	// to check if their exist any negative edge cycle in the graph
	for(u=1; u<=nVertices; u++){
			for(v=1; v<=nVertices; v++){
				if(graph[u][v] < INF) // if condition is true then (u,v) is an edge
					if(d[v] > d[u] + graph[u][v])
						return false; // return false if negative edge cycle exists
			}
		}
	return true; // return true if solution is found
}

void printRes(int possible){
	int i;
	if(possible){ // check if solution is available or not
		printf("\nvertex\tadjacency\tdistance\n");
		for(i=1; i<=nVertices; i++){
			printf("%d\t\t%d\t%d\t",i,pi[i],d[i]);
			printf("\n");
		}
		exit(0);
	}
	else{ // print solution not found
		printf("The graph contains an negative edge loop, This can not be solved by BellmanFord Algorithm");
		exit(0);
	}
}
