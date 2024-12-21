#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LANG_SIZE 10
#define WORD_SIZE 15

typedef struct Word {
    char **defenition;
    struct Word *next;
} Word;

typedef struct {
    char **languages;
    int num_langu;
    Word *word_list;
} dictionary;

dictionary *dictionaries = NULL;
int amount_dict = 0;

void new_dictionary() {
    amount_dict += 1;
    dictionaries = realloc(dictionaries, sizeof(dictionary) * amount_dict);
    if (dictionaries == NULL) {
        printf("Failed to allocate memory :(\n");
        return;
    }

    printf("Enter the amount of languages in this dictionary:\n");
    if (scanf("%d", &dictionaries[amount_dict - 1].num_langu) != 1 || dictionaries[amount_dict - 1].num_langu <= 0) {
        printf("Invalid input for number of languages.\n");
        return;
    }

    dictionaries[amount_dict - 1].languages = malloc(sizeof(char *) * dictionaries[amount_dict - 1].num_langu);
    if (dictionaries[amount_dict - 1].languages == NULL) {
        printf("Failed to allocate memory for languages :(\n");
        return;
    }
    dictionaries[amount_dict - 1].word_list = NULL;

    for (int i = 0; i < dictionaries[amount_dict - 1].num_langu; i++) {
        dictionaries[amount_dict - 1].languages[i] = malloc(LANG_SIZE * sizeof(char));
        if (dictionaries[amount_dict - 1].languages[i] == NULL) {
            printf("Failed to allocate memory for language %d :(\n", i + 1);
            return;
        }
        printf("Enter the %d language:\n", i + 1);
        if (scanf("%s", dictionaries[amount_dict - 1].languages[i]) != 1) {
            printf("Failed to read language name.\n");
            return;
        }
    }
    printf("Great! You created a new dictionary!\n");
}

void add_word_dict() {
    int dict_num = 0;
    printf("Enter the dictionary you want to add word to: 1 - %d\n", amount_dict);
    if (scanf("%d", &dict_num) != 1 || dict_num < 1 || dict_num > amount_dict) {
        printf("Invalid dictionary number.\n");
        return;
    }

    Word *new_word = malloc(sizeof(Word));
    if (new_word == NULL) {
        printf("Failed to allocate memory for new word :(\n");
        return;
    }

    new_word->defenition = malloc(sizeof(char *) * dictionaries[dict_num - 1].num_langu);
    if (new_word->defenition == NULL) {
        printf("Failed to allocate memory for definitions :(\n");
        free(new_word);
        return;
    }
    new_word->next = NULL;

    for (int i = 0; i < dictionaries[dict_num - 1].num_langu; i++) {
        new_word->defenition[i] = malloc(sizeof(char) * WORD_SIZE);
        if (new_word->defenition[i] == NULL) {
            printf("Failed to allocate memory for definition %d :(\n", i + 1);
            free(new_word->defenition);
            free(new_word);
            return;
        }
        printf("Enter the meaning in %s\n", dictionaries[dict_num - 1].languages[i]);
        if (scanf("%s", new_word->defenition[i]) != 1) {
            printf("Failed to read definition.\n");
            free(new_word->defenition);
            free(new_word);
            return;
        }
    }

    Word *head = dictionaries[dict_num - 1].word_list;
    if (head == NULL) {
        dictionaries[dict_num - 1].word_list = new_word;
    } else {
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = new_word;
    }

    printf("Great! We added the word to the dictionary!\n");
}

int print_word(int dict_num) {
    Word *current = dictionaries[dict_num - 1].word_list;
    int i = 0;
    int choice = 0;

    if (current == NULL) {
        printf("There are no words in this dictionary :(\n");
        return -1;
    }

    printf("Which word do you want to delete?\n");
    while (current != NULL) {
        printf("%d)", i + 1);
        for (int b = 0; b < dictionaries[dict_num - 1].num_langu; b++) {
            printf("%s    ", current->defenition[b]);
        }
        printf("\n");
        current = current->next;
        i++;
    }

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > i) {
        printf("Invalid choice.\n");
        return -1;
    }
    return choice;
}

