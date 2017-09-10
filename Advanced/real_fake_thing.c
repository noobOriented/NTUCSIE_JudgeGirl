#include <stdio.h>
 
int N, M;

typedef struct int512 {
    unsigned long long ary[8];
} INT512;

INT512 item[1024];

INT512 str_to_512(char str[]) {
    INT512 output;
    for(int i = 0; i < 8; ++i) {
        output.ary[i] = 0;
    }
    for(int i = 0; i < M; ++i) {
        output.ary[i >> 6] |= (unsigned long long)(str[i] == '1') << (i & 63);
    }
    return output;
}

void print512(INT512 *a) {
    for(int i = 0; i < 64; ++i) {
        printf("%d", (a->ary[0] >> (i & 63)) & 1);
    }
    printf("\n");
}

int similar(INT512 *a, INT512 *b) {
    int inter = 0, un = 0;
    for(int i = 0; i < (M + 63)/ 64; ++i) {
        inter += __builtin_popcount(a->ary[i] & b->ary[i]);
        un += __builtin_popcount(a->ary[i] | b->ary[i]);
    }
    return (5 * inter) >= (4 * un);
}
 
int main() {
    double ratio;
    char input[1024];
    while(scanf("%d %d", &N, &M) == 2) {
        ratio = 0;
        for(int i = 0; i < N; ++i) {
            scanf("%s", input);
            item[i] = str_to_512(input);
            for(int j = 0; j < i; ++j) {
                if(similar(&item[j], &item[i]))
                    ratio++;
            }
        }
        ratio *= 200.0;
        ratio /= N * (N - 1);
        printf("%.2lf\n", ratio);
    }
    return 0;
}