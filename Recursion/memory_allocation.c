#include <stdlib.h>
#include <assert.h>
#include "memory.h"
 
MemoryNode *newMemoryNode(int start, int length, MemoryNode *next){
    MemoryNode *current = (MemoryNode*)malloc(sizeof(MemoryNode));
    assert(current != NULL);
    current->start = start;
    current->length = length;
    current->next = next;
    return current;
}
 
void initMemory(Memory *memory, int length){
    memory->head = newMemoryNode(0, length, NULL);
}
void printMemory(Memory *memory){
    MemoryNode *current = memory->head;
    printf("==========\n");
    while(current != NULL){
        printf("start %d, length %d\n", current->start, current->length);
        current = current->next;
    }
}
 
void allocateMemory(Memory *memory, int start, int length){
    //可能刪除memory, 紀錄previous以便重新串聯
    MemoryNode *current = memory->head, *previous = NULL;
    while(current != NULL){
        int left = current->start;
        int right = current->start + current->length;
        if(start >= left && start < right) {
            //完整宣告掉一塊memory, 刪除memory
            if(left == start && right == start + length) {
                if(previous == NULL)
                    memory->head = current->next;
                else
                    previous->next = current->next;
                free(current);
                current = NULL;
            }//宣告的區塊緊貼現有memory的右邊
            else if(start + length == right) {
                current->length -= length;
            }//宣告的區塊緊貼現有memory的左邊
            else if(start == left) {
                current->length -= length;
                current->start += length;
            }//以上皆非，宣告在memory中間將其分割為二
            else{
                current->next = newMemoryNode(start + length, right - (start + length), current->next);
                current->length = start - left;
            }
            return;
        }
        previous = current;
        current = current->next;
    }
}
 
void freeMemory(Memory *memory, int start, int length){
    MemoryNode *current = memory->head;
    if(current == NULL){
        memory->head = newMemoryNode(start, length, NULL);
        return;
    }
    //釋放區域在head以前的位置
    if(start < current->start){
        //區塊緊鄰head，head往回延長
        if(start + length == current->start) {
            current->start -= length;
            current->length += length;
        }//宣告一塊新記憶體區域，成為新的head
        else {
            memory->head = newMemoryNode(start, length, current);
        }
        return;
    }
    while(current->next != NULL){
        int left = current->start + current->length;
        int right = current->next->start;
        if(start >= left && start < right){
            //釋放掉兩記憶體中間的位置，將其連接起來
            if(left == start && right == start + length) {
                MemoryNode *temp = current->next;
                current->length += length + current->next->length;
                current->next = current->next->next;
                free(temp);
                temp = NULL;
            }//釋放的區域緊鄰前一塊記憶體，將其延長
            else if(left == start){
                current->length += length;
            }//釋放的區域緊鄰下一塊記憶體，將其往回延長
            else if(right == start + length){
                current->next->length += length;
                current->next->start = start;
            }//以上皆非，在兩記憶體間有了新記憶體
            else{
                current->next = newMemoryNode(start, length, current->next);
            }
            return;
        }
        current = current->next;
    }
    //釋放區域在最後面
    if(start == current->start + current->length) 
        current->length += length;
    else
        current->next = newMemoryNode(start, length, NULL);
}