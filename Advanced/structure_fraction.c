#include "fraction.h"

long long gcd(long long a, long long b) {
	long long tmp;
	if(a < 0)
		a = -a;
	if(b < 0)
		b = -b;
    while(a) {
        tmp = a;
        a = b % a;
        b = tmp;
    }
    return b;
}

Frac normal(long long a, long long b) {
    long long d = gcd(a, b);
    Frac new;
    new.a = a / d;
    new.b = b / d;
    return new;
}
Frac add(Frac x, Frac y) {
    return normal(x.a * y.b + y.a * x.b, x.b * y.b);
}
Frac subtract(Frac x, Frac y) {
    return normal(x.a * y.b - y.a * x.b, x.b * y.b);
}
Frac multipy(Frac x, Frac y) {
    return normal(x.a * y.a, x.b * y.b);
}
Frac divide(Frac x, Frac y) {
    return normal(x.a * y.b, x.b * y.a);
}