#include <stdio.h>

#define MAX_N 100
typedef struct
{
    int A[MAX_N][MAX_N];
    int n, m;
} Graph;
void init_graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}
void add_edge(Graph *G, int x, int y)
{
    if (x == y)
        G->A[x][y] += 1;
    else
    {
        G->A[x][y] += 1;
        G->A[y][x] += 1;
    }
}
void print_graph(Graph *G)
{
    int i, j;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
            printf("%d ", G->A[i][j]);
        printf("\n");
    }
}
int adjacent(Graph *G, int x, int y){
    return G->A[x][y]>0;
}
void compete(Graph *G, int x, int y){
    int i, flag=0; 
    for(i=1; i<=G->n; i++){
        if(adjacent(G, x, i) && adjacent(G, y, i)){
            printf("%d ", i);
            flag=1;
        }
    }
    if(flag!=1)
        printf("KHONG CHUNG DOI THU");
}
int main()
{
    int i, j, n;
    freopen("HeSinhThaiRung.txt", "r", stdin);
    scanf("%d\n", &n);
    Graph G;
    init_graph(&G, n);
    int x;
    for (i = 1; i <= n; i++)
        for(j=1; j<=n; j++){
            scanf("%d", &x);
            if(x>0)
                G.A[i][j]=x;
        }
    print_graph(&G);
    int u, v;
    scanf("%d %d", &u, &v);
    compete(&G,u, v );
    return 0;
}