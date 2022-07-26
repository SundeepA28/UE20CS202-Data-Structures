#include<stdio.h>
#include "PES1UG20CS445_H.h"
int main()
{
    store_data info;
    GPH g;
    int adj_mat[MAX][MAX]={0};
    int a[10][10];
    int bfs_path[MAX]={0};
    int dfs_path[MAX]={0};
    int n=read_data(a)+1;
    int c = create_adjmat(a,&info,adj_mat,n);
    init(&g,c);
    adj_list(adj_mat,&g,&info);
    n=bfs_traversal(&g,0,c-1,bfs_path);
    if(n)
    {
        bfs_display(&info,bfs_path,n);  
    }
    else
    {
        FILE* ptr = fopen("outbfs.txt","w");
		fprintf(ptr,"-1");
	    fclose(ptr);
    }
    c=dfs_traversal(&g,0,c-1);
    if(n)
    {
        dfs_display(&info);  
    }
    else
    {
        FILE* ptr = fopen("outdfs.txt","w");
		fprintf(ptr,"-1");
	    fclose(ptr);
    }
}
