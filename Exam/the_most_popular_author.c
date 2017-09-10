#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct auther {
    char str[64];
    int sell;
    struct auther *left, *right;
} Auther;

typedef struct book {
    char str[64];
    Auther *au;
    struct book *left, *right;
} Book;

Auther *tmp;

Auther* newAuther(char str[]) {
    Auther *new;
    new = (Auther*) malloc(sizeof(Auther));
    assert(new != NULL);
    strcpy(new->str, str);
    new->sell = 0;
    new->left = NULL;
    new->right = NULL;
    tmp = new;
    return new;
}

Book* newBook(char str[]) {
    Book *new;
    new = (Book*) malloc(sizeof(Book));
    assert(new != NULL);
    strcpy(new->str, str);
    new->left = NULL;
    new->right = NULL;
    new->au = tmp;
    return new;
}

Auther* insertAuther(Auther *x, char str[]) {
    if(x == NULL)
        return newAuther(str);
    int cmp = strcmp(str, x->str);
    if(cmp < 0)
        x->left = insertAuther(x->left, str);
    else if(cmp > 0)
        x->right = insertAuther(x->right, str);
    else
        tmp = x;
    return x;
}

Book* insertBook(Book *x, char str[]) {
    if(x == NULL)
        return newBook(str);
    int cmp = strcmp(str, x->str);
    if(cmp < 0)
        x->left = insertBook(x->left, str);
    else if(cmp > 0)
        x->right = insertBook(x->right, str);
    return x;
}

Book* searchBook(Book *x, char str[]) {
    if(x == NULL)
        return NULL;
    int cmp = strcmp(str, x->str);
    if(cmp < 0)
        return searchBook(x->left, str);
    else if(cmp > 0)
        return searchBook(x->right, str);
    return x;
}

int main() {
    int n, sell, max;
    char str[64];
    Auther *root_Auther = NULL, *max_Auther = NULL;
    Book  *root_Book = NULL;
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%s", str);
        root_Auther = insertAuther(root_Auther, str);
        scanf("%s", str);
        root_Book = insertBook(root_Book, str);        
    }
    max = -1;
    for(int i = 0; i < n; ++i) {
        scanf("%s %d", str, &sell);
        tmp = searchBook(root_Book, str)->au;
        tmp->sell += sell;
        if(tmp->sell > max || (tmp->sell == max && strcmp(tmp->str, max_Auther->str) < 0)) {
            max_Auther = tmp;
            max = tmp->sell;
        }
    }
    printf("%s %d", max_Auther->str, max);
    return 0;
}