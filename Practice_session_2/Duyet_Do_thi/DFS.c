#include <stdio.h>
#define MAX_N 100
typedef int Element_type;
typedef struct
{
    Element_type A[MAX_N][MAX_N];
    int n, m;
} Graph;
void init_graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = 0;
    }
}
void add_adge(Graph *G, int x, int y)
{
    G->A[x][y] += 1;
    G->A[y][x] += 1;
}
int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] == 1 && G->A[y][x] == 1;
}

typedef struct
{
    Element_type data[MAX_N];
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
Element_type element_at(List *L, int i)
{
    return L->data[i - 1];
}
typedef struct{
    Element_type data[MAX_N];
    int index;
}Stack;
void make_null_Stack(Stack *S){
    S->index=-1;
}
void push(Stack *S, int x){
    S->index++;
    S->data[S->index]=x;
}
void pop(Stack *S){
    S->index--;
}
Element_type  top(Stack *S){
    return S->data[S->index];
}
int empty_Stack(Stack *S){
    return S->index==-1;
}
List neighbors(Graph *G, int x)
{
    List L;
    make_null_List(&L);
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (adjacent(G, x, i))
            push_back(&L, i);
    }
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

List DFS(Graph *G, int x){
    List L_dfs;
    make_null_List(&L_dfs);
    Stack S;
    make_null_Stack(&S);
    push(&S, x);
    int mark[MAX_N];
    int i;
    for(i=1; i<=G->n; i++)
        mark[i]=0;
    while(!empty_Stack(&S)){
        int u=top(&S);
        pop(&S);
        if(!mark[u]){
            // printf("%d\n", u);
            push_back(&L_dfs, u);
            mark[u]=1;
            List L=neighbors(G, u);
            for(i=1; i<=L.size; i++){
                int k=element_at(&L, i);
                if(!mark[k]){
                    push(&S, k);
                }
            }
        }
    }
    return L_dfs;
}

int main()
{
    int i, m, n;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    int x, y;
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        add_adge(&G, x, y);
    }
    // print_graph(&G);
    int mark_dfs[MAX_N];
    for (i = 1; i <= G.n; i++)
        mark_dfs[i] = 0;
    for (i = 1; i <= G.n; i++)
    {
        if (!mark_dfs[i])
        {
            List L = DFS(&G, i);
            int j;
            for (j = 1; j <= L.size; j++) 
            {
                int k = element_at(&L, j);
                printf("%d\n", element_at(&L, j));
                mark_dfs[k] = 1;
            }
        }
    }
    return 0;
}
