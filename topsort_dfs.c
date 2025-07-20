#include <stdio.h>
#include <stdlib.h>

int n=0,graph[10][10],count=0,d=0,stk[100],top=-1,visit[100],isCycle=0,arr[100],in=-1,remstk[100],dfsCount=0;

void clear(){
    FILE*f;
    f=fopen("Top_sort_dfs.txt","w");
    fclose(f);
}

void clearfiles(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            graph[i][j]=0;
        }
    }
    for(int i=0;i<100;i++){
        stk[i]=-1;
        visit[i]=0;
        arr[i]=-1;
        remstk[i]=0;
    }
    count=0;
    top=-1;
    isCycle=0;
    in=-1;
    dfsCount=0;
}

void dfs(int start, int parent){
    visit[start]=1;
    stk[++top]=start;
    remstk[start]=1;
        for(int i=0;i<n;i++){
            count++;
            if(!visit[i] && graph[start][i] && !remstk[i]){
                dfs(i,start);
            }
            else if(graph[start][i] && remstk[i]){
                isCycle=1;
                printf("Topological sorting for cyclic graph is not applicable\n");
                exit(0);
            }
        }
    arr[++in]=stk[top--];
    remstk[start]=0;
}

void input(){
    clearfiles();
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    printf("Enter the adjacency matrix of the graph:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }
    dfs(0,-1);
    for(int i=0;i<n;i++){
        if(!visit[i]){
            dfs(i,-1);
        }
    }
}

void output(){
    printf("Topological sorted order: ");
    while(in!=-1){
        printf("%c\t",arr[in]+65);
        in--;
    }
    
}

void top_sort_dfs_analysis(){
    FILE*f;
    f=fopen("Top_sort_dfs.txt","a");
    n=1;
    while(n<=10){
        //directed
        clearfiles();
        for(int i=0;i<n-2;i++){
            graph[i][i+1]=1;
        }
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
        printf("\n1. Tester\n2. Plotter\n0. To Exit\nEnter your choice from above: ");
        scanf("%d",&ch);

        switch(ch){

            case 1:
            input();
            output();
            break;

            case 2:
            top_sort_dfs_analysis();
            break;

            case 0:
            printf("Exiting...\n");
            exit(0);

            default:
            printf("Invalid Choice!Please Enter Again!...\n");
            break;
        }
    }
}