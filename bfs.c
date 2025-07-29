#include <stdio.h>
#include <stdlib.h>

int n=0,queue[100],graph[10][10],d=0,visit[10],par[10],front=0,rear=-1,isCycle=0,indeg[100],count=0;

void clearfiles(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            graph[i][j]=0;
        }
        visit[i]=0;
        par[i]=-1;
    }
    for(int i=0;i<100;i++){
        queue[i]=-1;
        indeg[i]=0;
    }
    d=0;
    front=0;
    rear=-1;
    isCycle=0;
}

void bfs_un(int start){
    queue[++rear]=start;
    par[start]=-1;
    while(front<=rear){
        int u=queue[front++];
        visit[u]=1;

        for(int i=0;i<n;i++){
            count++;
            if(!visit[i] && graph[u][i]){
                queue[++rear]=i;
                par[i]=u;
            }
            else if(visit[i] && graph[u][i] && par[u]!=i){
                isCycle=1;
            }
        }
    }
}

void cycle_d(){
    int p=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(graph[i][j]){
                indeg[j]++;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(!indeg[i]){
            queue[++rear]=i;
            indeg[i]=-1;
        }
    }
    while(front<=rear){
        int u=queue[front++];
        p++;
        visit[u]=1;
        int flag=0;
        for(int i=0;i<n;i++){
            if(graph[u][i]){
                indeg[i]--;
            }
        }
        for(int i=0;i<n;i++){
            if(!indeg[i]){
                flag=1;
                queue[++rear]=i;
                indeg[i]=-1;
            }
        }
    }
    if(p!=n){
        isCycle=1;
    }
}

void clear1(){
    for(int i=0;i<100;i++){
        visit[i]=0;
        queue[i]=-1;
    }
    front=0;
    rear=-1;
    count=0;
}

void bfs_d(int start){
    clear1();
    queue[++rear]=start;
    while(front<=rear){
        int u=queue[front++];
        visit[u]=1;
        for(int i=0;i<n;i++){
            count++;
            if(!visit[i] && graph[u][i]){
                queue[++rear]=i;
            }
        }
    }
}

void input(){
    clearfiles();
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    printf("Enter directed or undirected?(1/0): ");
    scanf("%d",&d);
    printf("Adjacency matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }

    if(d==0){
        bfs_un(0);
    }
    else{
        cycle_d();
        bfs_d(0);
    }
}

void out_d(){
    int f_un=0;
        int cc=1;
        for(int i=0;i<n;i++){
            f_un=0;
            if(!visit[i]){
                f_un=1;
                printf("Graph is disconnected\n");
                break;
            }
        }
        if(f_un==0){
            printf("Graph is connected\n");
        }
        printf("Connected components:\n");
        for(int i=0;i<n;i++){
            if(visit[i]){
                printf("%c\t",i+65);
            }
            else{
                cc++;
                printf("\n");
                bfs_d(i);
                i--;
            }
        }
        printf("\nNumber of connected components: %d\n",cc);
}

void output(){
    if(isCycle){
        printf("The graph is cyclic\n");
    }
    else{
        printf("The graph is acyclic\n");
    }

    if(d==0){
        int f_un=0;
        int cc=1;
        for(int i=0;i<n;i++){
            f_un=0;
            if(!visit[i]){
                f_un=1;
                printf("Graph is disconnected\n");
                break;
            }
        }
        if(f_un==0){
            printf("Graph is connected\n");
        }
        printf("Connected components:\n");
        for(int i=0;i<n;i++){
            if(visit[i]){
                printf("%c\t",i+65);
            }
            else{
                cc++;
                printf("\n");
                bfs_un(i);
                i--;
            }
        }
        printf("\nNumber of connected components: %d\n",cc);
    }
    else{
        out_d();
    }
}

void clear(){
    FILE*f1,*f2;
    f1=fopen("bfs_un.txt","w");
    fclose(f1);
    f2=fopen("bfs_d.txt","w");
    fclose(f2);
    
}

void bfs_analysis(){
    clearfiles();
    FILE*f1,*f2;
    f1=fopen("bfs_un.txt","a");
    f2=fopen("bfs_d.txt","a");
    printf("Directed or undirected(1/0): ");
    scanf("%d",&d);
    if(d==0){
        n=1;
        while(n<=10){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    graph[i][j]=1;
                    graph[j][i]=1;
                }
            }
        }
    count=0;
        bfs_un(0);
    fprintf(f1,"%d\t%d\n",n,count);
    n++;}
}
else{
    n=1;
    while(n<=10){
        for(int i=0;i<n;i++){
            graph[i][i+1]=1;
        }
        count=0;
        bfs_d(0);
        fprintf(f2,"%d\t%d\n",n,count);
        n++;
    }
}
fclose(f1);
fclose(f2);
}

void main(){
    clear();
    int ch;
    for(;;){
        printf("\nEnter:\n1. Tester\n2. Plotter\nEnter your choice from above: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
            input();
            output();
            break;

            case 2:
            bfs_analysis();
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