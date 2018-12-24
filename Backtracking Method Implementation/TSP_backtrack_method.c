#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define INF 9999

// declaring required variables at global scope
int e, nVertices, **graph, *visited, mincost, **t, source, *Path, vertexCount = 0;
int times = 0;

/*function prototype declaration*/
void input(); // Function for taking input from user
void make_zero_visited(); // Function for resetting visited array 
void print_graph(); // Function to print the cost matrix provided by user 
void TSP(int); // Function for Travelling salesman problem
int findNextVertex(int,int); // Function to find next adjacent unvisited vertex
void calculateMinPath(); // Function to calculate minPath and fill t[nVertices][4] matrix based on the vertex sequence Path[1:nVertices] obtained from TSP()
void printResult(); // print the optimum path result found by TSP()
void freeMemory(); // free up the dynamically allocated memory space

int main() {
    input();
    print_graph();
    TSP(source);
    printResult();
    freeMemory();
    return 0;
}

void input(){ // taking input from user 
	int i,j;
	printf("Enter number of vertices : ");
	scanf("%d",&nVertices);
	printf("Enter the start vertex for the TSP problem : ");
	scanf("%d",&source);
	
	//dynamic memory allocation for graph and visited and t;
	visited = (int *)calloc(sizeof(int),nVertices+1);
	
    Path = (int *)calloc(sizeof(int),nVertices+2);

	graph = (int **)calloc(sizeof(int),nVertices+1);
	for(i=0; i<=nVertices; i++){
		graph[i] = (int *)calloc(sizeof(int),nVertices+1);
	}
	
	t = (int **)calloc(sizeof(int),nVertices+1);
	for(i=0;i<=nVertices;i++){
		t[i] = (int *)calloc(sizeof(int),5);
	}
	
	printf("Enter the cost or weight matrix representation of the graph :\n");
    printf("***Enter 0 in place of no connection***\n");
    for(i=1; i<=nVertices; i++){
        for(j=1; j<=nVertices; j++){
        	scanf("%d",&graph[i][j]);
            if(graph[i][j] == 0){ // set absent edges with INF
                graph[i][j] = INF;
       	    }                  
        }
    }
    make_zero_visited(); // reset the visited[1:nVertices] to all zero
}

void TSP(int current){
    int next,i;
    visited[current] = 1;
    Path[++vertexCount] = current;
    if(vertexCount == nVertices){ // All vertices are visited.
        if(graph[current][source] != INF){ // Connection between starting and end. Solution found
            Path[++vertexCount] = source;
            calculateMinPath(); // function to fill the t matrix and calculate total path distance
            printResult(); // print result of traversal
            freeMemory(); // free up the dynamically allocated memory
            exit(0); // as the optimum minimum path is found and furthur backtracking not required
        }
        else{
            vertexCount--;
            visited[current] = 0;
            return; // backtrack to previous state to find another path for traversal
        }
    }
    
    else{
        for(i=1; i<=nVertices; i++){
            next = findNextVertex(current,i);
            if(next == 0){ // All adj. vertices are visited, No connection.
                vertexCount--; // decrementing vertex count as backtrcking will be performed
                visited[current] = 0; // reset the visited field of current vertex as the path is not feasible
                return; // backtrack to previous state to find another path for traversal
            }
            else{ // Nearest unvisited adjacent found
                TSP(next); // recursive call TSP() with nearest unvisited adjacent vertex as parameter
            }
        }
    }
}

int findNextVertex(int u,int pos){ // Function to find the "pos"-th unvisited adjacent vertex of u
    int i,j,v,temp;
    int adjacentVertices[nVertices+1],adjacentDistance[nVertices+1];
    // initialize adjacentVertices[1:nVertices] with adjacent vertices of u
    // initialize adjacentDistance[1:nVertices] with distance of adjacent vertices from u
    for(v=1; v<=nVertices; v++){
        adjacentVertices[v] = v;
        adjacentDistance[v] = graph[u][v];
    }

    // sort in ascending order adjacentVertices[1:nVertices] w.r.t corresponding adjacentDistance from vertex "u"
    for(i=1; i<=nVertices; i++){ // complexity can be furthur reduced if we store the sorted sequence for each vertex
        for(j=1; j<nVertices; j++){
            if(adjacentDistance[j] > adjacentDistance[j+1]){
                temp = adjacentVertices[j];
                adjacentVertices[j] = adjacentVertices[j+1];
                adjacentVertices[j+1] = temp;

                temp = adjacentDistance[j];
                adjacentDistance[j] = adjacentDistance[j+1];
                adjacentDistance[j+1] = temp;
            }
        }
    }
    for(i=pos; i<=nVertices; i++){ // if adjacentVertices[pos] is visited then next unvisited adjacent is returned 
        if((visited[adjacentVertices[i]] == 0) && (adjacentDistance[i] != INF))
            return adjacentVertices[i]; 
    }
    return 0; // return 0 if no unvisited nearest adjacent vertex found
}

void make_zero_visited(){ // reset the visited[1:nVertices] array
	int i;
	for(i=0; i<=nVertices; i++){
		visited[i] = 0;
	}
}

void print_graph(){ // print the cost matrix
	int i,j;
	printf("The cost matrix is :\n");
	for(i=1; i<=nVertices; i++){
		for(j=1; j<=nVertices; j++){
			printf("%d\t",graph[i][j]);
		}
		printf("\n");
	}
}

void calculateMinPath(){ // function to calculate minPath and fill the t[1:nVertices][4] matrix
    int i;
    mincost = 0;
    for(i=1; i<=nVertices; i++){
        t[i][1] = Path[i];
		t[i][2] = Path[i+1];
		t[i][3] = graph[Path[i]][Path[i+1]];
		mincost += graph[Path[i]][Path[i+1]];
        t[i][4] = mincost;
    }
}

void printResult(){  // print the traversal result
    int i;
     // if backtrack completes and returns to main() then count value = 0, i.e. solution not found
    if(vertexCount){ // checking if count value is non-zero
        printf("\nMinimum cost for TSP problem is : %d",mincost);
        printf("\nOptimum Path for traversal is : \n");
        for(i=1; i<=nVertices;i++){
            if(i == 1)
                printf("--> V%d ",t[i][1]);
            printf("--> V%d ",t[i][2]);
        }
        printf("\nThe t matrix (distance in between vertices) is : \n");
        printf("source \t destination \t min \t mincost\n");
        for(i=1; i<=nVertices; i++){
            printf("%d \t\t %d \t %d \t %d",t[i][1],t[i][2],t[i][3],t[i][4]);
            printf("\n");
        }
    }
    else // no solution found
        printf("\nThe provided graph is impossible to solve using TSP backtracking as it may contains no cycle");
}

void freeMemory(){ // free the dynamically allocated memory
    int i;
    free(visited);
    free(Path);
    free(t);
    free(graph);
}
