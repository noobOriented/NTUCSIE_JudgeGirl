#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char dictionary[100000][128];

int loc[128];

int cmp(char *a, char *b) {
    return strlen(a) - strlen(b);
}

int main() {
    int N, Q;
    scanf("%d\n", &n);
    for(int i = 0; i < N; ++i) {
        scanf("%s", dictionary[i]);
    }
    qsort(dictionary, N, 128, cmp);
    int length = 0;
    for(int i = 0; i < N; ++i) {
        if(length != strlen(dictionary[i])) {
            loc[length] = i;
            length = strlen(dictionary[i]);
        }
    }
    loc[length + 1] = N;
    return 0;
}