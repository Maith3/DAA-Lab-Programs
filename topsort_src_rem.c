#include <stdio.h>
#include <stdlib.h>

int n=0,graph[10][10],visit[100],indeg[100],count=0,remcount=0,stk[100],top=-1,topsort[100],in=0,flag=0;

void clearfiles(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            graph[i][j]=0;
        }
    }
    for(int i=0;i<100;i++){
        visit[i]=0;
        indeg[i]=0;
        stk[i]=-1;
        topsort[i]=-1;
    }
    count=0;
    top=-1;
    in=0;
    remcount=0;
    flag=0;
}

void topsort_src_rem(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(graph[i][j]){
                indeg[j]+=1;
            }
        }
    }
    while(remcount!=n){
        for(int i=0;i<n;i++){
            count++;
            if(!indeg[i]){
                flag=1;
                stk[++top]=i;
                indeg[i]=-1;
            }
        }
        if(flag==0){
            printf("Topological sorting for cyclic graph is not applicable\n");
            exit(0);
        }
        int temp=stk[top--];
        topsort[in++]=temp;
        remcount++;
        for(int i=0;i<n;i++){
            if(graph[temp][i]){
                indeg[i]--;
            }
        }
    }
}

void topsort_src_rem_analysis(){
    FILE*f=fopen("Topsort_src_rem.txt","a");
    n=1;
    while(n<=10){
        clearfiles();
        for(int i=0;i<n-2;i++){
            graph[i][i+1]=1;
        }
        topsort_src_rem();
        fprintf(f,"%d\t%d\n",n,count);
        n++;
    }
    fclose(f);
}

void input(){
    clearfiles();
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    printf("Enter the adjacency matrix: \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }

}

void output(){
    printf("Topological sorting order:\n");
    for(int i=0;i<in;i++){
        printf("%c\t",topsort[i]+65);
    }
}

clear(){
    FILE*f;
    f=fopen("Topsort_src_rem.txt","w");
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
            topsort_src_rem();
            output();
            break;

            case 2:
            topsort_src_rem_analysis();
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