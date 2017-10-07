#include "RMQ.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
typedef struct SparseTable {
    int32_t **table;
} SparseTable;

unsigned mylog2(unsigned x) {
    register unsigned int r = 0;
       if(x & 0xFFFF0000) x >>= 16, r |= 16;
       if(x & 0x0000FF00) x >>= 8 , r |= 8 ;
       if(x & 0x000000F0) x >>= 4 , r |= 4 ;
       if(x & 0x0000000C) x >>= 2 , r |= 2 ;
       if(x & 0x00000002) x >>= 1 , r |= 1 ;
    return r;
}

static inline int32_t max(int32_t x, int32_t y) {
    return x > y ? x : y;
}

void* preprocessing(int N, int32_t A[]) {
    SparseTable *tool = (SparseTable*) malloc(sizeof(SparseTable));
    int loglength = mylog2(N);
    int32_t **table = (int32_t **) malloc(sizeof(int32_t*) * (loglength + 1));
    table[0] = (int32_t *) malloc(sizeof(int32_t) * N);
    memcpy(table[0], A, sizeof(int32_t) * N);
    for(int i = 0; i < loglength; ++i) {
    	table[i + 1] = (int32_t *) malloc(sizeof(int32_t) * (N + 1 - (2 << i)));
    	for(int j = 0; j < N + 1 - (2 << i); ++j)
    		table[i + 1][j] = max(table[i][j], table[i][j + (1 << i)]);
    }
    tool->table = table;
    return tool;
}

void offline_query(void *tool, int M, int32_t Q[][2], int32_t R[]) {
	int32_t l, r, loglength;
    int32_t **table = ((SparseTable*) tool)->table;
    for (int i = 0; i < M; i++) {
        l = Q[i][0], r = Q[i][1];
        if(r == l)
        	R[i] = table[0][l];
        else{
	        loglength = mylog2(r - l);
	        R[i] = max(table[loglength][l], table[loglength][r + 1 - (1 << loglength)]);
        }
    }
}

void destroy(void *tool) {
    SparseTable *t = (SparseTable*) tool;
    free(t->table);
    free(t);
}