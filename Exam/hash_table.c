#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct treeNode {
    char str[128];
    struct treeNode *left, *right;
} Node;
 
Node* newNode(char str[]) {
    Node *new;
    new = (Node*) malloc(sizeof(Node));
    assert(new != NULL);
    strcpy(new->str, str);
    new->left = NULL;
    new->right = NULL;
    return new;
}
 
Node* insert(Node *x, char str[]) {
    if(x == NULL)
        return newNode(str);
    int cmp = strcmp(str, x->str);
    if(cmp < 0)
        x->left = insert(x->left, str);
    else if(cmp > 0)
        x->right = insert(x->right, str);
    return x;
}
 
int search(Node *root, char str[]) {
    int cmp;
    Node *x = root;
    while(x != NULL) {
        cmp = strcmp(str, x->str);
        if(cmp < 0)
            x = x->left;
        else if(cmp > 0)
            x = x->right;
        else
            return 1;
    }
    return 0;
}
 
int S, N, Q;
 
void putTable(Node *table[], char str[]) {
    int index = 0, len = strlen(str);
    for(int i = 0; i < len; ++i) {
        if(isdigit(str[i]))
            index += str[i] - '0';
        else
            index += str[i];
    }
    index %= S;
    table[index] = insert(table[index], str);
}
 
int searchTable(Node *table[], char str[]) {
    int index = 0, len = strlen(str);
    for(int i = 0; i < len; ++i) {
        if(isdigit(str[i]))
            index += str[i] - '0';
        else
            index += str[i];
    }
    index %= S;
    if(search(table[index], str))
        return index;
    else
        return -1;
}
 
int main() {
    char input[128];
    Node* hashtable[1024];
    scanf("%d %d %d\n", &S, &N, &Q);
    for(int i = 0; i < N; ++i) {
        scanf("%s", input);
        putTable(hashtable, input);
    }
    for(int i = 0; i < Q; ++i) {
        scanf("%s", input);
        printf("%d\n", searchTable(hashtable, input));
    }
    return 0;
}