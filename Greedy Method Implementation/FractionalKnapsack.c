#include <stdio.h>
#include <stdlib.h>

float *profit,*weight,*p_wfrac,*solution,total_weight;
int *product,n;

void print();
void input();
void make_zeros();
void bubblesort(float *,float *,float *,int);
void swap(float *,float *,float *,int,int);
float knapsack_weight();
float knapsack_profit();
float knapsack_pwratio();
void fractional_knapsack();
float calculate_profit();
void compare_print(float,float,float);


int main(){
    float tprofit_weight,tprofit_profit,tprofit_ratio;
    printf("Enter Total knapsack weight : ");
    scanf("%f",&total_weight);
    printf("Enter number of products : ");
    scanf("%d",&n);
    profit = (float *) calloc(sizeof(float),n);
    weight = (float *) calloc(sizeof(float),n);
    product = (int *) calloc(sizeof(int),n);
    p_wfrac = (float *) calloc(sizeof(float),n);
    solution = (float *) calloc(sizeof(float),n);
    input();
    print();
    
    tprofit_weight = knapsack_weight();
    tprofit_profit = knapsack_profit();
    tprofit_ratio = knapsack_pwratio();
    compare_print(tprofit_weight,tprofit_profit,tprofit_ratio);
    free(profit);
    free(weight);
    free(product);
    free(solution);
    free(p_wfrac);
    return 0;
}

void input(){
    int i;
    printf("Enter The weight and profit for corresponding products : \n");
    for(i=0;i<n;i++){
        printf("Enter the profit & weight data for product %d :",i+1);
        scanf("%f %f",&profit[i],&weight[i]);
        product[i] = i+1;
        p_wfrac[i] = profit[i]/weight[i]; // calculating profit weight ratio
    }
}

void print(){
    int i;
    for(i=0;i<n;i++)
        printf("The data for product %d :=\tweight : %f\tprofit = %f\tpwfrac = %f\tsolution = %f\n",product[i],weight[i],profit[i],p_wfrac[i],solution[i]);
}

void make_zeros(){
    int i=0;
    for(i=0;i<n;i++){
        solution[i] = 0;
    }
}

float knapsack_weight(){
    make_zeros();
    bubblesort(weight,p_wfrac,profit,0);
    //printf("After sorting w.r.t weight :\n");
    //print();
    //printf("After applying fractional knapsack :\n");
    fractional_knapsack();
    //print();
    printf("profit by weight : %f\n",calculate_profit());
    return calculate_profit();
}
float knapsack_profit(){
    make_zeros();
    bubblesort(profit,p_wfrac,weight,1);
    //printf("After sorting w.r.t profit :\n");
    //print();
    //printf("After applying fractional knapsack :\n");
    fractional_knapsack();
    //print();
    printf("profit by profit : %f\n",calculate_profit());
    return calculate_profit();
}
float knapsack_pwratio(){
    make_zeros();
    bubblesort(p_wfrac,weight,profit,1);
    //printf("After sorting w.r.t pwfrac :\n");
    print();
    //printf("After applying fractional knapsack :\n");
    fractional_knapsack();
    //print();
    printf("profit by profit weight ratio : %f\n",calculate_profit());
    return calculate_profit();
}

void compare_print(float x,float y,float z){
    if(x>y){
        if(x>z){
            printf("Maximum profit can be achieved by SOLTUION BASED ON WEIGHT\n");
            printf("Total profit : %f\n",x);
        }
        else{
            printf("Maximum profit can be achieved by SOLTUION BASED ON PROFIT-WEIGHT RATIO\n");
            printf("Total profit : %f\n",z);
        }
    }
    else{
        if(y>z){
            printf("Maximum profit can be achieved by SOLTUION BASED ON PROFIT\n");
            printf("Total profit : %f\n",y);
        }
        else{
            printf("Maximum profit can be achieved by SOLTUION BASED ON PROFIT-WEIGHT RATIO\n");
            printf("Total profit : %f\n",z);
        }
    }
}

void fractional_knapsack(){
    int i;
    float bag_weight = total_weight;
    for(i=0;i<n;i++){
        if(weight[i]>bag_weight)
            break;
        solution[i] = 1.0;
        bag_weight = bag_weight - weight[i]; 
    }
    if(i<=n)
        solution[i] = bag_weight/weight[i];
}

float calculate_profit(){
    int i=0;
    float total_profit = 0.0;
    for(i=0;i<n;i++){
        total_profit = total_profit + solution[i]*profit[i];
    }
    return total_profit;
}

void bubblesort(float *arr,float *aux1,float *aux2,int mode){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(mode == 1){
                if(arr[j]<arr[j+1])
                    swap(arr,aux1,aux2,j,j+1);
            }
            else{
                if(arr[j]>arr[j+1])
                    swap(arr,aux1,aux2,j,j+1);
            }
        }
    }
}

void swap(float *arr,float *aux1,float *aux2,int i,int j){
    float ftemp;
    int itemp;

    ftemp = arr[i];
    arr[i] = arr[j];
    arr[j] = ftemp;

    
    ftemp = aux1[i];
    aux1[i] = aux1[j];
    aux1[j] = ftemp;

    
    ftemp = aux2[i];
    aux2[i] = aux2[j];
    aux2[j] = ftemp;

    
    itemp = product[i];
    product[i] = product[j];
    product[j] = itemp;
}