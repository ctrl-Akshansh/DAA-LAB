#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20

void printSolution(int board[MAX_N][MAX_N], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

bool isSafe(int board[MAX_N][MAX_N], int row, int col, int N) {
    int i, j;

    for (i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    for (i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }

    return true;
}

bool solveNQueens(int board[MAX_N][MAX_N], int col, int N) {
    if (col >= N) {
        return true;
    }

    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;

            if (solveNQueens(board, col + 1, N)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

int main(void) {
    int N = 4;
    int board[MAX_N][MAX_N] = {0};

    printf("Solving %d-Queens Problem:\n\n", N);

    if (solveNQueens(board, 0, N)) {
        printSolution(board, N);
    } else {
        printf("No solution exists for N = %d\n", N);
    }

    return 0;
}
