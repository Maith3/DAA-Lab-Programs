#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n=0,count=0,graph[10][10];

void clearfiles(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph[i][j]=0;
        }
    }
    count=0;
}

int min(int a,int b){
    return a<b?a:b;
}

void floyds(){
    int temp;
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                count++;
                graph[i][j]=min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
}

void floyds_analysis(){
    srand(time(NULL));
    FILE*f=fopen("Floyds.txt","a");
    n=1;
    while(n<=10){
        clearfiles();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    graph[i][j]=rand()%n+1;
                }
            }
        }
        floyds();
        fprintf(f,"%d\t%d\n",n,count);
        n++;
    }
    fclose(f);
}

void clear(){
    FILE*f;
    f=fopen("Floyds.txt","w");
    fclose(f);
}

void input(){
    clearfiles();
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    printf("\nEnter the cost matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }
    printf("\nCost matrix of input graph:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}

void output(){
    printf("\nAll-Pair Shortest Path Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}

void main(){
    clear();
    int ch;
    for(;;){
        printf("\nENTER:\n1. Tester\n2. Plotter\n0. To Exit\nEnter your choice from above: ");
        scanf("%d",&ch);

        switch(ch){
            case 1:
            input();
            floyds();
            output();
            break;

            case 2:
            floyds_analysis();
            break;

            case 0:
            printf("Exiting...\n");
            exit(0);

            default:
            break;
        }
    }
}