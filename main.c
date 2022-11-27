#include <stdio.h>
#include <stdlib.h>

void showMenu();

void createNewNote();

void openNote();

void deleteNote();

int viewAllNotes();

void adjustNumbering();

void freeAll();

void delay();

typedef struct note {
    int count;
    char title[50];
    char content[200];
    struct note *next;
} note;

note *head = NULL;

int main() {
    while (1) {
        int choice;

        showMenu();
        do {
            printf("Choice --> ");
            scanf(" %d", &choice);
        } while (choice < 1 || choice > 5);

        switch (choice) {
            case 1:
                createNewNote();
                break;
            case 2:
                openNote();
                delay();
                break;
            case 3:
                deleteNote();
                break;
            case 4:
                viewAllNotes();
                delay();
                break;
            default:
                freeAll();
                return 0;
        }
    }
}

void showMenu() {
    printf("\nWhat do you want to do? (Notes App)\n");
    printf("======================================\n");
    printf("[1] Create New Note\n");
    printf("[2] Open Note\n");
    printf("[3] Delete Note\n");
    printf("[4] View All Notes\n");
    printf("[5] Exit\n");
    printf("======================================\n");
}

int viewAllNotes() {
    note *temp = head;

    if (temp == NULL) {
        printf("No notes yet.\n");
        return 1;
    } else {
        printf("Notes List:\n\n");
        while (temp != NULL) {
            printf("[%d]\n", temp->count);
            printf("Title: %s\n", temp->title);
            printf("Content: %s\n\n", temp->content);
            temp = temp->next;
        }
    }
    return 0;
}

void createNewNote() {
    note *temp = NULL;

    temp = malloc(sizeof(note));
    printf("Title: ");
    fflush(stdin);
    scanf("%[^\n]s", temp->title);
    printf("Content: ");
    fflush(stdin);
    scanf("%[^\n]s", temp->content);
    temp->next = NULL;

    if (head == NULL) {
        temp->count = 1;
        head = temp;
    } else {
        note *find = head;
        while (find->next != NULL) {
            find = find->next;
        }
        temp->count = find->count + 1;
        find->next = temp;
    }
    printf("======================================\n");
    printf("Saved!\n");
    printf("======================================\n");
}

void openNote() {
    int count, found = 0;

    if (viewAllNotes() == 1) {
        return;
    }

    do {
        printf("Choose note to open: ");
        scanf(" %d", &count);

        for (note *temp = head; temp != NULL; temp = temp->next) {
            if (temp->count == count) {
                printf("\nTitle: %s", temp->title);
                printf("\nContent: %s\n", temp->content);
                found = 1;
            }
        }
    } while (found == 0);
}

void deleteNote() {
    int count, found = 0;

    if (viewAllNotes() == 1) {
        return;
    }

    do {
        printf("Choose note to delete: ");
        scanf(" %d", &count);

        note *temp = head;
        if (temp->count == count) {

            if (temp->next != NULL) {
                head = temp->next;
            } else {
                head = NULL;
            }
            free(temp);
            found = 1;

        } else {
            while (temp->next != NULL) {

                note *del = temp->next;
                if (del->count == count) {

                    if (del->next != NULL) {
                        temp->next = del->next;
                    } else {
                        temp->next = NULL;
                    }
                    free(del);
                    found = 1;

                } else {
                    temp = temp->next;
                }
            }
        }
    } while (found == 0);

    adjustNumbering();
    printf("======================================\n");
    printf("Deleted!\n");
    printf("======================================\n");
}

void adjustNumbering() {
    int count = 1;
    for (note *temp = head; temp != NULL; temp = temp->next) {
        temp->count = count;
        count++;
    }
}

void freeAll() {
    for (note *temp = head, *save; temp != NULL; temp = save) {
        save = temp->next;
        free(temp);
    }
}

void delay() {
    printf("\n[END]\nPress any key to continue... ");
    fflush(stdin);
    getchar();
}