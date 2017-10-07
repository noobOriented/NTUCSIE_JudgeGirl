#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_N 1 << 18

int a[MAX_N];

inline int abs(int x) {
	return x < 0? -x : x;
}


typedef struct treeNode {
    int lidx, ridx, sum;
    struct treeNode *left, *right;
} Node;

Node* newNode(int lidx, int ridx) {
    Node *t;
    t = (Node*) malloc(sizeof(Node));
    assert(t != NULL);
    t->lidx = lidx;
    t->ridx = ridx;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void construct(Node *x, int lidx, int ridx) {
	if(lidx == ridx) {
		x->sum = abs(a[lidx]);
		return;
	}
	int mid = (lidx + ridx) / 2;
	x->left = newNode(lidx, mid);
	construct(x->left, lidx, mid);
	x->right = newNode(mid + 1, ridx);
	construct(x->right, mid + 1, ridx);
	x->sum = x->left->sum + x->right->sum;
}

void printNode(Node *x) {
	if(x->left == NULL) {
		printf("%d\n", a[x->lidx]);
		return;
	}
	printNode(x->left);
	printNode(x->right);
}

int rangeSum(Node *x, int lidx, int ridx) {
	if(lidx <= x->lidx && x->ridx <= ridx)
		return x->sum;
	int mid = (x->lidx + x->ridx) / 2;
    if(ridx <= mid)
        return rangeSum(x->left, lidx, ridx);
    else if(lidx > mid)
        return rangeSum(x->right, lidx, ridx);
    return rangeSum(x->left, lidx, mid) + rangeSum(x->right, mid + 1, ridx);
}

void update(Node *x, int lidx, int ridx, int add) {
    if(x->left == NULL) {
        a[lidx] += add;
        x->sum = abs(a[lidx]);
        return;
    }
	int mid = (x->lidx + x->ridx) / 2;
    if(ridx <= mid) {
        update(x->left, lidx, ridx, add);
    }
    else if(lidx > mid)
        update(x->right, lidx, ridx, add);
    else {
	    update(x->left, lidx, mid, add);
	    update(x->right, mid + 1, ridx, add);
    }
	x->sum = x->left->sum + x->right->sum;    
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; ++i)
		scanf("%d", &a[i]);
    Node *root = newNode(0, N - 1);
   	construct(root, 0, N - 1);
   	int query, lidx, ridx, add;
   	for(int i = 0; i < M; ++i) {
   		scanf("%d", &query);
   		if(query) {
			scanf("%d %d %d", &lidx, &ridx, &add);
			update(root, lidx, ridx, add);
   		} else {
   			scanf("%d %d", &lidx, &ridx);
   			printf("%d\n", rangeSum(root, lidx, ridx));
   		}
   	}
}
