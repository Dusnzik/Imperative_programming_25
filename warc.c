#include <stdio.h>
#include <stdlib.h>
#define N 20

int cnt[2];
char filler = '_';

int rnd(const int min, const int max) {
    return (rand() % (max - min)) + min;
}

void print(char board[][N], const int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}

void start(char board[][N], const int n) {
    for (int i=0; i<n;i++) {
        for (int j=0; j<n;j++) {
            board[i][j]='_';
        }
    }
    for (int i=0; i<4;i++) {
        for (int j=(i%2); j<n; j+=2) {
            board[i][j]='1';
        }
    }
    for (int i=n-1;i>n-5;i--) {
        for (int j=(i%2);j<n;j+=2) {
            board[i][j]='2';
        }
    }
}

int move(char board[][N], const int i, const int j, const int n) {
    if (board[i][j]=='_')
        return 0;
    if (board[i][j]=='1') {
        if (i+1==n)
            return 0;
        if (j+1<n && board[i+1][j+1]=='_') {
            board[i][j]='_';
            board[i+1][j+1]='1';
            return 1;
        }
        if (j-1>=0 && board[i+1][j-1]=='_') {
            board[i][j]='_';
            board[i+1][j-1]='1';
            return 1;
        }
        return 0;
    }
    if (i-1<0)
        return 0;
    if (j+1<n && board[i-1][j+1]=='_') {
        board[i][j]='_';
        board[i-1][j+1]='2';
        return 1;
    }
    if (j-1>=0 && board[i-1][j-1]=='_') {
        board[i][j]='_';
        board[i-1][j-1]='2';
        return 1;
    }
    return 0;
}

int capture(char board[][N], const int i, const int j, const int n) {
    if (board[i][j]=='_')
        return 0;
    if (board[i][j]=='1') {
        if (i+2>=n)
            return 0;
        if (j+2<n && board[i+1][j+1]=='2' && board[i+2][j+2]=='_') {
            board[i][j]='_';
            board[i+1][j+1]='_';
            board[i+2][j+2]='1';
            cnt[1]--;
            return 1;
        }
        if (j-2>=0 && board[i+1][j-1]=='2' && board[i+2][j-2]=='_') {
            board[i][j]='_';
            board[i+1][j-1]='_';
            board[i+2][j-2]='1';
            cnt[1]--;
            return 1;
        }
        return 0;
    }
    if (i-2<0)
        return 0;
    if (j+2<n && board[i-1][j+1]=='1' && board[i-2][j+2]=='_') {
        board[i][j]='_';
        board[i-1][j+1]='_';
        board[i-2][j+2]='2';
        cnt[0]--;
        return 1;
    }
    if (j-2>=0 && board[i-1][j-1]=='1' && board[i-2][j-2]=='_') {
        board[i][j]='_';
        board[i-1][j-1]='_';
        board[i-2][j-2]='2';
        cnt[0]--;
        return 1;
    }
    return 0;
}


int main(void) {
    char board[N][N];
    int n, steps;
    unsigned seed;
    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    cnt[0] = cnt[1] = 2 * n;
    start(board, n);
    for (int i = 0; i < steps; i++) {
        int ix, iy;
        const char turn = (i % 2 == 0) ? '1' : '2';
        do {
            ix = rnd(0, n);
            iy = rnd(0, n);
        } while (board[ix][iy] != turn);
        if (!capture(board, ix, iy, n)) {
            move(board, ix, iy, n);
        }
    }
    print(board, n);
    printf("%d %d\n", cnt[0], cnt[1]);

    return 0;
}

