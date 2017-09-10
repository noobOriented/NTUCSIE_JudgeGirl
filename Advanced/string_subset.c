#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct treeNode {
    char c;
    struct treeNode *left, *right, *next;
} Node;

Node* newNode(char *str) {
	if(*str == '\0')
		return NULL;
    Node *new;
    new = (Node*) malloc(sizeof(Node));
    assert(new != NULL);
    new->c = *str;
    new->left = NULL;
    new->right = NULL;
	new->next = newNode(str + 1);
    return new;
}

Node* insert(Node *x, char *str) {
    if(x == NULL)
        return newNode(str);
    if(*str == x->c)
    	x->next = insert(x->next, str + 1);
    else if(*str < x->c)
        x->left = insert(x->left, str);
    else if(*str > x->c)
        x->right = insert(x->right, str);
    return x;
}

char output[501];

void printSubset(Node *x, int i) {
    if(x == NULL)
        return;
    printSubset(x->left, i);
    output[i] = x->c;
    output[i + 1] = '\0';
    printf("%s\n", output);
    printSubset(x->next, i + 1);
    printSubset(x->right, i);
}
 
int main() {
    int len;
    Node *root = NULL;
    char input[501];
    scanf("%s", input);
    len = strlen(input);
    for(int i = 0; i < len; ++i) {
        root = insert(root, input + i);
    }
    printSubset(root, 0);
    return 0;
}