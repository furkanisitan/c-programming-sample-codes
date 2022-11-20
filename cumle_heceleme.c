#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/* TÜRKÇE HECELEME KURALLARI
 * iki ünlü arasındaki ünsüz, kendinden sonraki ünlüyle hece kurar: a-ra-ba, bi-çi-mi-ne
 * yan yana gelen iki ünsüzden ilki kendinden önceki ünlüyle,
ikincisi kendinden sonraki ünlüyle hece kurar: al-dı, bir-lik, sev-mek vb.
 * yan yana gelen üç ünsüz harften ilk ikisi kendinden önceki ünlüyle,
üçüncüsü kendinden sonraki ünlüyle hece kurar: alt-lık, Türk-çe
 * kaynak: https://www.tdk.gov.tr/icerik/yazim-kurallari/hece-yapisi-ve-satir-sonunda-kelimelerin-bolunmesi/
 * */

const char vowels[] = "AaEeIıİiOoÖöUuÜü";

char *spellSentence(char *);
char *spellWord(char *);
int *getVowelIndexes(char *);
int isVowel(char);

int main() {

    setlocale(LC_ALL, "Turkish");

    puts(spellSentence("furkan    isitan   c   programlama"));
    return 0;
}

char *spellSentence(char *sentence) {
    char *output = malloc(strlen(sentence) * 2 * sizeof(char));
    output[0] = '\0';

    // boşluğa göre split
    char *word = strtok(strdup(sentence), " ");
    while (word != NULL) {
        strcat(output,spellWord(word));
        strcat(output, " ");
        word = strtok(NULL, " ");
    }

    return output;
}

char *spellWord(char *word) {

    int wordLength = strlen(word);
    char *output = (char *) malloc(wordLength * 2 * sizeof(char));
    int *vowelIndexes = getVowelIndexes(word);

    // hiç ünlü yoksa aynı kopyasını dön
    if (vowelIndexes[0] == -1) {
        return strcpy(&output[0], &word[0]);
    }

    int j = 0, consonantAmount;

    // ilk ünlüden önceki ünsüzler
    for (int i = 0; i < vowelIndexes[0]; ++i) {
        output[j++] = word[i];
    }

    for (int i = 0; vowelIndexes[i] != -1; i++) {

        // son ünlüye gelinmişse kalan tüm karakterleri kopyala ve döngüyü bitir.
        if (vowelIndexes[i + 1] == -1) {
            strcpy(&output[j], &word[vowelIndexes[i]]);
            break;
        }

        // iki ünlü arasındaki ünsüz sayısı
        consonantAmount = vowelIndexes[i + 1] - vowelIndexes[i] - 1;

        // sesli harfi ekle
        output[j++] = word[vowelIndexes[i]];

        // iki ünlü arası 2 ünsüz => ünsüz1 + '-'
        // iki ünlü arası 3 ünsüz => ünsüz1 + ünsüz2 '-'
        for (int k = 1; k < consonantAmount; ++k) {
            output[j++] = word[vowelIndexes[i] + k];
        }

        // heceyi ayır
        output[j++] = '-';

        // iki ünlü peş peşe gelmiyorsa sonra gelen ünlüden önceki ünsüzü ekle
        if (consonantAmount > 0) {
            output[j++] = word[vowelIndexes[i + 1] - 1];
        }
    }
    return output;
}

int *getVowelIndexes(char *word) {

    int wordLength = strlen(word);
    int *indexes = malloc(wordLength * sizeof(int));
    int j = 0;

    for (int i = 0; i < wordLength; i++) {
        if (isVowel(word[i])) {
            indexes[j++] = i;
        }
    }
    indexes[j] = -1;
    return indexes;
}

int isVowel(char ch) {
    return strchr(vowels, ch) != NULL;
}
