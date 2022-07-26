#include<stdio.h>
#include<stdlib.h>
#include "PES1UG20CS445_H.h"
NODE *getnode(int vertex_id,int x_cor,int y_cor)
{
    NODE * temp;
    temp=(NODE *)malloc(sizeof(NODE));
    temp->vertex_id=vertex_id;
    temp->x_cor=x_cor;
    temp->y_cor=y_cor;
    temp->link=NULL;
    return(temp);
}
int read_data(int a[10][10])
{
	FILE *ptr;
	ptr = fopen("input.txt","r");
	if(ptr == NULL)
   	{
      printf("Error!");   
      exit(1);             
   	}
	fscanf(ptr,"%d%d%d%d",&sr,&sc,&r,&c);
	for (int i = 0; i < r+1; i++)
        for (int j = 0; j < c+1; j++)
        {
            char c;
            if (fscanf(ptr, " %c", &c) != 1)
                printf("reading data failed");
            else if (isdigit((unsigned char)c))
                a[i][j] = c - '0';
            else
                a[i][j] = 0;
        }   
    return c;
}
void initQueue(QUEUE* q) 
{
    q->rear = -1;
    q->front = -1;
}
void adj_list(int a[MAX][MAX],GPH* g,store_data* info)
{
    NODE *ptr,*temp;
    int i,j;
    for(i=0;i<g->num_ver;i++)
        for(j=0;j<g->num_ver;j++)
            if(a[i][j]==1)
            {
                temp=getnode(j,info->x_cor[j],info->y_cor[j]);
                if(g->h[i]==NULL)
                    g->h[i]=temp;
                else
                {
                    temp->link=g->h[i]->link;
                    g->h[i]->link=temp;
                }
            }
}


void init(GPH *g,int n)
{
    g->num_ver=n;
    int i=0;
    while(i<n)
    {
        g->visited[i]=0;
        g->h[i]=NULL;
        i++;
    }
}
int create_adjmat(int a[10][10],store_data* info,int adj_mat[MAX][MAX],int n)
{
    
    int i,j;
    int ini=0;
    int c=0;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]==0)
            {   
                info->x_cor[c]=i;
                info->y_cor[c]=j;
                info->vertex_id[c]=c+1;
                c=c+1;
            }
        }
    }    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(a[i][j]==0)
            {
                if (a[i][j+1]==0)
                {
                    int check=-1;
                    for (int k = 0; k<c; k++)
                    {
                        if (info->x_cor[k]==i && info->y_cor[k]==j+1)
                        {
                            check=k;
                            break;
                        }
                        
                    }
                    if (check!=-1)
                    {
                        adj_mat[ini][check]=1;
                        adj_mat[check][ini]=1;
                    }
                }
                if (a[i+1][j]==0)
                {
                    int check=-1;
                    for (int k = 0; k<c; k++)
                    {
                        if (info->x_cor[k]==i+1 && info->y_cor[k]==j)
                        {
                            check=k;
                            break;
                        }
                        
                    }
                    if (check!=-1)
                    {
                        adj_mat[ini][check]=1;
                        adj_mat[check][ini]=1;
                    }
                }
            ini =ini+1;
            }
    return c;
}

void bfs(GPH *g, int start_ver,QUEUE* q) 
{   
    int s=start_ver;
    g->visited[start_ver] = 1;
    q->front=0;
    q->rear=0;
    q->end[0]=start_ver;
    q->start[0]=-1;
    do
    {   
        s=q->end[q->front];
        NODE* temp=g->h[s];
        while (temp!=NULL )
        {
            if (g->visited[temp->vertex_id]==0)
            {
                q->rear++;
                q->start[q->rear]=s;
                q->end[q->rear]=temp->vertex_id;
                g->visited[temp->vertex_id] = 1;
            }
            temp=temp->link;
        }
        q->front++;
        
    } while (q->front<=q->rear);
}
void initvisited(int visited[MAX],int n)
{
    for(int i=0;i<n;i++)
        visited[i]=0;
}
int bfs_traversal(GPH *g, int start_ver,int destination,int bfs_path[MAX])
{   
    int k=-1,c=0;
    QUEUE q;
    initQueue(&q);
    bfs(g,start_ver,&q); 
    int i=0;
    while(i < q.rear+1)
    {
        if (q.end[i] == destination)
        {
            k=i;
            break;
        }
        i++;
    }
    if (k!=-1)
    {   
        bfs_path[c++]=q.end[k];
        while (k!=0)
        {
            
            for (int i = 0; i < k; i++)
            {
                if (q.end[i] == q.start[k])
                {
                    k=i;
                    break;
                }
            }
            bfs_path[c++]=q.end[k];
        }
        bfs_path[c]=q.end[0];
        return c;
    }
    else
        return 0;  
}
void bfs_display(store_data* info,int bfs_path[MAX],int n)
{
	
	FILE* ptr = fopen("outbfs.txt","w");
	for (int i = n-1; i >=0; i--)
        fprintf(ptr,"%d %d\n",info->x_cor[bfs_path[i]],info->y_cor[bfs_path[i]]);
        printf("path using bfs has been sucessfully inserted into the file outbfs.txt\n");
	fclose(ptr);
}
void dfs_display(store_data* info)
{
	
	FILE* ptr = fopen("outdfs.txt","w");
	for (int i = 0; i <= len; i++)
        fprintf(ptr,"%d %d\n",info->x_cor[dfs_path[i]],info->y_cor[dfs_path[i]]);
        printf("path using dfs has been sucessfully inserted into the file outdfs.txt");
	fclose(ptr);
}

int DFS(GPH* g, int start_ver,int destination) 
{
    NODE* temp = g->h[start_ver];
    g->visited[start_ver] = 1;
    while (temp != NULL) 
    {
        
        if (g->visited[temp->vertex_id] == 0) 
        {
            len++;
            dfs_path[len]=temp->vertex_id;
            if((temp->vertex_id==destination)|| DFS(g,temp->vertex_id,destination))
                return 1;
        }
        temp = temp->link;
    }
    --len;
    return 0;
}
int dfs_traversal(GPH *g, int start_ver,int dest_ver)
{   
    initvisited(g->visited,g->num_ver);
    dfs_path[len] = start_ver;
    int c=DFS(g,start_ver,dest_ver);
    return c;
}
