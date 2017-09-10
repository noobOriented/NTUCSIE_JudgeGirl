#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

typedef struct word {
	char str[11];
} Word;

typedef struct group {
	Word *members[50];
	Word *leader;
	int n;
} Group;

int N, L, R;
Word words[50];
Group groups[3];

int Mdist(char a[], char b[]) {
	int dist = 0;
	for(int i = 0; i < L; ++i) {
		dist += abs(a[i] - b[i]);
	}
	return dist;
}

void add_to_group(Word *w, Group *g) {
	g->members[g->n] = w;
	g->n++;
}

void choose_group(Word *w) {
	Group *g = &groups[0];
	int tmp, min = Mdist(w->str, g->leader->str);
	for(int i = 1; i < 3; ++i) {
		tmp = Mdist(w->str, groups[i].leader->str);
		if(tmp < min || (tmp == min && strcmp(groups[i].leader->str, g->leader->str) < 0)) {
			min = tmp;
			g = &groups[i];
		}
	}
	add_to_group(w, g);
}

void assign_leader(Group *g) {
	int tmp;
	char mean[10];
	for(int i = 0; i < L; ++i) {
		tmp = 0;
		for(int j = 0; j < g->n; ++j)
			tmp += g->members[j]->str[i];
		mean[i] = (char*) (tmp / g->n);
	}
	Word *w = g->members[0];
	int min = Mdist(mean, w->str);
	for(int i = 1; i < g->n; ++i) {
		tmp = Mdist(mean, g->members[i]->str);
		if(tmp < min || (tmp == min && strcmp(g->members[i]->str, w->str) < 0)) {
			min = tmp;
			w = g->members[i];
		}
	}
	g->leader = w;
	g->n = 0;
}

void print_leader() {
	char output[3][11];
	for(int i = 0; i < 3; ++i)
		strcpy(output[i], groups[i].leader->str);
	qsort(output, 3, 11, strcmp);
	for(int i = 0; i < 3; ++i)
		printf("%s\n", output[i]);
}

void print_groups() {
	for(int i = 0; i < 3; ++i) {
		printf("*%s*", groups[i].leader->str);
		for(int j = 0; j < groups[i].n; ++j)
			printf(", %s", groups[i].members[j]->str);
		printf(".\n");
	}
}

int main() {
	int i;
	scanf("%d %d %d", &N, &L, &R);
	// init groups and leaders
	for(i = 0; i < N; ++i) {
		scanf("%s", words[i].str);
		if(i < 3) {
			groups[i].leader = &words[i];
			groups[i].n = 0;
		}
	}

	for(int r = 1; r <= R; ++r) {
		for(i = 0; i < N; ++i)
			choose_group(&words[i]);
		for(i = 0; i < 3; ++i)
			assign_leader(&groups[i]);
	}
	print_leader();
	return 0;
}