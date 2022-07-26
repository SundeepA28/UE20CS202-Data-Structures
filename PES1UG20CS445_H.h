#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdlib.h>
#define MAX 100
typedef struct node
{
    int vertex_id;
    int x_cor;
    int y_cor;
    struct node *link;
}NODE;
typedef struct storedata
{

    int x_cor[100];
    int y_cor[100];
    int vertex_id[100];
}store_data;

typedef struct queue
{
    int start[MAX];
    int end[MAX];    
    int front;
    int rear;
}QUEUE;
typedef struct Graph 
{
  int num_ver;
  NODE *h[100];
  int visited[100];
}GPH;
int r,c,sr,sc;
int dfs_path[MAX];
int len;
int read_data(int a[10][10]);
int create_adjmat(int a[10][10],store_data* info,int adj_mat[MAX][MAX],int n);
void init(GPH *g,int n);
void adj_list(int a[MAX][MAX],GPH* g,store_data* info);
int bfs_traversal(GPH *g, int start_ver,int destination,int bfs_path[MAX]);
int dfs_traversal(GPH *g, int start_ver,int dest_ver);
void bfs_display(store_data* info,int bfs_path[MAX],int n);
void dfs_display(store_data* info);
