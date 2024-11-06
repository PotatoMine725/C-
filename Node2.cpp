#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *addN(struct node *head, struct node *data) {
    if (head == NULL) {
        head = data;
        head->next = head; 
    } else {
        struct node *tg = head;
        while (tg->next != head) { 
            tg = tg->next;
        }
        tg->next = data; 
        data->next = head; 
    }
    return head;
}

void outN(struct node *head) {
    if (head == NULL) return; 
    struct node *tg = head;
    do {
        printf("%d ", tg->data);
        tg = tg->next;
    } while (tg != head); 
    printf("\n");
}

void inN(struct node **head) {
    struct node *p;
    char choice;

    do {
        p = (struct node *)malloc(sizeof(struct node));
        if (p == NULL) {
            printf("Khong the cap phat\n");
            return;
        }
        printf("Nhap so: ");
        scanf("%d", &p->data);
        p->next = NULL; 

        *head = addN(*head, p);

        printf("Muon nhap tiep khong (y/n): ");
        scanf(" %c", &choice); 

    } while (choice == 'y');
}

int main() {
    struct node *head = NULL;
    inN(&head); 
    printf("Day da nhap : ");
    outN(head);

    if (head != NULL) {
        struct node *current = head;
        struct node *next;
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }

    return 0;
}