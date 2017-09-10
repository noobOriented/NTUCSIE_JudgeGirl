#include <stdio.h>
#include <stdlib.h>

int n, ans;
int a[64], donation[64], hate[64][64];

void indepenent(int i, int k, int max) {
    if(max <= ans)
        return;
    if (i == n) {
        ans = max;
        return;
    }
    for(int j = 0; j < k; ++j) {
        if(hate[a[j]][i]){
            indepenent(i + 1, k, max - donation[i]);
            return;
        }
    }
    a[k] = i;
    indepenent(i + 1, k + 1, max);
    indepenent(i + 1, k, max - donation[i]);
}
 
int main() {
    int max = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &donation[i]);
        max += donation[i];
    }
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < n; ++j) {
        	scanf("%d", &hate[i][j]);
        }
    }
    ans = 0;
    indepenent(0, 0, max);
    printf("%d", ans);
    return 0;
}