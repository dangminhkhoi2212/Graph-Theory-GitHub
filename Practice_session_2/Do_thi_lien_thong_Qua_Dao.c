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
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = 0;
}
void add_edges(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}
int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] == 1;
}

typedef struct
{
    int data[MAX_N];
    int size;
} List;

void make_null_List(List *L)
{
    L->size = 0;
}
void push_back(List *L, int x)
{
    L->data[L->size] = x;
    L->size++;
}
int element_at(List *L, int i)
{
    return L->data[i - 1];
}
List neighbours(Graph *G, int x)
{
    int i;
    List L;
    make_null_List(&L);
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, x, i))
            push_back(&L, i);
    return L;
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
typedef struct
{
    int data[MAX_N];
    int index;
} Stack;
void make_null_stack(Stack *S)
{
    S->index = 0;
}
void push_stack(Stack *S, int x)
{
    S->data[S->index] = x;
    S->index++;
}
void pop(Stack *S)
{
    S->index--;
}
int top(Stack *S)
{
    return S->data[S->index - 1];
}
int emptyStack(Stack *S)
{
    return S->index == 0;
}
List DFS(Graph *G, int x, int parent[])
{
    int i;
    int mark[MAX_N];
    for (i = 1; i <= G->n; i++)
        mark[i] = 0;
    Stack S;
    make_null_stack(&S);
    push_stack(&S, x);
    parent[x] = 0;
    List L_dfs;
    make_null_List(&L_dfs);
    while (!emptyStack(&S))
    {
        int u = top(&S);
        pop(&S);
        if (mark[u] == 1)
            continue;
        // printf("%d\n", u);
        push_back(&L_dfs, u);
        mark[u] = 1;
        List L = neighbours(G, u);
        for (i = 1; i <= L.size; i++)
        {
            int k = element_at(&L, i);
            if (mark[k] == 0)
            {
                push_stack(&S, k);
                parent[k] = u;
            }
        }
    }
    return L_dfs;
}
int main()
{
    int i, j, n, m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    int x, y;
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        add_edges(&G, x, y);
    }
    // print_graph(&G);
    int mark_dfs[MAX_N];
    for (i = 1; i <= G.n; i++)
        mark_dfs[i] = 0;
    int parent[MAX_N];
    for (i = 1; i <= G.n; i++)
        parent[i] = 0;
    int visit=0;
    for (i = 1; i <= G.n; i++)
    {
        if (mark_dfs[i] == 0)
        {
            visit++;
            List L = DFS(&G, i, parent);
            for (j = 1; j <= L.size; j++)
            {
                int k = element_at(&L, j);
                // printf("%d\n", k);
                mark_dfs[k] = 1;
            }
        }
    }
    if (visit==1)
        printf("YES");
    else
        printf("NO");
    return 0;
}
