#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    char data;
    struct node *next;
};

struct node *addN(struct node *head, struct node *newNode) {
    if (head == NULL) {
        head = newNode;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) { 
            temp = temp->next;
        }
        temp->next = newNode; 
    }
    newNode->next = NULL; 
    return head; 
}


void outN(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%c: %d\n", temp->data, (int)temp->data); 
        temp = temp->next;
    }
}


void freeList(struct node *head) {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


struct node* nhapDanhSach(int n) {
    struct node *head = NULL;
    for (int i = 0; i < n; i++) {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Khong the cap phat bo nho\n");
            freeList(head); 
            return NULL;
        }
        newNode->data = 'A' + rand() % 26; 
        head = addN(head, newNode); 
    }
    return head;
}

int main() {
    srand(time(NULL)); 
    int n;

    printf("Nhap so luong ky tu (n): ");
    scanf("%d", &n); 

    struct node *head = nhapDanhSach(n); 

    printf("Danh sach ky tu va ma ASCII:\n");
    outN(head); 
    freeList(head); 
    return 0;
}