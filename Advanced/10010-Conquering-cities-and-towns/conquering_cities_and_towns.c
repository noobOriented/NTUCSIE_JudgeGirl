#include <stdio.h>
#include <stdbool.h>
 
bool land[1000][1000];
int x[1000000], y[1000000];
 
void query(int lx, int ly, int rx, int ry) {
    int S = 0;
    for(int i = lx; i <= rx; ++i) {
        for(int j = ly; j <= ry; ++j) {
            if(!land[i][j]) {
            	land[i][j] = 1;
            	x[S] = i;
            	y[S] = j;
                S++;
            }
        }
    }
    printf("%d", S);
    for(int i = 0; i < S; ++i)
    	printf(" (%d, %d)", x[i], y[i]);
    printf("\n");
}
 
 
int main() {
    int N, M, Q, lx, ly, rx, ry;
    //memset(land, 0, sizeof(land));
    scanf("%d %d\n", &N, &M);
    scanf("%d\n", &Q);
    for(int i = 0; i < Q; ++i) {
        scanf("%d %d %d %d\n", &lx, &ly, &rx, &ry);
        query(lx, ly, rx, ry);
    }
}