#include <stdio.h>
#include <string.h>
#define max(x, y) x>y? x:y;
 
 
int main() {
    int i, j, lx, ly, tmp, tmp2, LCS[1 << 16];
    char X[1 << 16], Y[1 << 16];
    while(scanf("%s%s", X, Y) == 2) {
        lx = strlen(X), ly = strlen(Y);
        for(j = 0; j <= ly; ++j)
            LCS[j] = 0;
        for(i = 1; i <= lx; ++i) {
        	tmp = 0;
            for(j = 1; j <= ly; ++j) {
                if(X[i - 1] == Y[j - 1]) {
                	tmp2 = tmp;
                	tmp = LCS[j];
                    LCS[j] = tmp2 + 1;
                }
                else {
                	tmp = LCS[j];
                    LCS[j] = max(tmp, LCS[j - 1]);
                }
            }
        }
        printf("%d\n", LCS[ly]);
    }
}