// Implement Travelling Salesman Problem (TSP) problem using proper algorithm design technique.
// Shuvankar Roy    CSE/16/32   date : 19/11/2018   time : 12:12:10

#include <stdio.h>
#include <stdlib.h>
#define INF 9999 

int e, nVertices, **graph,*visited,minCost,**t,startV;

/*function prototype declaration*/
void input(); // Function for taking input from user
void make_zero_visited(); // Function for resetting visited array 
void print_graph(); // print the user provided graph
void TSP(int); // Function for Travelling salesman problem
void printRes(); // Function to print the TSP solution 
int findNextVertex(int); // Function to find next vertex

int main() {
	input();
	print_graph();

	TSP(startV); // call TSP() with starting node
	printRes(); // print the traversal path
	
	/*free up allocated memory*/
	free(visited);
	free(graph);
	free(t);
	return 0;
}

void input(){ // taking input from user 
	int i,j;
	printf("Enter number of vertices : ");
	scanf("%d",&nVertices);
	printf("Enter the start vertex for the TSP problem : ");
	scanf("%d",&startV);
	
	//dynamic memory allocation for graph and visited and t;
	visited = (int *)calloc(sizeof(int),nVertices+1);
	
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

void TSP(int startVertex){
    int i,j,minPath,minIndex,vertexCount = 1,currentVertex,nextVertex;
	make_zero_visited();
	visited[startVertex] = 1;
	currentVertex = startVertex;
	while(vertexCount < nVertices){ // checking if all vertices are exhausted
		nextVertex = findNextVertex(currentVertex); // finding nearest vertex
		minPath = graph[currentVertex][nextVertex]; // distance of nextVertex
		if(minPath == INF){ // check if there exist any edge 
			printf("Traversal Is not possible\n");
			exit(0);
		}
		minCost += minPath; // update total traversal distance
		visited[nextVertex] = 1; // update visited array
		// updating t matrix
		t[vertexCount][1] = currentVertex;
		t[vertexCount][2] = nextVertex;
		t[vertexCount][3] = minPath;
		t[vertexCount][4] = minCost;
		
		currentVertex = nextVertex;
		vertexCount++;
	}
	if(graph[currentVertex][startVertex] < INF){
		// checking if there exist any edge from last to initial node 
		minPath = graph[currentVertex][startVertex];
		minCost += minPath;
		visited[currentVertex] = 1;

		// updating t matrix
		t[vertexCount][1] = currentVertex;
		t[vertexCount][2] = startVertex;
		t[vertexCount][3] = minPath;
		t[vertexCount][4] = minCost;

	}
	else{ // traversal not possible
		printf("Traversal Is not possible\n");
		exit(0);
	}
}

int findNextVertex(int row){ // finding the next vertex to visit by row
	int i;
	int minDistance = INF;
	int minIndex = 1;
	for(i=1; i<=nVertices; i++){
		if(graph[row][i] < minDistance && visited[i]==0){
			// check for unvisited minimum distant node
			minIndex = i;
			minDistance = graph[row][i];
		}
	}
	return minIndex; // return the nearest unvisited node
}

void make_zero_visited(){ // reset the visited[1:nVertices] array
	int i;
	for(i=0; i<=nVertices; i++){
		visited[i] = 0;
	}
}

void printRes(){ // print the traversal result
	int i;
	printf("\nMinimum cost for TSP problem is : %d",minCost);
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
