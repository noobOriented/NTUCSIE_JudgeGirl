#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char dictionary[100000][128];

int candidate[1000][128];

int N, Q, n_candidate;

int cmp(char *a, char *b) {
    return strlen(a) - strlen(b);
}

int similar(char *query, char *str, int length, int length2) {
    // 1 if same, 0 if else
    int flag = 0, i = 0, j = 0;
    while(i < length && j < length2){
        if(query[i] != str[j]) {
            if(flag)
                return 0;
            else {
                flag = 1;
                if(length2 > length) {
                    ++j;
                    continue;
                } else if(length2 < length) {
                    ++i;
                    continue;
                }
            }
        }
        ++i;
        ++j;
    }
    if(flag || (length != length2)) {
        strcpy(candidate[n_candidate], str);
        n_candidate++;
        return 0;
    }
    printf(">%s\n", str);
    return 1;
}

int find_query(char *query) {
    int length = strlen(query), length2;
    for(int i = 0; i < N; ++i) {
        length2 = strlen(dictionary[i]);
        if(length2 > length + 1 || length > length2 + 1)
            continue;
        if(similar(query, dictionary[i], length, length2))
            return 1;
    }
    return 0;
}

int main() {
    char query[128];
    scanf("%d\n", &N);
    for(int i = 0; i < N; ++i) {
        scanf("%s", dictionary[i]);
    }
    scanf("%d\n", &Q);
    for(int i = 0; i < Q; ++i) {
        scanf("%s", query);
        n_candidate = 0;
        if(!find_query(query)) {
            if (n_candidate > 0) {
                printf("?%s", candidate[0]);
                for(int j = 1; j < n_candidate; ++j)
                    printf(" %s", candidate[j]);
                printf("\n");
            } else
                printf("!%s\n", query);
        }
    }
    return 0;
}