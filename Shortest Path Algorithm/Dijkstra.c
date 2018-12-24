#include <stdio.h>
#include <stdlib.h>
# define INF 99999

/*function prototype declaration*/
void input();
void Initialize_Single_Src();
void print_graph();
void Relax(int, int);
void Dijkstra();
void printRes();
void sortQ_d();
int extractMin();
void setQueue();

int **graph, *d, *pi, *path, nVertices, startVertex, endVertex, nEdges;
int *Q, Qstart, Qend;

int main(){
    input();
	print_graph();
	Dijkstra();
	printRes();
	/*free allocated memory*/
	free(d);
	free(pi);
	free(path);
	free(Q);
	free(graph);
	return 0;
}

void input(){
	int i,j,k,from,to,weight,choice;
	printf("Enter number of vertices : ");
	scanf("%d",&nVertices);
	printf("Enter number of edges : ");
	scanf("%d",&nEdges);
	printf("Enter starting vertex : ");
    scanf("%d",&startVertex);
	
	//dynamic memory allocation for graph and visited and t;
	
	d = (int *)calloc(sizeof(int),nVertices+1);
    pi = (int *)calloc(sizeof(int),nVertices+1);
	path = (int *)calloc(sizeof(int),nVertices+1);
	Q = (int *)calloc(sizeof(int),nVertices+1);

	graph = (int **)calloc(sizeof(int),nVertices+1);
	for(i=0; i<=nVertices; i++){
		graph[i] = (int *)calloc(sizeof(int),nVertices+1);
	}
	printf("Enter the cost or weight matrix representation of the graph :\n");
    printf("***Enter 0 in place of no connection***\n");
    for(i=1; i<=nVertices; i++){
        for(j=1; j<=nVertices; j++){
        	scanf("%d",&graph[i][j]);
            if(graph[i][j] == 0){
                graph[i][j] = INF;
       	    }                  
        }
    }
}

void print_graph(){
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

void Relax(int u, int v){
	if(d[v] > d[u] + graph[u][v]){
		d[v] = d[u] + graph[u][v];
		pi[v] = u;
	}
}

void Dijkstra(){
	int u,v,counter,i,j,k;
	counter = 0;
	Initialize_Single_Src();
	setQueue();
	while(Qstart<=Qend){
		u = extractMin();
		path[++counter] = u;
		for(v=1; v<= nVertices; v++){
			if(graph[u][v] != INF && v != startVertex){
				Relax(u,v);
			}
		}
	}
}

void setQueue(){
	int i;
	for (i=1; i<= nVertices; i++)
		Q[i] = i;
	Qstart = 1;
	Qend = nVertices;
}

int extractMin(){
	int i,j,temp;
    for(i=Qstart; i<=nVertices; i++){
        for(j=Qstart; j<=nVertices -1; j++){
            if ( d[Q[j]] > d[Q[j+1]]){
				temp = Q[j];
				Q[j] = Q[j+1];
				Q[j+1] = temp;	 
			}  
        }
    }
	return Q[Qstart++];
}

void printRes(){
	int i;
	printf("\nvertex\tadjacency\tdistance\n");
	for(i=1; i<=nVertices; i++){
		printf("%d\t\t%d\t%d\t",i,pi[i],d[i]);
		printf("\n");
	}
}
