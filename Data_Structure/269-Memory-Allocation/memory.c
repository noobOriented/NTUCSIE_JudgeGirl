#include <stdlib.h>
#include "memory.h"
 
Memory *newMemory(int start, int length, Memory *next){
    Memory *x = (Memory*) malloc(sizeof(Memory));
    x->start = start;
    x->length = length;
    x->next = next;
    return x;
}

void initMemory(Memory *memory, int length){
    memory->next = newMemory(0, length, NULL);
}

void printMemory(Memory *memory){
    //head
    Memory *x = memory->next;
    printf("==========\n");
    while(x){
        printf("start %d, length %d\n", x->start, x->length);
        x = x->next;
    }
}
 
void allocateMemory(Memory *memory, int start, int length){
    //head
    Memory *x = memory->next, *previous = NULL;
    //可能刪除memory, 紀錄previous以便重新串聯
    while(x){
        int left = x->start, right = x->start + x->length;
        //尋找可用的空位
        if(start >= left && start < right) {
            //完整宣告掉一塊memory, 刪除memory
            if(left == start && right == start + length) {
                if(previous)
                    previous->next = x->next;    
                else
                    memory->next = x->next;
                free(x);
                x = NULL;
            }//宣告的區塊緊貼現有memory的右邊
            else if(start + length == right) {
                x->length -= length;
            }//宣告的區塊緊貼現有memory的左邊
            else if(start == left) {
                x->length -= length;
                x->start += length;
            }//以上皆非，宣告在memory中間將其分割為二
            else{
                x->next = newMemory(start + length, right - (start + length), x->next);
                x->length = start - left;
            }
            return;
        }
        previous = x, x = x->next;
    }
}
 
void freeMemory(Memory *memory, int start, int length) {
    //head
    Memory *x = memory->next;
    if(x == NULL){
        memory->next = newMemory(start, length, NULL);
        return;
    }
    //釋放區域在head以前的位置
    if(start < x->start){
        //區塊緊鄰head，head往回延長
        if(start + length == x->start) {
            x->start -= length;
            x->length += length;
        }//宣告一塊新記憶體區域，成為新的head
        else {
            memory->next = newMemory(start, length, x);
        }
        return;
    }
    Memory *next = x->next;
    while(next){
        int left = x->start + x->length;
        int right = next->start;
        if(start >= left && start < right){
            //釋放掉兩記憶體中間的位置，將其連接起來
            if(left == start && right == start + length) {
                x->length += length + next->length;
                x->next = next->next;
                free(next);
                next = NULL;
            }//釋放的區域緊鄰前一塊記憶體，將其延長
            else if(left == start){
                x->length += length;
            }//釋放的區域緊鄰下一塊記憶體，將其往回延長
            else if(right == start + length){
                next->length += length;
                next->start = start;
            }//以上皆非，在兩記憶體間有了新記憶體
            else{
                x->next = newMemory(start, length, next);
            }
            return;
        }
        x = next;
        next = next->next;
    }
    //釋放區域在最後面
    if(start == x->start + x->length) 
        x->length += length;
    else
        x->next = newMemory(start, length, NULL);
}