#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return *(int*)a - *(int*)b;
}

int a[9], b[9], next[9], n;

void permutation(int min_i, int i){
    int j, previous;
    if (i == n){
        for (j = 0; j < n; ++j){
            printf("%d ", b[j]);
        }
        printf("\n");
        return;
    }
    j = next[min_i];
    previous = min_i;
    b[i] = a[min_i];
    permutation(j, i + 1);
    while(j != -1){
        b[i] = a[j];
        next[previous] = next[j];
        permutation(min_i, i + 1);
        next[previous] = j;
        previous = j;
        j = next[j];
    }
}
 
int main(){
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (i = 0; i < n-1; ++i)
        next[i] = i + 1;
    next[n-1] = -1;
    qsort(a, n, sizeof(int), cmpfunc);
    permutation(0, 0);
    return 0;
}