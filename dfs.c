#include <stdio.h>
#include <stdlib.h>

int graph[100][100],isCycle=0,visit[100],n=0,d=0,stk[100],cc=1,count;

void clearfiles(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            graph[i][j]=0;
        }
    }
    isCycle=0;
    for(int i=0;i<100;i++){
        visit[i]=0;
        stk[i]=0;
    }
    d=0;
    cc=1;
    count=0;
}

void input(){
    clearfiles();
    printf("\nEnter the number of nodes: ");
    scanf("%d",&n);
    printf("Enter whether the graph is directed or not (0/1): ");
    scanf("%d",&d);
    printf("\nEnter the adjacency matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }
}

void dfs(int start,int parent){
    visit[start]=1;
    stk[start]=1;

    if(d==0){
        for(int i=0;i<n;i++){
            count++;
            if(!visit[i] && graph[start][i]){
                dfs(i,start);
            }
            else if(visit[i] && graph[start][i] && parent!=i){
                isCycle=1;
            }
        }
    }
    else{
        for(int i=0;i<n;i++){
            count++;
            if(!visit[i] && graph[start][i] && !stk[i]){
                dfs(i,start);
            }
            else if(graph[start][i] && stk[i]){
                isCycle=1;
            }
        }
    }
    stk[start]=0;
}

void output(){
    //Cyclicity
    if(isCycle){
        printf("Graph is cyclic\n");
    }
    else{
        printf("Graph is acyclic\n");
    }

    //Connectivity
    int c=0;
    for(int i=0;i<n;i++){
        if(!visit[i]){
            printf("Graph is disconnected\n");
            c=1;
            break;
            }
        }
    if(c){
        printf("Connected Components:\n");
        for(int i=0;i<n;i++){
            if(visit[i]){
                printf("%c\t",i+65);
        }
        else if(!visit[i]) 
        {cc++;
        dfs(i,-1);
        printf("\n");
        i--;
        }
    }
        printf("\nNumber of connected components: %d\n",cc);
    }
    else{
        printf("Graph is connected\n");
        printf("Connected Components:\n");
        for(int i=0;i<n;i++){
            printf("%c\t",i+65);
        }
        printf("\nNumber of connected components: %d\n",cc);
    }
}

void clear(){
    FILE*f;
    f=fopen("dfs.txt","w");
    fclose(f);
}

void dfs_analysis(){
    n=1;
    FILE*f=fopen("dfs.txt","a");
    while(n<=10){
        clearfiles();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    graph[i][j]=1;
                }
            }
        }
        count=0;
        dfs(0,-1);
        fprintf(f,"%d\t%d\n",n,count);
        n++;
    }
    fclose(f);
}

void main(){
    clear();
    int ch;
    for(;;){
        printf("\nEnter:\n1. Tester\n2. Plotter\n0. To Exit\nEnter your choice from above: ");
        scanf("%d",&ch);

        switch(ch){
            case 1:
            input();
            dfs(0,-1);
            output();
            break;

            case 2:
            dfs_analysis();
            break;

            case 0:
            printf("Exiting...\n");
            exit(0);

            default:
            printf("Invalid Choice! Please Enter Again!...\n");
        }
    }
}