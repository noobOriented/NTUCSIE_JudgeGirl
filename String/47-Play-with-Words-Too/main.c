#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
typedef struct treeNode {
    char c;
    int n, size;
    struct treeNode *left, *right;
} Node;
 
Node* newNode(char c, int n, int size){
    Node *x;
    x = (Node*) malloc(sizeof(Node));
    x->left = NULL;
    x->right = NULL;
    x->c = c;
    x->n = n;
    x->size = size;
    return x;
}
 
 
Node* insert_left(Node *x, char c, int n) {
    if(x == NULL)
        return newNode(c, n, n);
    x->size += n;
    if(x->left == NULL){
        if(c == x->c)
            x->n += n;
        else{
            x->left = newNode(c, n, n);
        }
    }else{
        x->left = insert_left(x->left, c, n);
    }
    return x;
}
 
Node* insert_right(Node *x, char c, int n) {
    if(x == NULL)
        return newNode(c, n, n);
    x->size += n;
    if(x->right == NULL){
        if(c == x->c)
            x->n += n;
        else {
            x->right = newNode(c, n, n);
        }
    }else
        x->right = insert_right(x->right, c, n);
    return x;
}
 
Node* insert(Node *x, int loc, char c, int n){
    if(x == NULL)
        return newNode(c, n, n);
    //插入位置在左邊
    x->size += n;
    int left_size = 0;
    if(x->left != NULL)
        left_size = x->left->size;
    if(loc < left_size){
        x->left = insert(x->left, loc, c, n);
    } //插入位置在右邊，改變loc以符合在右側的index
    else if(loc > left_size + x->n){
        x->right = insert(x->right, loc - (left_size + x->n), c, n);
    }
    else {
        if(c == x->c) {
            x->n += n;
        } //插入位置為現在區塊的正左方，插入左子樹的最右邊
        else if(loc == left_size){
            x->left = insert_right(x->left, c, n);
        } //插入位置為現在區塊的正右方，插入右子樹的最左邊
        else if(loc == left_size + x->n){
            x->right = insert_left(x->right, c, n);
        } // 插入現有區塊的正中間，將其分割為二
        else {
            x->left = insert_right(x->left, x->c, loc - left_size);
            x->right = insert_left(x->right, x->c, left_size + x->n - loc);
            x->c = c;
            x->n = n;
        }
    }
    return x;
}
 
void printList(Node *x){
    if(x == NULL)
        return;
    printList(x->left);
    printf("%c %d ", x->c, x->n);
    printList(x->right);
}
 
int main() {
    int n;
    Node* root = NULL;
    char c, command[8], pos[8];
    while(scanf("%s ", command) != EOF) {
        if(command[0] == 'i'){
            scanf("%s ", pos);
            scanf("%c", &c);
            scanf("%d", &n);
            if(pos[0] == 'l')
                root = insert_left(root, c, n);
            else if(pos[0] == 'r')
                root = insert_right(root, c, n);
            else
                root = insert(root, atoi(pos) - 1, c, n);
        }else{
            printList(root);
            printf("$\n");
        }
    }
    return 0;
}