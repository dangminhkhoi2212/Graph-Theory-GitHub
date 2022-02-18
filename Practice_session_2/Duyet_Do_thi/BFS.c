#include <stdio.h>
#define MAX_N 100
typedef int Element_type;
typedef struct{
    Element_type A[MAX_N][MAX_N];
    int n, m;
}Graph;
void init_graph(Graph *G, int n){
    int i, j;
    G->n=n;
    for(i=1; i<=G->n; i++){
        for(j=1;j<=G->n; j++)
            G->A[i][j]=0;
    }
}
void add_adge(Graph *G, int x, int y){
    G->A[x][y]+=1;
    G->A[y][x]+=1;
}
int adjacent(Graph *G, int x, int y){
    return G->A[x][y]==1 && G->A[y][x]==1;
}

typedef struct{
    Element_type data[MAX_N];
    int size;
}List;
void make_null_List(List *L){
    L->size=0;
}
void push_back(List *L, int x){
    L->data[L->size]=x;
    L->size++;
}
Element_type element_at(List *L, int i){
    return L->data[i-1];
}
typedef struct{
    Element_type data[MAX_N];
    int front, rear;
}Queue;
void make_null_Queue(Queue *Q){
    Q->front=0;
    Q->rear=-1;
}
void enQueue(Queue *Q, int x){
    Q->rear++;
    Q->data[Q->rear]=x;
}
void deQueue(Queue *Q){
    Q->front++;
}
int emptyQueue(Queue *Q){
    return Q->front>Q->rear;
}
Element_type front(Queue *Q){
    return Q->data[Q->front];
}
List neighbors(Graph *G, int x)
{
    List L;
    make_null_List(&L);
    int i;
    for(i=1; i<=G->n; i++){
        if(adjacent(G, x, i))
            push_back(&L, i);
    }
    return L;
}
void print_graph(Graph *G){
    int i, j;
    for(i=1; i<=G->n; i++){
        for(j=1; j<=G->n; j++)
            printf("%d ", G->A[i][j]);
        printf("\n");
    }
}
List BFS(Graph *G, int x){
    List L_bfs;
    make_null_List(&L_bfs);
    int mark[MAX_N];
    int i;
    for(i=1; i<=G->n; i++)
        mark[i]=0;
    Queue Q;
    make_null_Queue(&Q);
    enQueue(&Q, x);
    while(!emptyQueue(&Q)){
        int y=front(&Q);
        deQueue(&Q);
        if(!mark[y]){
            // printf("%d\n", y);
            push_back(&L_bfs, y);
            mark[y]=1;
            List L=neighbors(G, y);
            for(i=1; i<=L.size; i++){
                int u=element_at(&L, i);
                if(!mark[u])
                    enQueue(&Q, u);
            }
        }
    }
    return L_bfs;
}
int main(){
    int i,m, n;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    int x, y;
    for(i=1; i<=m; i++){
        scanf("%d%d", &x, &y);
        add_adge(&G, x, y);
    }
    // print_graph(&G);
    int mark_bfs[MAX_N];
    for(i=1; i<=G.n; i++)
        mark_bfs[i]=0;
    for(i=1; i<=G.n; i++){
        if(!mark_bfs[i]){
            List L=BFS(&G, i);
            int j;
            for(j=1; j<=L.size; j++){
                int k=element_at(&L, j);
                printf("%d\n", element_at(&L, j));
                mark_bfs[k]=1;
            }
        }
    }
    BFS(&G, 1);
    return 0;
}