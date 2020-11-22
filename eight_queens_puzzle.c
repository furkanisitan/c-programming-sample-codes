#include <stdio.h>

#define QUEENS 8
#define int unsigned

int num = 0;
int board[QUEENS];

FILE *file;

void place(int);
void printSolution();
int isPlace(int);

signed main() {

    // ilk sıradan başla
    place(0);

    printf("8 queens problem solved....\n");
    printf("to see the solution, check the file puzzle.txt.");
    return 0;
}


/*
 * verilen satır için veziri, önceki satırlardaki vezirlerin konumuna göre uygun bir pozisyona yerleştirir.
 * ardından bir sonrali satır için kendini tekrar çağırır.
 * */
void place(int row) {

    // Son sıraya gelindiğinde çözümü yaz.
    if (row == QUEENS)
        printSolution();
    else

        // board[row] = 1 => 00000001
        // 1 << VIZIERS => 10000000
        // en sağdan başla sola doğru deneyerek git
        for (board[row] = 1; board[row] < (1 << QUEENS); board[row] <<= 1)
            // uygun pozisyonda bir alt satıra geç
            if (isPlace(row))
                place(row + 1);
}

// önceki satırlar için aynı sütun ya da çaprazda vezir varsa 0 yoksa 1 döner
int isPlace(int row) {
    int r;

    for (r = 0; r < row; r++)
        if ((board[row] == board[r]) ||                 // aynı sütun
            (board[row] == (board[r] << (row - r))) ||  // sağ çapraz
            (board[row] == (board[r] >> (row - r))))    // sol çapraz
            return 0;
    return 1;
}

void printSolution() {

    int t, r;
    file = fopen("puzzle.txt", "a");
    if (file) {
        fprintf(file, "\n\n\tSOLUTION %u\n\n", ++num);
        for (r = 0; r < QUEENS; r++) {
            for (t = (1 << (QUEENS - 1)); t > 0; t >>= 1)
                fprintf(file, " %c", board[r] == t ? 'V' : '.');
            fprintf(file, "\n");
        }
    } else
        perror("the file could not be opened!");
}
