long D, a, b, c, A, B, C;

int matchA(long, long);
int matchB(long, long);
int matchC(long);
 
int matchA(long sum, long i){
    if (i > a || sum > D)
        return 0;
    return (matchB(sum, 0) || matchA(sum + A, i + 1));
}
int matchB(long sum, long j){
    if (j > b || sum > D)
        return 0;
    return (matchC(sum) || matchB(sum + B, j + 1));
}
int matchC(long sum){
    if (sum == D)
        return 1;
    if (C == 0)
        return 0;
    return ((D - sum) % C == 0 && (c * C) >= (D - sum));
}
 
int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i){
        scanf("%d%d%d%d%d%d%d\n", &D, &a, &b, &c, &A, &B, &C);
        if (matchA(0, 0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}