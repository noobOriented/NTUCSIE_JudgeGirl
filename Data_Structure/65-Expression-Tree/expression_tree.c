#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct treeNode {
  char value[33];
  struct treeNode *left, *right;
}TreeNode;
 
 
TreeNode* stack[300];
char name_variable[50][33];
int n = 0, value_variable[50];
 
TreeNode* newTreeNode(char *input){
  TreeNode *current;
  current = (TreeNode*) malloc(sizeof(TreeNode));
  assert(current != NULL);
  current->left = NULL;
  current->right = NULL;
  strcpy(current->value, input);
  return current;
}
 
int getValue(TreeNode *root) {
  if (root->left == NULL){
    if(isdigit(root->value[0]))
      return atoi(root->value);
    else{
      for(int i = 0; i < n; ++i){
        if(!strcmp(name_variable[i], root->value))
          return value_variable[i];
      }
    }
    return 0;
  }else {
    switch (root->value[0]) {
      case '+':
        return getValue(root->left) + getValue(root->right);
      case '-':
        return getValue(root->left) - getValue(root->right);
      case '*':
        return getValue(root->left) * getValue(root->right);
      default:
        return getValue(root->left) / getValue(root->right);
    }
  }
 
}
 
int main(){
  int top = 0, brackets = 0;
  char tmp, input[33];
  scanf("%s ", input);
  if(input[0] == '(')
    brackets++;
  else{
    stack[top] = newTreeNode(input);
  }
 
  while(brackets > 0) {
    scanf("%s ", input);
    if(input[0] == '(')
      brackets++;
    else if(input[0] == ')'){
      stack[top-3]->right = stack[top-1];
      stack[top-3]->left = stack[top-2];
      top -= 2;
      brackets--;
    }else{
      stack[top] = newTreeNode(input);
      top++;
    }
  }
  while(scanf("%s ", name_variable[n]) != EOF) {
    scanf("%c ", &tmp);
    scanf("%d", &value_variable[n]);
    n++;
  }
  printf("%d", getValue(stack[0]));
  return 0;
}