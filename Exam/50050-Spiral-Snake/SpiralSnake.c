void SpiralSnake(int N, int *snake, int *result) {
    const int di[] = {-1, -N, 1, N};
    int i = (N * N)/ 2, r = 0, k = 0;
    for(int j = 0; j < N * N; ++j) {
        result[i] = snake[j];
        i += di[r % 4];
        if(k >= r / 2){
            r++;
            k = 0;
        }else
            k++;
    }
}