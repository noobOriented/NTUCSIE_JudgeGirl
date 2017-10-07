#include <stdio.h>
int N, M;
double a[128][128];
 
int zero(double f) {
    return (f > 0.0? f: -f)< 0.000001;
}
 
int getHead(int i1) {
    //找出第一個非零的位置
    int j = 0;
    while(j <= M) {
        if(!zero(a[i1][j]))
            return j;
        ++j;
    }
    return -1;
}
 
void GaussElimination(int i1, int i2, int head) {
    if(zero(a[i2][head]))
        return;
    double b = a[i1][head], c = a[i2][head];
    for(int j = head; j <= M; ++j){
        a[i2][j] -= a[i1][j] * c / b;
    }
}
 
void printSol() {
    for(int j = 0; j < M; ++j) {
        if(!zero(a[N][j])) {
            printf("not sure\n");
            return;
        }
    }
    if(zero(a[N][M]))
        printf("0\n");
    else
        printf("%.0f\n", -a[N][M]);
}
 
int main() {
    int i, j, head, has_sol;
    while(scanf("%d %d\n", &N, &M) == 2) {
        for(i = 0; i < N; ++i) {
            for(j = 0; j <= M; ++j) {
                scanf("%lf", &a[i][j]);
            }
        }
        for(j = 0; j < M; ++j) {
            scanf("%lf", &a[N][j]);
        }
        a[N][M] = 0.0;
        has_sol = 1;
        for(i = 0; i < N && has_sol; ++i) {
            head = getHead(i);
            if(head == -1)
                continue;
            if(head == M) {
                has_sol = 0;
                continue;
            }
            for(j = i + 1; j <= N; ++j)
                GaussElimination(i, j, head);
        }
        /*for(i = 0; i <= N; ++i) {
            for(j = 0; j <= M; ++j) {
                printf("%f ", a[i][j]);
            }
            printf("\n");
        }*/
        if(has_sol) {
            printSol();
        } else
            printf("contradictory\n");
    }
    return 0;
}