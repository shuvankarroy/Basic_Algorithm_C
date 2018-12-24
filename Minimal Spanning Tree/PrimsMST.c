#include <stdio.h>
#include <stdlib.h>
#define INF 9999 

int e, v, **g,*visited,mincost,**t;

/*function prototype declaration*/
void input();
void make_zero_visited();
void print_g();
void prims();
void printRes();

int main() {
	input();
	print_g();
	prims();
	printRes();
	/*free up allocated memory*/
	free(visited);
	free(g);
	free(t);
	return 0;
}

void input(){
	int i,j,k,from,to,weight;
	printf("Enter number of vertices : ");
	scanf("%d",&v);
	printf("Enter number of edges : ");
	scanf("%d",&e);

	//dynamic memory allocation for graph and visited and t;
	
	visited = (int *)calloc(sizeof(int),v+1);
	
	g = (int **)calloc(sizeof(int),v+1);
	for(i=0; i<=v; i++){
		g[i] = (int *)calloc(sizeof(int),v+1);
	}
	
	t = (int **)calloc(sizeof(int),v+1);
	for(i=0;i<=v;i++){
		t[i] = (int *)calloc(sizeof(int),5);
	}
	
	printf("Enter the cost or weight matrix representation of the graph :\n");
    printf("***Enter 0 in place of no connection***\n");
    for(i=1; i<=v; i++){
        for(j=1; j<=v; j++){
        	scanf("%d",&g[i][j]);
            if(g[i][j] == 0){
                g[i][j] = INF;
       	    }                  
        }
    }
}

void print_g(){
	int i,j;
	printf("The cost matrix is :\n");
	for(i=1;i<=v;i++){
		for(j=1;j<=v;j++){
			printf("%d\t",g[i][j]);
		}
		printf("\n");
	}
}


void make_zero_visited(){
	int i;
	for(i=0;i<=v;i++){
		visited[i] = 0;
	}
}

void prims(){
	int i,j,k,min,v1,v2;
	make_zero_visited();
	visited[1]=1;
	mincost = 0;
	for(k=1; k<v;k++){
		min = INF;
		for(i=1;i<=v;i++){
			for(j=1;j<=v;j++){
				if(g[i][j]!= INF && visited[j] == 0 && visited[i] == 1){
					if(min>g[i][j]){
						min = g[i][j];
						v1 = i;
						v2 = j;	
					}
				}
			}
		}
		
		mincost = mincost + min;
		visited[v1] = visited[v2] = 1;
		t[k][1] = v1;
		t[k][2] = v2;
		t[k][3] = min;
		t[k][4] = mincost;
	}
}

void printRes(){
	int i;
	printf("\nMinimum cost : %d",mincost);
	
	printf("\nThe t matrix (distance in between vertices) is : \n");
	printf("v1 \t v2 \t min \t mincost\n");
	for(i=1;i<v;i++){
		printf("%d \t %d \t %d \t %d",t[i][1],t[i][2],t[i][3],t[i][4]);
		printf("\n");
	}
}
