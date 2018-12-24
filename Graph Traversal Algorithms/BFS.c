#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int **graph,nVertices,*visited,startVertex;

int Q[100],startQ,endQ;

// defining function prototypes
void input();
void BFT();
void BFS(int);
void printGraph();

// for queue operations
void insertQ(int);
int extractQ();

int main() {
	input();
	printGraph();
	printf("The Traversal by BFS algorithm is :\n");
	BFT(startVertex);
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

	startQ = 1;
	endQ = 0;

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

void BFT(int start){
	int i;
	BFS(start);
	for(i=1; i<=nVertices; i++){
		if(!visited[i]){
			BFS(i);
		}
	}
}

void BFS(int v){
	int u,w,i;
	u = v;
	visited[v] = 1;
	insertQ(u);
	printf("--> %d",u);
	while(1){
		u = Q[startQ];
		for(w=1; w<=nVertices; w++){
			if(!visited[w] && graph[u][w]){
				insertQ(w);
				visited[w] = 1;
				printf("--> %d",w);
			}
		}
		if(startQ>endQ)
			return;
		extractQ();
	}
}

void insertQ(int v){
	Q[++endQ] = v;
}

int extractQ(){
	return Q[startQ++];
}
