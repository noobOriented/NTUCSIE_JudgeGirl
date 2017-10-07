#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int wealth;
	char name[12];
} Person;

Person person[1024];

FILE *f;

int fsize() {
	int prev = ftell(f);
	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, prev, SEEK_SET);
	return size;
}

int wealth_cmp(const void *c, const void *d) {
	Person *a = (Person*) c;
	Person *b = (Person*) d;
	int wa = a->wealth, wb = b->wealth;
	if(wa == wb)
		return strcmp(a->name, b->name);
	return wa > wb ? 1 : -1;
}

int main(int argc, char const *argv[]) {
	f = fopen(argv[1], "rb");
	int N = fsize() / 16;
	for(int i = 0; i < N; ++i) {
		fread(person[i].name, 12, 1, f);
		fread(&(person[i].wealth), 4, 1, f);
	}
	fclose(f);

	qsort(person, N, sizeof(Person), wealth_cmp);

	int count = 1, new_level;
	for(int i = 0; i < N - 1; ++i) {
		if(person[i].wealth / 1000 < person[i + 1].wealth / 1000) {
			printf("%d\n", count);
			count = 1;
		} else
			count++;
	}
	printf("%d\n", count);
	printf("%s\n", person[0].name);
	int tail = N - 1;
	while(tail >= 1 && person[tail].wealth == person[tail-1].wealth)
		tail--;
	printf("%s\n", person[tail].name);
	if(N & 1)
		printf("%d\n", person[N / 2].wealth);
	else {
		long long int median = ((long long int)(person[(N / 2) - 1].wealth)
							 + person[N / 2].wealth) / 2;
		printf("%lld\n", median);
	}
	return 0;
}