int B_row_index_table[1024][1024] = {0}, B_rows_n[1024] = {0};

void matrix_multiplication(int N, int** ptrA, int M, int** ptrB, int S, int *result) {
	int B_row;
	for (int j = 0; j < M; ++j) {
		B_row = ptrB[1][j];
		B_row_index_table[B_row][B_rows_n[B_row]] = j;
		B_rows_n[B_row]++;
	}
	int j;
	for (int i = 0; i < N; ++i) {
		B_row = ptrA[2][i];
		for (int k = 0; k < B_rows_n[B_row]; ++k) {
			j = B_row_index_table[B_row][k];
			result[ptrA[1][i] * S + ptrB[2][j]] += ptrA[0][i] * ptrB[0][j];
		}
	}
}