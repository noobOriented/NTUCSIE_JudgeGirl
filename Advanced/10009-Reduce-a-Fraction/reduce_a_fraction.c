#include <stdio.h>
int tmp;
 
int gcd(int a, int b) {
    while(a) {
        tmp = a;
        a = b % a;
        b = tmp;
    }
    return b;
}
 
int main() {
    int a, b, c;
    while(scanf("%d %d", &a, &b) != EOF){
        if(a > b)
            c = gcd(b, a);
        else
            c = gcd(a, b);
        printf("%d / %d\n", a / c, b / c);
    }
    return 0;
}