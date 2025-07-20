#include <stdio.h>
#include <stdlib.h>

int n=0,count=0,graph[10][10];

void clearfiles(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            graph[i][j]=0;
        }
    }
    count=0;
}

void warshall(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            if(graph[i][k]){
            for(int j=0;j<n;j++){
                count++;
                graph[i][j]=graph[i][j] || (graph[i][k] && graph[k][j]);
            }}
        }
    }
}

void warshall_analysis(){
    FILE*f1,*f2;
    f1=fopen("Warshall_b.txt","a");
    f2=fopen("Warshall_w.txt","a");
    n=1;
    while(n<=10){
        //best case
        clearfiles();
        for(int i=0;i<n;i++){
            graph[i][i+1]=1;
        }
        warshall();
        fprintf(f1,"%d\t%d\n",n,count);
        //worst case
        clearfiles();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j)
                graph[i][j]=1;
            }
        }
        warshall();
        fprintf(f2,"%d\t%d\n",n,count);
        n++;
    }
    fclose(f1);
    fclose(f2);
}

void clear(){
    FILE*f1,*f2;
    f1=fopen("Warshall_b.txt","w");
    fclose(f1);
    f2=fopen("Warshall_w.txt","w");
    fclose(f2);
}

void input(){
    clearfiles();
    printf("\nEnter the number of nodes: ");
    scanf("%d",&n);
    printf("\nEnter the adjacency matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }
    printf("Adjacency matrix of Input matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}

void output(){
    printf("Transitive Closure Matrix:\n");
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
        printf("\n1. Tester\n2. Plotter\n0. To Exit\nEnter your choice from above: ");
        scanf("%d",&ch);

        switch(ch){
            case 1:
            input();
            warshall();
            output();
            break;

            case 2:
            warshall_analysis();
            break;

            case 0:
            printf("Exiting...\n");
            exit(0);
        }
    }
}