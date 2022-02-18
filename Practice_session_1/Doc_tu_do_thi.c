#include <stdio.h>

#define MAX_N 100
typedef struct{
    int A[MAX_N][MAX_N];
    int n, m;
}Graph;
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
int main(){
    int i, n, m;
    freopen("dt1.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    int x, y;
    for(i=1; i<=m; i++){
        scanf("%d%d", &x, &y);
        add_edge(&G, x, y);
    }
    print_graph(&G);
    return 0;
}