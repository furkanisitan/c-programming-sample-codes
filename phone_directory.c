#include<stdio.h>
#include<string.h>

int addPerson(char *, char *);
int deletePerson(int);
void viewDirectory();
void changeFiles();
void menu();
void changeFiles();
void addPersonAction();
void changeFiles();
void changeFiles();
int isDecimal(const char *);

char *filename = "directory.txt";
FILE *file;

int main() {

    menu();
    int opr, id;

    while (1) {
        printf("\nselect the action you want to do: ");
        scanf("%d", &opr);

        switch (opr) {
            case 1:
                addPersonAction();
                break;
            case 2:
                printf("enter the id of the number to be deleted: ");
                scanf("%d", &id);
                puts(deletePerson(id) ? "was deleted!" : "invalid id!");
                break;
            case 3:
                viewDirectory();
                break;
            case 4:
                return 0;
            default:
                puts("incorrect action!");
                menu();
                break;
        }
    }

}

void addPersonAction() {
    char name[20], phone[15];
    printf("name: ");
    fflush(stdin);
    gets(name);
    printf("number: ");
    fflush(stdin);
    gets(phone);
    puts(addPerson(name, phone) ? "was recorded!" : "number is incorrect!");
}

int addPerson(char *name, char *number) {

    if (isDecimal(number)) {

        file = fopen(filename, "r");
        FILE *tempFile = fopen("temp.txt", "w");

        int line = 1, isAdded = 0;
        char str[50];

        while (fgets(str, 50, file) != NULL) {

            if (strcmp(name, str + 5) < 0 && !isAdded) {
                fprintf(tempFile, "%-5d%-20s%-15s\n", line++, name, number);
                isAdded = 1;
            }
            fprintf(tempFile, "%-5d%s", line++, str + 5);
        }
        if (!isAdded)
            fprintf(tempFile, "%-5d%-20s%-15s\n", line, name, number);

        fclose(file);
        fclose(tempFile);
        changeFiles();
        return 1;
    }
    return 0;
}

int deletePerson(int id) {

    file = fopen(filename, "r");
    int res = 0;

    if (file) {

        FILE *tempFile = fopen("temp.txt", "w");
        int line = 1;
        char str[50];

        while (fgets(str, 50, file) != NULL) {

            if (line == id) {
                res = 1;
                continue;
            }
            fprintf(tempFile, "%-5d%s", line++, str + 5);
        }
        fclose(file);
        fclose(tempFile);
        changeFiles();
    }
    return res;
}

void viewDirectory() {

    printf("\n%-5s%-20s%-15s\n\n", "id", "name", "number");
    file = fopen(filename, "r");
    if (file) {
        char str[50];
        while (fgets(str, 50, file) != NULL)
            printf("%s", str);
        fclose(file);
    }
}

int isDecimal(const char *str) {
    for (int i = 0; str[i] != 0; i++)
        if (!(48 <= str[i] && 57 >= str[i]))
            return 0;
    return 1;
}

void changeFiles() {
    remove(filename);
    rename("temp.txt", filename);
}

void menu() {
    printf("*        1. Add Person                *\n");
    printf("*        2. Delete Person             *\n");
    printf("*        3. View Directory            *\n");
    printf("*        4. Exit                      *\n");
    printf("--------------------------------------");
}