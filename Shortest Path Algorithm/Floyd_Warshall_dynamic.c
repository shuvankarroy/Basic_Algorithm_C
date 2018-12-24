#include <stdio.h>
#include <stdlib.h>
# define INF 99999

void input();
void print_graph();
void FloydWarshall();
void printD();

int **graph ,***D, ***P, nVertices, startVertex, endVertex, nEdges;

//int graph[100][100] ,D[100][100][100], P[100][100][100], nVertices, startVertex, endVertex, nEdges;

int main(){
    input();
	print_graph();
	FloydWarshall();
	printD();
	return 0;
}

void input(){
	int i,j,k,from,to,weight,choice;
	printf("Enter number of vertices : ");
	scanf("%d",&nVertices);
	printf("Enter number of edges : ");
	scanf("%d",&nEdges);
	
	//dynamic memory allocation for graph and visited and t;

	graph = (int **)calloc(sizeof(int),nVertices+1);
	for(i=0; i<=nVertices; i++){
		graph[i] = (int *)calloc(sizeof(int),nVertices+1);
	}
	
	D = (int ***)calloc(sizeof(int **),nVertices+1);
	for(i=0; i<=nVertices; i++){
		D[i] = (int **)calloc(sizeof(int*),nVertices+1);
		for(j=0; j<=nVertices; j++){
			D[i][j] = (int *)calloc(sizeof(int),nVertices+1);
		}
	}

	P = (int ***)calloc(sizeof(int **),nVertices+1);
	for(i=0; i<=nVertices; i++){
		P[i] = (int **)calloc(sizeof(int *),nVertices+1);
		for(j=0; j<=nVertices+1; j++){
			P[i][j] = (int *)calloc(sizeof(int),nVertices+1);
		}
	}	
		
    printf("How do you want to input your graph? \n choice 1 => by matrix \n choice 2 => by edge and vertices\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);
    switch(choice){
        case 1: printf("Enter the cost or weight matrix representation of the graph :\n");
                printf("***Enter 0 in place of no connection***\n");
                for(i=1; i<=nVertices; i++){
                    for(j=1; j<=nVertices; j++){
                        scanf("%d",&graph[i][j]);
                        if(graph[i][j] == 0 && i!=j){
                            graph[i][j] = INF;
                        }                  
                        D[0][i][j] = graph[i][j];
                        P[0][i][j] = 0;
                    }
                }
                break;


        case 2: printf("Enter the source and destination vertex and weight of a edge : \n" );
	            for(i=1; i<=nEdges; i++){
		            printf("Enter source and destination for edge %d : ",i);
		            scanf("%d %d",&from ,&to);
		            printf("Enter weight of the edge between %d and %d : ",from,to);
		            scanf("%d",&weight);
		            graph[from][to] = weight;
	            }
                break;
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

void FloydWarshall(){
	int n,k,i,j,u,v;
	n = nVertices;
	for(k=1; k<=nVertices; k++){
		
		/*initialize D[k]*/
		for(u=1; u<= nVertices; u++){
			for(v=1; v<=nVertices; v++){
				D[k][u][v] = D[k-1][u][v];
				P[k][u][v] = P[k-1][u][v];
			}
		}
		
		for(i=1; i<=nVertices; i++){
			for(j=1; j<=nVertices; j++){
				 if(D[k][i][j] > D[k-1][i][k] + D[k-1][k][j]){
				 	D[k][i][j] = D[k-1][i][k] + D[k-1][k][j];
				 	P[k][i][j] = k;
				 }
			}
		}
	}
}

void printD(){
	int i,j;
	printf("\nD[k] matrix is : \n");
	for(i=1;i<=nVertices; i++){
		for(j=1; j<=nVertices; j++){
			printf("%d\t",D[nVertices][i][j]);
		}
		printf("\n");
	}
	
	printf("\nP[k] matrix is : \n");
	for(i=1;i<=nVertices; i++){
		for(j=1; j<=nVertices; j++){
			if(P[nVertices][i][j])
				printf("%d\t",P[nVertices][i][j]);
			else
				printf("*\t");
		}
		printf("\n");
	}
}

