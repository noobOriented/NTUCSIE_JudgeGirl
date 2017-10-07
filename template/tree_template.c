#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct treeNode {
    int v;
    struct treeNode *left, *right;
} Node;

Node* newNode(int v) {
    Node *new;
    new = (Node*) malloc(sizeof(Node));
    assert(new != NULL);
    new->v = v;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node* insert(Node *x, int v) {
    if(x == NULL)
        return newNode(v);
    else if(v < x->v)
        x->left = insert(x->left, v);
    else if(v > x->v)
        x->right = insert(x->right, v);
    return x;
}

Node* search(Node *x, int v) {
    if(x == NULL)
        return NULL;
    if(v < x->v)
        return search(x->left, v);
    else if(v > x->v)
        return search(x->right, v);
    return x;
}

int main() {
    int n, input;
    Node *root = NULL;
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &input);
        root = insert(root, input);
    }
    return 0;
}