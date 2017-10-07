#include <stdio.h>
#include <stdlib.h>

int n, m;
int a[128], friends[128][128];

int indepenent(int i, int k) {
    if (k == m) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", a[j]);
        }
        printf("%d\n", a[m - 1]);
        return 1;
    }
    if(m - k > n - i)
    	return 0;
    for(int j = 0; j < k; ++j) {
    	if(friends[a[j]][i])
            return indepenent(i + 1, k);
    }
    a[k] = i;
    return indepenent(i + 1, k + 1) || indepenent(i + 1, k);
}
 
int main() {
    while(scanf("%d %d\n", &n, &m) != EOF) {
	    for (int i = 0; i < n; ++i) {
	    	for (int j = 0; j < n; ++j) {
	        	scanf("%d", &friends[i][j]);
	        }
	    }
	    if(!indepenent(0, 0))
	    	printf("no solution\n");
	}
    return 0;
}