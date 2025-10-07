#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char word;
    char deskrip[100];
    bool end;
    struct node *next[256];
} node;

node *root;
node *curr;

int cek, count = 1, pilih;

struct node  *create(char kata) {
    node *temp = (node *)malloc(sizeof(node));
    for (int i = 0; i < 256; i++) {
        temp->next[i] = NULL;
    }
    temp->word = kata;
    return temp;
}

void insert(char str[], char desk[]) {
    int index;

    for (int i = 0; i < strlen(str); i++) {
        index = (int)str[i];
        if (curr->next[index] == NULL) {
            cek = 1;
            curr->next[index]=create(str[i]);
        }
        curr = curr->next[index];
    }
    strcpy(curr->deskrip, desk);
    curr->end = true;
}

void search(char str[]) {
    cek = 1;
    curr = root;
    int index;

    for (int i = 0; i < strlen(str); i++) {
        index = (int)str[i];
        if (curr->next[index] == NULL) {
            return;
        }
        curr = curr->next[index];
    }
    if(curr!=NULL&&curr->end==true){
    	cek=0;
    	return ;
	}
}

void print(char str[]) {
    if (count == 1 && pilih == 4) {
        printf("\nList of all slang words in the dictionary:\n");
    }
    printf("%d. %s\n", count, str);
    count++;

    return;
}

void display(node *curr, char str[], int idx) {
    if (curr->end == true) {
        str[idx] = '\0';
        print(str);
    }

    for (int i = 0; i < 256; i++) {
        if (curr->next[i] != NULL) {
            cek = 1;
            str[idx] = (char)i;
            display(curr->next[i], str, idx + 1);
        }
    }

    return;
}

void startprefix(char str[]) {
    int index = 0;
    node *temp = root;

    for (int i = 0; i < strlen(str); i++) {
        index = (int)str[i];

        if (!temp->next[index]) {
            printf("\nThere is no prefix \"%s\" in the dictionary\n", str);
            return;
        }

        temp = temp->next[index];
    }

    printf("Words starts with \"%s\":\n", str);
    char storage[100];
    count = 1;
    strcpy(storage, str);
    display(temp, storage, strlen(str));
    puts("");

    return;
}

int main() {
	root=create('*');
    char arr[100]={}, desc[100]={};
    int dec;

    do {
        printf("1. Release a new slang word\n2. Search a slang word\n3. View all slang words starting with a certain prefix word\n4. View all slang words\n5. Exit\n\n");
        printf("Input pilih: ");
        scanf("%d", &pilih);
        getchar();
        if (pilih == 1) {
            do {
                printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
                scanf("%[^\n]", arr);
                getchar();
                dec = strlen(arr);
                for (int i = 0; i < dec; i++) {
                    if (arr[i] == ' ') {
                        dec = 1;
                    }
                }
            } while (dec <2);
            dec = 0;
            do {
                printf("Input a new slang word description [Must be more than 2 words]: ");
                scanf("%[^\n]", desc);
                getchar();
                for (int i = 0; i < strlen(desc); i++) {
                    if (desc[i] == ' ') {
                        dec += 1;
                    }
                }
            } while (dec < 2);
            curr = root;
            cek=0;
            insert(arr, desc);
            if (cek == 0) {
                printf("\nSuccessfully updated a slang word.\n");
            } else {
                printf("\nSuccessfully released new slang word.\n");
            }
            printf("Press enter to continue...");
            getchar();
            system("cls");
        }

        else if (pilih == 2) {
            cek = 0;
            do {
                printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
                scanf("%[^\n]", arr);
                getchar();
                dec = strlen(arr);

                for (int i = 0; i < dec; i++) {
                    if (arr[i] == ' ') {
                        dec = 1;
                    }
                }
            } while (dec == 1);

            curr = root;
            search(arr);
            if (cek == 1) {
                printf("\nThere is no word \"%s\" in the dictionary.\n", arr);
            } else {
                printf("\nSlang word  : %s\n", arr);
                printf("Description : %s\n\n", curr->deskrip);
            }
            printf("Press enter to continue...");
            getchar();
            system("cls");
        } else if (pilih == 3) {
            printf("\nInput a prefix to be searched: ");
            scanf("%s", arr);
            getchar();

            cek = 0;
            curr = root;
            startprefix(arr);

            printf("Press enter to continue...");
            getchar();
            system("cls");
        } else if (pilih == 4) {
            cek = 0;
            count = 1;
            curr = root;
            char storage[100];
            display(curr, storage, 0);
            if (cek == 0) {
                printf("\nThere is no slang word yet in the dictionary.\n");
                printf("Press enter to continue...");
            } else {
                printf("\nPress enter to continue...");
            }
            getchar();
            system("cls");
        }

    } while (pilih != 5);

    printf("Thank you... Have a nice day :)\n");

 

    return 0;
}

