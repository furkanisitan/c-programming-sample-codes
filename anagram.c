#include<stdio.h>
#include<string.h>
#include<ctype.h>

int anagram(const char *, const char *);

int main() {

    printf("%d\n", anagram("SeLam", "elmAs"));
    printf("%d\n", anagram("SeLam", "SeLmE"));

    return 0;
}


// anagram ise 1, değilse 0 döner
int anagram(const char *str1, const char *str2) {

    // str2'yi temp'e kopyala
    char temp[strlen(str2)];
    strcpy(temp, str2);

    // Uzunluklar eşit değilse anagram deildir.
    if (strlen(str1) == strlen(temp)) {

        for (int i = 0; i < strlen(str1); i++) {

            for (int j = 0; j < strlen(temp); j++) {

                // eşitlik varsa temp'den j indisini sil
                if (tolower(str1[i]) == tolower(temp[j])) {
                    strcpy(&temp[j], &temp[j + 1]);
                    break;
                }
            }
        }
    }
    // !strlen(temp) => Eğer temp'in uzunluğu sıfır ise tüm harfler eşleşmiş demektir. Yani anagramdır.
    // strlen(str2)  => str2 boş ise anagramlık aranmaz, 0 döner.
    return !strlen(temp) && strlen(str2);
}