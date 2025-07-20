#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n=0,count=0,knap[100][100],profit[100],weight[100],items[100],capacity=0;

clearfiles(){
    for(int i=0;i<100;i++){
        profit[i]=0;
        weight[i]=0;
        items[i]=0;
    }
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            knap[i][j]=0;
        }
    }
    capacity=0;
}

int max(int a,int b){
    return (a>b)?a:b;
}

void knapsack(){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=capacity;j++){
            if(i==0 || j==0)
            knap[i][j]=0;
            else{
                count++;
                if(j>=weight[i]){
                    knap[i][j]=max(knap[i-1][j],(profit[i]+knap[i-1][j-weight[i]]));
                }
                else{
                    knap[i][j]=knap[i-1][j];
                }
            }
        }
    }
}

void knapsack_analysis(){
    srand(time(NULL));
    FILE*f;
    f=fopen("Knapsack.txt","a");
    n=1;
    while(n<=10){
        clearfiles();
        for(int i=1;i<=n;i++){
            profit[i]=rand()%n+1;
            weight[i]=rand()%n+1;
        }
        capacity=n+1;
        count=0;
        knapsack();
        fprintf(f,"%d\t%d\n",n,count);
        n++;
    }
}

void clear(){
    FILE*f;
    f=fopen("Knapsack.txt","w");
    fclose(f);
}

void input(){
    printf("Enter the number of items: ");
    scanf("%d",&n);
    printf("Enter the capacity: ");
    scanf("%d",&capacity);
    printf("\nEnter the weight for each item:\n");
    for(int i=1;i<=n;i++){
        scanf("%d",&weight[i]);
    }
    printf("\nEnter the profit for each item:\n");
    for(int i=1;i<=n;i++){
        scanf("%d",&profit[i]);
    }
}

void items_selected(){
    int col=capacity;
    int row=n;
    int j=0;
    while(row>0 && col>0){
        if(knap[row][col]!=knap[row-1][col]){
            items[j++]=row;
            col-=weight[row];
        }
        row--;
    }
    printf("Items selected:\n");
    for(int i=0;i<j;i++){
        printf("%d\t",items[i]);
    }
    printf("\n");
}

void output(){
    printf("\n");
    for(int i=0;i<=capacity;i++){
        printf("\t%d",i);
    }
    printf("\n");
    for(int i=0;i<=n;i++){
        printf("%d",i);
        for(int j=0;j<=capacity;j++){
            printf("\t%d",knap[i][j]);
        }
        printf("\n");
    }
    items_selected();
}

void main(){
    clear();
    int ch;
    for(;;){
        printf("\nENTER:\n1. Tester\n2. Plotter\n0. To EXIT\nEnter your choice from above: ");
        scanf("%d",&ch);

        switch(ch){
            case 1:
            clearfiles();
            input();
            knapsack();
            output();
            break;

            case 2:
            knapsack_analysis();
            break;

            case 0:
            printf("Exiting...\n");
            exit(0);

            default:
            printf("Invalid Choice! Please Enter Again!...\n");
            break;
        }
    }
}