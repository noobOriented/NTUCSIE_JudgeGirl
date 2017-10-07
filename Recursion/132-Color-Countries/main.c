#include <stdio.h>
int N, C, P, conflict;
int color[20], adjacent[20][20] = {0};
 
int paint(int i){
    if(i == N)
        return 1;
    for(int c = 1; c <= C; ++c){
        conflict = 0;
        for(int j = 0; j < i && !conflict; ++j){
            if(adjacent[j][i] && color[j] == c)
                conflict = 1;
        }
        if(!conflict){
            color[i] = c;
            if(paint(i + 1))
                return 1;
        }
    }
    return 0;
}
 
int main() {
    int i, a, b;
    scanf("%d %d %d", &N, &C, &P);
    for(i = 0; i < P; ++i){
        scanf("%d%d", &a, &b);
        adjacent[a][b] = 1;
        adjacent[b][a] = 1;
    }
    if(paint(0)){
        for(i = 0; i < N; ++i)
            printf("%d\n", color[i]);
    }else
        printf("no solution.\n");
}