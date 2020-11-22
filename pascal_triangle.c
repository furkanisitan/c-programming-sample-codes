#include<stdio.h>

void pascal(int);
int factorial(int);
int combination(int, int);

int main() {

    int line;
    printf("Satir sayisini giriniz: ");
    scanf("%d", &line);
    pascal(line);
    return 0;
}

void pascal(int line){

    int n = 0;
    puts("");

    while (n < line) {

        // satır başı boşlukları yazdırılır
        for (int i = 1; i < line - n; i++)
            printf(" ");

        // değerler yazdırılır.
        for (int r = 0; r <= n; r++)
            printf("%d ", combination(n, r));

        puts("");
        n++;
    }
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int combination(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}