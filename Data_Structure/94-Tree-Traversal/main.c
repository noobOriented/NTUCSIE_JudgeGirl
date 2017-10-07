#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
 
 
typedef struct treenode{
    int data;
    struct treenode *left;
    struct treenode *right;
} TreeNode;
 
TreeNode* stack[1000];
 
void print_HLHR_tree(TreeNode *root);
 
void print_HRHL_tree(TreeNode *root){
    if (root == NULL)
        return;
    printf("%d\n", root->data);
    print_HLHR_tree(root->right);
    printf("%d\n", root->data);
    print_HLHR_tree(root->left);
    return;
}
 
void print_HLHR_tree(TreeNode *root){
    if (root == NULL)
        return;
    printf("%d\n", root->data);
    print_HRHL_tree(root->left);
    printf("%d\n", root->data);
    print_HRHL_tree(root->right);
    return;
}
 
TreeNode* buildNode(int data){
    TreeNode *current;
    current = (TreeNode*) malloc(sizeof(TreeNode));
    assert(current != NULL);
    current->data = data;
    current->left = NULL;
    current->right = NULL;
    return current;
}
 
TreeNode* construct_tree(TreeNode *left, TreeNode *right){
    TreeNode *current;
    current = (TreeNode*) malloc(sizeof(TreeNode));
    assert(current != NULL);
    current->data = left->data + right->data;
    current->left = left;
    current->right = right;
    return current;
}
 
int main() {
    int top = 0;
    char *ptr;
    char buffer[4096];
    scanf("%s", buffer);
    ptr = buffer;
    while(*ptr != '\0'){
        if (isdigit(*ptr)){
            int data;
            sscanf(ptr, "%d", &data);
            TreeNode *newNode = buildNode(data);
            stack[top++] = newNode;
            while(isdigit(*ptr))
                ptr++;
        }else if (*ptr == ')'){
            TreeNode *right = stack[--top];
            TreeNode *left = stack[--top];
            TreeNode *root = construct_tree(left, right);
            stack[top++] = root;
            ptr++;
        }else
            ptr++;
    }
    print_HLHR_tree(stack[0]);
    return 0;
}