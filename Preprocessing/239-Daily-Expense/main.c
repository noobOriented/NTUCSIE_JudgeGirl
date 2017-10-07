#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct expense{
	int y, m, d, acc;
	char c[33];
} Expense;

Expense exp[10000];

int cmpfunc(const void *aa, const void *bb) {
	const Expense *a = (const Expense *)aa;
	const Expense *b = (const Expense *)bb;
	if(a->y != b->y)
		return a->y - b->y;
	if(a->m != b->m)
		return a->m - b->m;
	if(a->d != b->d)
		return a->d - b->d;
	if(strcmp(a->c, b->c))
		return strcmp(a->c, b->c);
	return a->acc - b->acc;

}

int same(Expense *a, Expense *b) {
	if(a->y != b->y)
		return 0;
	if(a->m != b->m)
		return 0;
	if(a->d != b->d)
		return 0;
	return !strcmp(a->c, b->c);
}

int main() {
	int i, n = 0;
	while(scanf("%d %d %d %s %d", &exp[n].y, &exp[n].m, &exp[n].d, exp[n].c, &exp[n].acc) != EOF)
		n++;
	qsort(exp, n, sizeof(Expense), cmpfunc);
	int account = 0;
	for(i = 0; i < n - 1; ++i){
		account += exp[i].acc;
		if(!same(&exp[i], &exp[i + 1])){
			printf("%d %d %d %s %d\n", exp[i].y, exp[i].m, exp[i].d, exp[i].c, account);
			account = 0;
		}
	}
	account += exp[i].acc;
	printf("%d %d %d %s %d\n", exp[i].y, exp[i].m, exp[i].d, exp[i].c, account);
	return 0;
}