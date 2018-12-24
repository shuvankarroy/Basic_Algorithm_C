#include <stdio.h>
#include <stdlib.h>

int **graph,nVertices,*visited,startVertex,previous;

void input();
void DFS(int,int);
void printGraph();

int main() {
	input();
	printGraph();
	printf("The Traversal by DFS algorithm is :\n");
	printf("***Predecessor are provided in the parenthesis ()***\n");
	previous = 0;
	DFS(startVertex,0);
	return 0;
}

void input(){
	int i,j;
	printf("Enter number of vertices : ");
	scanf("%d",&nVertices);
	printf("Enter the start vertex : ");
	scanf("%d",&startVertex);
	graph = (int **)calloc(sizeof(int *),nVertices+1);
	for(i=0; i<=nVertices; i++){
		graph[i] = (int *)calloc(sizeof(int),nVertices+1);	
	}
	
	visited = (int *)calloc(sizeof(int),nVertices+1);
	visited[0] = 0;

	printf("Enter the adjacency matrix : \n");
	for(i=1; i<=nVertices; i++){
		for(j=1; j<=nVertices; j++){
			scanf("%d",&graph[i][j]);
		}

		visited [i] = 0;
	}
}

void printGraph(){
	int i,j;
	printf("The Adjacency Matrix is : \n");
	for(i=1; i<=nVertices; i++){
		for(j=1; j<=nVertices; j++){
			printf("%d\t",graph[i][j]);
		}
		printf("\n");
	}
}

void DFS(int v,int previous){
	int w,i;
	visited[v] = 1;
	printf(" --> %d (%d) ",v,previous);
	for(w=1; w<=nVertices; w++){
		if(graph[v][w] && !visited[w]){
			DFS(w,v);	
		}
	}
}