void delete_word_dictionary() {
    int dict_num = 0;
    printf("Enter the dictionary you want to remove word from: 1 - %d\n", amount_dict);
    if (scanf("%d", &dict_num) != 1 || dict_num < 1 || dict_num > amount_dict) {
        printf("Invalid dictionary number.\n");
        return;
    }

    int choice = print_word(dict_num);
    if (choice == -1) return;

    Word *current = dictionaries[dict_num - 1].word_list;
    Word *prev = NULL;
    for (int i = 1; i <= choice; i++) {
        if (i == choice) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                dictionaries[dict_num - 1].word_list = current->next;
            }
            free(current->defenition);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    printf("Word deleted from dictionary!\n");
}

void find_word_dictionary() {
    int dict_num = 0;
    printf("Enter the dictionary you want to search a word in: 1 - %d\n", amount_dict);
    if (scanf("%d", &dict_num) != 1 || dict_num < 1 || dict_num > amount_dict) {
        printf("Invalid dictionary number.\n");
        return;
    }

    char Word_find[WORD_SIZE] = {0};
    printf("Enter the word you are searching for :\n");
    if (scanf("%s", Word_find) != 1) {
        printf("Failed to read search word.\n");
        return;
    }

    Word *current = dictionaries[dict_num - 1].word_list;
    while (current != NULL) {
        for (int i = 0; i < dictionaries[dict_num - 1].num_langu; i++) {
            if (strcmp(current->defenition[i], Word_find) == 0) {
                printf("The word '%s' is in this dictionary :)\n", Word_find);
                for (int b = 0; b < dictionaries[dict_num - 1].num_langu; b++) {
                    printf("%s       ", current->defenition[b]);
                }
                printf("\n");
                return;
            }
        }
        current = current->next;
    }

    printf("The word '%s' is not in this dictionary :(\n", Word_find);
}

void delete_dictionary() {
    int dict_num = 0;
    printf("Enter the dictionary you want to delete: 1 - %d\n", amount_dict);
    if (scanf("%d", &dict_num) != 1 || dict_num < 1 || dict_num > amount_dict) {
        printf("Invalid dictionary number.\n");
        return;
    }

    Word *current = dictionaries[dict_num - 1].word_list;
    Word *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->defenition);
        free(temp);
    }

    free(dictionaries[dict_num - 1].languages);
    dictionaries[dict_num - 1].languages = NULL;
    dictionaries[dict_num - 1].word_list = NULL;

    printf("Dictionary deleted!\n");
}

void print_dict() {
    int dict_num = 0;
    printf("Enter the dictionary you want to print: 1 - %d\n", amount_dict);
    if (scanf("%d", &dict_num) != 1 || dict_num < 1 || dict_num > amount_dict) {
        printf("Invalid dictionary number.\n");
        return;
    }

    Word *current = dictionaries[dict_num - 1].word_list;
    int i = 0;
    if (current == NULL) {
        printf("There are no words in this dictionary :(\n");
        return;  // return early if no words exist
    }

    // Print words from the linked list
    while (current != NULL) {
        printf("%d)", i + 1);
        for (int b = 0; b < dictionaries[dict_num - 1].num_langu; b++) {
            printf("%s    ", current->defenition[b]);
        }
        printf("\n");
        current = current->next;
        i++;
    }
}


void exit_program() {
    for (int i = 0; i < amount_dict; i++) {
        Word *current = dictionaries[i].word_list;
        Word *temp;
        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp->defenition);
            free(temp);
        }
        free(dictionaries[i].languages);
    }

    free(dictionaries);
    printf("Have a good day and thank you for using our Dictionary program :)\n");
    exit(0);
}

void menu() {
    int choice = 0;
    while (1) {
        printf("Welcome to the dictionaries manager!\nChoose an option:\n");
        printf("1) Create a new dictionary\n");
        printf("2) Add a word to a dictionary\n");
        printf("3) Delete a word from a dictionary\n");
        printf("4) Find a word in a dictionary\n");
        printf("5) Delete a dictionary\n");
        printf("6) Print dictionary\n");
        printf("7) Exit\n");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            continue;
        }

        switch (choice) {
            case 1:
                new_dictionary();
                break;
            case 2:
                add_word_dict();
                break;
            case 3:
                delete_word_dictionary();
                break;
            case 4:
                find_word_dictionary();
                break;
            case 5:
                delete_dictionary();
                break;
            case 6:
                print_dict();
                break;
            case 7:
                exit_program();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

int main(void) {
    menu();
    return 0;
}
