#include <stdio.h>
#define MAX_N 100
typedef int ElementType;
typedef struct
{
    ElementType A[MAX_N][MAX_N];
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
void add_egde(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
}
int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
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
    ElementType Data[MAX_N];
    int size;
} List;
void make_null_List(List *L)
{
    L->size = 0;
}
void push_back(List *L, ElementType x)
{
    L->Data[L->size] = x;
    L->size++;
}
ElementType element_at(List *L, int i)
{
    return L->Data[i - 1];
}
typedef struct
{
    ElementType Data[MAX_N];
    int index;
} Stack;
void make_null_stack(Stack *S)
{
    S->index = 0;
}
void push(Stack *S, ElementType x)
{
    S->Data[S->index] = x;
    S->index++;
}
ElementType top(Stack *S)
{
    return S->Data[S->index - 1];
}
void pop(Stack *S)
{
    S->index--;
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
ElementType min(ElementType x, ElementType y)
{
    return x < y ? x : y;
}
ElementType num[MAX_N], min_num[MAX_N], on_stack[MAX_N];
int k = 1, check = 0;
Stack S;
void strong_connect(Graph *G, int x)
{
    num[x] = min_num[x] = k;
    k++;
    push(&S, x);
    on_stack[x] = 1;
    List L = neighbors(G, x);
    int i;
    for (i = 1; i <= L.size; i++)
    {
        int y = element_at(&L, i);
        if (num[y] < 0)
        {
            strong_connect(G, y);
            min_num[x] = min(min_num[x], min_num[y]);
        }
        else if (on_stack[y])
            min_num[x] = min(min_num[x], num[y]);
    }
    // printf("min_num[%d] = %d\n", x, min_num[x]);
    if (min_num[x] == num[x])
    {
        // printf("%d la diem khop\n", x);
        int w;
        do
        {
            w = top(&S);
            pop(&S);
            // printf("%d ", w);
            on_stack[w] = 0;
        } while (x != w);
        check += 1;
    }
}
int main()
{
    freopen("dt.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    int i, x, y;
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        add_egde(&G, x, y);
    }
    // print_graph(&G);
    for (i = 1; i <= G.n; i++)
    {
        num[i] = min_num[i] = -1;
        on_stack[i] = 0;
    }
    make_null_stack(&S);
    strong_connect(&G, 1);
    if (check == 1)
        printf("strong connected");
    else
        printf("unconnected");
    return 0;
}
