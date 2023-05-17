#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void wstawNaPoczatku(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = (*head);
    new_node->prev = NULL;

    if ((*head) != NULL) {
        (*head)->prev = new_node;
    }

    (*head) = new_node;
}

void usun(struct Node** head, int key) {
    struct Node* temp = *head;

    while(temp != NULL) {
        if(temp->data == key) {
            if(temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            if(temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if(temp == *head) {
                *head = temp->next;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

void wyswietl(struct Node *node) {
    while (node != NULL) {
        printf("%d \n", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;

    wstawNaPoczatku(&head, 2);
    wstawNaPoczatku(&head, 1);
    wstawNaPoczatku(&head, 3);
    wstawNaPoczatku(&head, 7);

    printf("Lista dwustronnie wiazana: \n");
    wyswietl(head);

    usun(&head, 1);
    printf("\nLista po usunieciu \"1\": \n");
    wyswietl(head);

    return 0;
}
