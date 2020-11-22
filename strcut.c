#include<stdio.h>
#include<stdlib.h>

char *strcut(char *str, int pos, int length) {

    if (pos < 0 || length < 0)
        return NULL;

    char *output = malloc(length * sizeof(char));
    char *p = output;
    for (str += pos; p - output < length && *str; p++, str++)
        *p = *str;
    *p = '\0';
    return output;
}

int main() {

    char *text = "merhaba dunya";
    puts(strcut(text, 4, 6));
}