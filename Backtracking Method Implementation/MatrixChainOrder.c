# include <stdio.h>
# include <stdlib.h>
# define INF 99999

int **m,**s,*p,length;

void print(int **,int,int);
void matrixChainMultiply();
void parenthesized(int,int);
int main()
{
	int i;

	printf("Enter the length of p vector : ");
	scanf("%d",&length);

	// dynamically allocating memory for m,s,p
	p = (int *) calloc(sizeof(int),length);
	
	m = (int **)malloc(sizeof(int *)*(length));
	for(i=0;i<=length;i++)
		m[i] = (int *)malloc(sizeof(int *)*(length));
	
	s = (int **)malloc(sizeof(int *)*length);
	for(i=0;i<length;i++)
		s[i] = (int *)malloc(sizeof(int *)*(length-1));

	//taking input from user 
	printf("Enter the p vector containg dimensions of matrix :\n");
	for(i=0;i<length;i++)
		scanf("%d",&p[i]);

	matrixChainMultiply();
	print(m,length,0);
	print(s,length,1);
	printf("The parenthesized content is : \n");
	parenthesized(1,length-1);
	return 0;
}

void matrixChainMultiply(){
	int i,n,l,j,k,q;
	n = length-1;

	printf("in matrix chain \n");
	for(i=1;i<=n;i++)
		m[i][i] = 0;
	
	for(l=2;l<=n;l++){
		printf("in matrix chain loop 1\n");
		for(i=1;i<=(n-l+1);i++){
			printf("in matrix chain loop 2\n");
			j = i+l-1;
			m[i][j] = INF;
			for(k=i;k<j;k++){
				printf("in matrix chain loop 3\n");
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				printf("value of m[%d][%d] q : %d\n",i,j,q);
				if(q < m[i][j]){
					m[i][j] = q;
					s[i][j] = k;
					printf("value of m[%d][%d] : %d\n",i,j,m[i][j]);
				}
			}
		}
	}
}

void parenthesized(int i,int j){
	if(i==j)
		printf("A[%d]",i);
	else{
		printf("(");
		parenthesized(i,s[i][j]);
		parenthesized(s[i][j]+1,j);
		printf(")");
	}
}

void print(int **target,int len,int mode){
	int i,j;
	if(mode == 0){
		for(i=1;i<len;i++){
			for(j=1;j<len;j++){
				if(i>j)
					printf("\t");
				else
					printf("%d\t",target[i][j]);
			}
			printf("\n");
		}
	}
	else{
		for(i=1;i<len-1;i++){
			for(j=2;j<len;j++){
				if(i>=j)
					printf("\t");
				else
					printf("%d\t",target[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}
