#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_N 1 << 18

struct Node {
    int idx, x[2];
    bool axis;
    Node *left, *right;
};
 
Node* newNode(int idx, int x[2], bool axis) {
    Node *t = (Node*) malloc(sizeof(Node));
    assert(t != NULL);
    t->idx = idx;
    t->x[0] = x[0];
    t->x[1] = x[1];
    t->axis = axis;
    t->left = NULL;
    t->right = NULL;
    return t;
}
 
Node* insert(Node *t, int idx, int x[2], bool axis) {
    if(t == NULL)
        return newNode(idx, x, axis);
    else if(x[axis] < t->x[axis])
        t->left = insert(t->left, idx, x, !axis);
    else
        t->right = insert(t->right, idx, x, !axis);
    return t;
}
 
float get_dist(Node *t, int x[2]) {
    int dx = t->x[0] - x[0],
        dy = t->x[1] - x[1];
    return sqrt(dx * dx + dy * dy);
}
 
float min;
int ans_n = 0, ans_i[MAX_N], ans_j[MAX_N];

void search(Node *t, int x[2], int i) {
    if(t == NULL)
        return;
    float dist = get_dist(t, x);
    if(dist < min) {
        min = dist;
        ans_i[0] = t->idx;
        ans_j[0] = i;
        ans_n = 1;
    } else if(dist == min) {
        ans_i[ans_n] = t->idx;
        ans_j[ans_n] = i;
        ans_n++;
    }
    int dx = x[t->axis] - t->x[t->axis];
    if(dx <= -min)
        search(t->left, x, i);
    else if(dx >= min)
        search(t->right, x, i);
    else if(dx > 0) {
        search(t->right, x, i);
        search(t->left, x, i);
    } else {
        search(t->left, x, i);
        search(t->right, x, i);
    }
}
 
int main() {
    int N, x[2];
    Node *root = NULL;
    scanf("%d", &N);
    min = 30000.0;
    for(int i = 1; i <= N; ++i) {
        scanf("%d %d", &x[0], &x[1]);
        search(root, x, i);
        root = insert(root, i, x, 0);
    }
    printf("%.2f %d\n", min, ans_n);
    for(int i = 0; i < ans_n; ++i) {
        printf("%d %d\n", ans_i[i], ans_j[i]);
    }
    return 0;
}