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
    return G->A[x][y] == 1 && G->A[y][x]==1;
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
int mark[MAX_N], parent[MAX_N];
// int DFS(Graph *G, int x){
//     mark[x]=1;
//     List L=neighbours(G, x);
//     int i;
//     for(i=1; i<=L.size; i++){
//         int y=element_at(&L, i);
//         parent[y]=x;
//         if(mark[y]==0){
//             if(DFS(G, y))
//                 return 1;
//         }
//         else if(y!=parent[x])
//             return 1;
//     }
//     return 0;
// }
typedef struct
{
    int data[MAX_N];
    int front, rear;
} Queue;
void make_null_queue(Queue *G)
{
    G->front = 0;
    G->rear = -1;
}
void enqueue(Queue *Q, int x)
{
    Q->rear++;
    Q->data[Q->rear] = x;
}
void dequeue(Queue *Q)
{
    Q->front++;
}
int front(Queue *Q)
{
    return Q->data[Q->front];
}
int empty(Queue *Q)
{
    return Q->front > Q->rear;
}
int DFS(Graph *G, int x){
    Queue Q;
    make_null_queue(&Q);
    enqueue(&Q, x);
    mark[x]=1;
    parent[x]=0;
    while(!empty(&Q)){
        int v=front(&Q);
        dequeue(&Q);
        List L=neighbours(G, v);
        int i;
        for(i=1; i<=L.size; i++){
            int k=element_at(&L, i);
            if(!mark[k]){
                mark[k]=1;
                parent[k]=v;
                enqueue(&Q, k);
            }
            else if(k!=parent[v]){
               return 1;
            }
        }
    }
    return 0;
}
int main()
{
    freopen("dt.txt", "r", stdin);
    int i, n, m;
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
    for(i=1; i<=G.n; i++){
        parent[i]=mark[i]=0;
    }
    parent[1]=0;
    if(DFS(&G, 1))
        printf("YES");
    else printf("NO");
    return 0;
}
