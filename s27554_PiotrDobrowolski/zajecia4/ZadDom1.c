#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void dodaj(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = (*head);

    (*head) = new_node;
}

void usun(struct Node **head, int key) {
    struct Node* temp = *head, *prev;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void wyswietl(struct Node *node) {
    while (node != NULL) {
        printf(" %d \n", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;

    dodaj(&head, 2);
    dodaj(&head, 1);
    dodaj(&head, 3);
    dodaj(&head, 7);

    printf("lista jednostronnie wiazana: \n");
    wyswietl(head);

    usun(&head, 1);
    printf("Lista po usunieciu \"1\": \n");
    wyswietl(head);

    return 0;
}
