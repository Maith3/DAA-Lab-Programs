#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n=0,count=0,cost[10][10],src=0,visit[100],dist[100],path[100];

void clearfiles(){
    for(int i=0;i<100;i++){
        visit[i]=0;
        dist[i]=9999;
        path[i]=-1;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<n;j++){
            cost[i][j]=0;
        }
    }
    src=0;
}

void dijkstras(){
    dist[src]=0;
    path[src]=-1;
    for(int i=0;i<n-1;i++){
        int min=9999;
        int u=-1;
        for(int j=0;j<n;j++){
            if(!visit[j] && dist[src]<min){
                min=dist[src];
                u=j;
            }
        }
        if(u==-1) return;
        visit[u]=1;
        for(int v=0;v<n;v++){
            count++;
            if(!visit[v] && cost[u][v] && (dist[v]>dist[u]+cost[u][v])){
                dist[v]=dist[u]+cost[u][v];
                path[v]=u;
            }
        }
    }
}

void dijkstras_analysis(){
    srand(time(NULL));
    FILE*f=fopen("Dijkstras.txt","a");
    n=1;
    while(n<=10){
        clearfiles();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j)
                cost[i][j]=0;
                else{
                    cost[i][j]=(rand()%n)+1;
                }
            }
        }
        count=0;
        dijkstras();
        fprintf(f,"%d\t%d\n",n,count);
        n++;
    }
    fclose(f);
}

void clear(){
    FILE*f=fopen("Dijkstras.txt","w");
    fclose(f);
}

void input(){
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    printf("\nEnter the cost matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
        }
    }
    printf("Enter the source: ");
    scanf("%d",&src);
}

void output(){
    for(int i=0;i<n;i++){
        printf("Distance of %d from source %d is: %d\n",i,src,dist[i]);
    }
    for(int i=0;i<n;i++){
        printf("Parent of %d is: %d\n",i,path[i]);
    }
}

void main(){
    int ch;
    clear();
    for(;;){
        printf("\nENTER:\n1. Tester\n2. Plotter\n0. To Exit\nEnter your choice from above: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
            clearfiles();
            input();
            dijkstras();
            output();
            break;

            case 2:
            dijkstras_analysis();
            break;

            case 0:
            printf("Exiting...\n");
            exit(0);

            default:
            printf("Invalid Input! Please Enter Again!...\n");
            break;
        }
    }
}