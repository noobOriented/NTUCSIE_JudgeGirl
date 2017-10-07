#include <stdio.h>
#include "memory.h"
 
int main() {
    char command;
    int id, start, length;
    Memory myMemory[2];
    while(scanf("%c %d", &command, &id) != EOF) {
        switch(command) {
            case 'I':
                scanf("%d %d\n", &length);
                initMemory(myMemory + id, length);
                break;
            case 'P':
                printMemory(myMemory + id);
                break;
            case 'A':
                scanf("%d %d\n", &start, &length);
                allocateMemory(myMemory + id, start, length);
                break;
            case 'F':
                scanf("%d %d\n", &start, &length);
                freeMemory(myMemory + id, start, length);
                break;
        }
    }
    return 0;
}