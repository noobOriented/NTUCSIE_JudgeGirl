#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
/* 
   出現過的字母表（依出現先後順序）：alphabet
   相異字母個數： n_alphabet
   各字母對應數字： digit_alphabet
 
   input內容：input
   input各位置對應到字母表中的第幾個字：pointer                (或許這兩個可以只用一個陣列表示)
 
*/
int n_alphabet = 0;
int digit_alphabet[20], pointer[3][10];
char alphabet[20], input[3][10];
 
//依序讀取 第id行的input內的字元，建立字母表
void build_dictionary(int id){
    int repeat, L = strlen(input[id]);
    for(int i = 0; i < L; ++i){
        //檢查是否為字母
        if(!isalpha(input[id][i]))
            continue;
        repeat = 0;
        //與字母表中的所有字母對照，檢查是否已出現過
        for(int j = 0; j < n_alphabet && !repeat; ++j){
            //若出現過，pointer紀錄此位置為表中的第幾個字母
            if(input[id][i] == alphabet[j]){
                repeat = 1;
                pointer[id][i] = j;
            }
        }
        //未出現過，將新字母紀錄至表中，相異字母個數增加
        if(!repeat){
            alphabet[n_alphabet] = input[id][i];
            pointer[id][i] = n_alphabet;
            n_alphabet++;
        }
    }
}
 
// 第id行 input 對應的數字
int decode_alphabet(int id) {
    int L = strlen(input[id]), sum = 0;
    for(int i = 0; i < L; ++i){
        // 十進位左移
        sum *= 10;
        if(isalpha(input[id][i]))
            // 查找現在這個字母是字母表中第幾個，並填上digit
            sum += digit_alphabet[pointer[id][i]];
        else
            sum += input[id][i] - '0';
    }
    return sum;
}
 
// 對字母表內的數字進行遞迴窮舉
int try_digit(int i_alphabet) {
    //所有字母的digit皆填完，驗證等式是否正確
    if(i_alphabet == n_alphabet) {
        int A = decode_alphabet(0), B = decode_alphabet(1), C = decode_alphabet(2);
        if(A * B == C){
            printf("%d x %d = %d\n", A, B, C);
            return 1;
        }
        return 0;
    }
    //對於第i_alphabet個字母，窮舉所有digit的可能，並繼續填下個字母（類似八皇后）
    for(int j = 1; j < 10; ++j){
        digit_alphabet[i_alphabet] = j;
        if(try_digit(i_alphabet + 1))
            return 1;
    }
}
 
 
int main(){
    for(int id = 0; id < 3; ++id){
        scanf("%s", input[id]);
        build_dictionary(id);
    }
    try_digit(0);
}