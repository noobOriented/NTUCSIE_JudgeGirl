#include "account.h"
#include <stdio.h>
#include <stdlib.h>

#define AGE 1
#define ZIPCODE 2

FILE *f;

int fsize() {
	int prev = ftell(f);
	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, prev, SEEK_SET);
	return size;
}

int accountNum_cmp(const void *a, const void *b) {
	Account *c = (Account*) a, *d = (Account*) b;
	return c->accountNum > d->accountNum? 1:-1;
}

int age_cmp(const void *a, const void *b) {
	Account *c = (Account*) a, *d = (Account*) b;
	return c->age > d->age? 1:-1;
}

int zipcode_cmp(const void *a, const void *b) {
	Account *c = (Account*) a, *d = (Account*) b;
	return c->zipcode > d->zipcode? 1:-1;
}


int main() {
	char file_name[64];
	scanf("%s", file_name);
	f = fopen(file_name, "rb");
	int n = fsize() / sizeof(Account);
	Account *a = (Account*) malloc(sizeof(Account) * n);
	fread(a, sizeof(Account), n, f);
	qsort(a, n, sizeof(Account), accountNum_cmp);
	printf("account, age, zipcode, balance\n");
	for (int i = 0; i < n; ++i) {
		printf("%d, %d, %d, %d\n", a[i].accountNum, a[i].age, a[i].zipcode, a[i].balance);
	}
	int sum, tmp;
	#if defined SORTBY && SORTBY == AGE
		printf("age, sum_balance\n");
		qsort(a, n, sizeof(Account), age_cmp);
		sum = a[0].balance, tmp = a[0].age;
		for(int i = 1; i < n; ++i) {
			if(tmp == a[i].age) {
				sum += a[i].balance;
			} else {
				printf("%d, %d\n", tmp, sum);
				tmp = a[i].age;
				sum = a[i].balance;
			}
		}
		printf("%d, %d\n", tmp, sum);
	#elif defined SORTBY && SORTBY == ZIPCODE
		printf("zipcode, sum_balance\n");
		qsort(a, n, sizeof(Account), zipcode_cmp);
		sum = a[0].balance, tmp = a[0].zipcode;
		for(int i = 1; i < n; ++i) {
			if(tmp == a[i].zipcode) {
				sum += a[i].balance;
			} else {
				printf("%d, %d\n", tmp, sum);
				tmp = a[i].zipcode;
				sum = a[i].balance;
			}
		}
		printf("%d, %d\n", tmp, sum);
	#endif
}