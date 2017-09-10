#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


typedef struct food {
	int ni;
	char name[65];
	char ingredients[10][65];
} Food;

Food* searchByName(Food *f[], int n, char name[]) {
	for(int i = 0; i < n; ++i){
		if(!strcmp(f[i]->name, name))
			return f[i];
	}
	return NULL;
}

void showCommon(Food *fa, Food *fb) {
	int k = 0;
	char common[10][65];
	for(int i = 0; i < fa->ni; ++i) {
		for(int j = 0; j < fb->ni; ++j) {
			if(!strcmp(fa->ingredients[i], fb->ingredients[j])) {
				strcpy(common[k], fa->ingredients[i]);
				k++;
			}
		}
	}
	if(!k){
		printf("nothing\n");
		return;
	}
	qsort(common, k, sizeof(char[65]), strcmp);
	for(int i = 0; i < k - 1; ++i){
		printf("%s ", common[i]);
	}
	printf("%s\n", common[k - 1]);
}

int main() {
	int n, m;
	char a[65], b[65];
	scanf("%d", &n);
	Food *f[n];
	for(int i = 0; i < n; ++i) {
		f[i] = (Food*) malloc(sizeof(Food));
		assert(f[i] != NULL);
		scanf("%s %d", f[i]->name, &f[i]->ni);
		for(int j = 0; j < f[i]->ni; ++j) {
			scanf(" %s", f[i]->ingredients[j]);
		}
	}
	scanf("%d", &m);
	for(int i = 0; i < m; ++i) {
		scanf("%s %s", a, b);
		Food *fa = searchByName(f, n, a), *fb = searchByName(f, n, b);
		showCommon(fa, fb);
	}
	return 0;
}