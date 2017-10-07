#include <stdio.h>

int gcd(int x, int y) {
	int tmp;
    while(x) {
        tmp = x;
        x = y % x;
        y = tmp;
    }
    return y;
}


typedef struct Fraction {
	int num, den;
} Fraction;

void initFraction(Fraction *x) {
	x->num = 0;
	x->den = 1;
}

void print_Fraction(Fraction *x) {
	printf("%d/%d\n", x->num, x->den);
}

void plus_equal(Fraction *x, Fraction *y, int den, int num) {
	int yden = y->den * den,
		ynum = y->num * num;
	int r = gcd(yden, ynum);
	yden /= r;
	ynum /= r;
	int new_den = x->den * yden,
		new_num = x->num * yden + x->den * ynum;
	r = gcd(new_den, new_num);
	x->den = new_den / r;
	x->num = new_num / r;
}


Fraction prob[16][16];

int main() {
	int N, a, b;
	scanf("%d", &N);
	prob[0][0].num = prob[0][0].den = 1;
	for(int i = 0; i < N; ++i) {
		initFraction(&prob[i+1][0]);
		for(int j = 0; j <= i; ++j) {
			scanf("%d %d", &a, &b);
			int r = gcd(a, b);
			a /= r;
			b /= r;
			plus_equal(&prob[i+1][j], &prob[i][j], a+b, a);
			initFraction(&prob[i+1][j+1]);
			plus_equal(&prob[i+1][j+1], &prob[i][j], a+b, b);
		}
	}
	for(int j = 0; j <= N; ++j) {
		print_Fraction(&prob[N][j]);
	}
}