#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdint.h>

uint32_t Hash(const int const * nPair, const int num){
    uint32_t ret = 0;
    for (int i=0; i<num; i++)
        ret += nPair[i] * (i+1);
    return ret;
}
 
typedef struct treeNode {
    int x[2];
    bool axis;
    struct treeNode *left, *right;
} Node;
 
Node* newNode(int x[2], bool axis) {
    Node *new;
    new = (Node*) malloc(sizeof(Node));
    assert(new != NULL);
    new->x[0] = x[0];
    new->x[1] = x[1];
    new->axis = axis;
    new->left = NULL;
    new->right = NULL;
    return new;
}
 
Node* insert(Node *t, int x, int y, bool axis) {
    if(t == NULL)
        return newNode(x, axis);
    else if(x[axis] < t->x[axis])
        t->left = insert(t->left, x, !axis);
    else
        t->right = insert(t->right, x, !axis);
    return t;
}

int D;

int detect(Node *t, int x[2]) {
	int dx = t->x[0] - x[0],
		dy = t->x[1] - x[1];
    return dx * dx + dy * dy <= D * D;
}
 
void search(Node *t, int x[2]) {
    if(t == NULL)
        return;
    int dx = x[t->axis] - t->x[t->axis];
    if(dx <= -D)
        search(t->left, x);
    else if(dx >= D)
        search(t->right, x);
    else if(dx > 0) {
        search(t->right, x);
        search(t->left, x);
    } else {
        search(t->left, x);
        search(t->right, x);
    }
}
 
int main() {
    int X, Y, N, x[2];
    Node *root = NULL;
    scanf("%d %d %d", &X, &Y, &D);
    scanf("%d %d", &N, &T);
    for(int i = 0; i < N; ++i) {
    	scanf("%d %d", x[0], x[1]);
    	root = insert(root, x, 0);
    }
    return 0;
}