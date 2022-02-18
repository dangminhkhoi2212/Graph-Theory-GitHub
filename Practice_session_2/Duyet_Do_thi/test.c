#include <stdio.h>
int max(int a, int b){
    return a>b ? a:b;
}
int main(){

    int a ,b;
    scanf("%d %d", &a, &b);
    int maxn=max(a,b);

    printf("%d ", maxn);
    return 0;
}