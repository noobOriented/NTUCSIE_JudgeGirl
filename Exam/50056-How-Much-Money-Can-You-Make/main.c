#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

static inline int min(int x, int y) {
    return x < y? x : y; 
}
 
typedef struct treeNode {
    int amount, price;
    char str[64];
    struct treeNode *left, *right;
} Node;

Node* newNode(char str[], int amount, int price) {
    Node *new;
    new = (Node*) malloc(sizeof(Node));
    assert(new != NULL);
    strcpy(new->str, str);
    new->amount = amount;
    new->price = price;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node* insert(Node *x, char str[], int amount, int price) {
    if(x == NULL)
        return newNode(str, amount, price);
    int cmp = strcmp(str, x->str);
    if(cmp < 0)
        x->left = insert(x->left, str, amount, price);
    else if(cmp > 0)
        x->right = insert(x->right, str, amount, price);
    return x;
}

Node* search(Node *x, char str[]) {
    if(x == NULL)
        return NULL;
    int cmp = strcmp(str, x->str);
    if(cmp < 0)
        return search(x->left, str);
    else if(cmp > 0)
        return search(x->right, str);
    return x;
}

int main() {
    int N, M, Q, amount, price;
    char best_product[64], ingredient[64], product[64];
    Node *root = NULL, *tmp;
    scanf("%d %d\n", &N, &M);
    // 將材料建為BST 以供查詢
    for(int i = 0; i < N; ++i) {
        scanf("%s %d %d\n", ingredient, &amount, &price);
        root = insert(root, ingredient, amount, price);
    }
    int product_n, cost, max = -1;
    for(int i = 0; i < M; ++i) {
        product_n = 20000, cost = 0;
        scanf("%s %d", product, &Q);
        for(int j = 0; j < Q; ++j) {
            scanf("%s %d\n", ingredient, &amount);
            // 找到對應的材料
            tmp = search(root, ingredient);
            cost += tmp->price * amount;
            product_n = min(product_n, tmp->amount / amount);
        }
        scanf("%d", &price);
        price -= cost;
        price *= product_n;
        if(price > max || (price == max && strcmp(product, best_product) < 0)) {
            max = price;
            strcpy(best_product, product);
        }
    }
    printf("%s %d\n", best_product, max);
    return 0;
}