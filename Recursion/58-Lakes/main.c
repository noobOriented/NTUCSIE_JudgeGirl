#include <stdio.h>
 
int N, M, pic[400][400];
 
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a > *(int*)b );
}
 
int count(int i, int j){
    if(!pic[i][j] || i < 0 || i > N - 1 || j < 0 || j > M - 1)
        return 0;
    pic[i][j] = 0;
    return 1 + count(i+1, j) + count(i-1, j) + count(i, j-1) + count(i, j+1);
}
 
 
int main() {
    int i, j, n = 0;
    scanf("%d %d", &N, &M);
    for(i = 0; i < N; ++i){
        for(j = 0; j < M; ++j)
            scanf("%d", &pic[i][j]);
    }
    int size[N * M / 2 + 1];
    for(i = 0; i < N; ++i){
        for(j = 0; j < M; ++j){
            if(pic[i][j]){
                size[n] = count(i, j);
                n++;                
            }
        }
    }
    qsort(size, n, sizeof(int), cmpfunc);
    for(i = n - 1; i >= 0; --i)
        printf("%d\n", size[i]);
}