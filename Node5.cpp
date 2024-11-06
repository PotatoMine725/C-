#include <stdio.h>
#include <stdlib.h>

struct NODE {
    int num;
    struct NODE *next;
};

struct NODE *themN(struct NODE *head, struct NODE *num) {
    if (head == NULL) 
        head = num; 
    else {
        struct NODE *tg = head;
        while (tg->next != NULL) 
            tg = tg->next;
        tg->next = num; 
    }
    num->next = NULL; 
    return head;
}

struct NODE *xoaN(struct NODE **head) {
    if (*head == NULL) {
        return NULL; 
    }
    struct NODE *temp = *head; 
    *head = (*head)->next; 
    return temp;
}

void xuat(struct NODE *head) {
    struct NODE *tg = head;
    while (tg != NULL) {
        printf("%d ", tg->num);
        tg = tg->next;
    }
    printf("\n");
}

void xoamem(struct NODE *head) {
    struct NODE *tg;
    while (head != NULL) {
        tg = head;
        head = head->next;
        free(tg);
    }
}

struct NODE *nhap() {
    struct NODE *Head = NULL, *p;
    int count;

    printf("Nhap so luong phan tu: ");
    scanf("%d", &count);

    for (int i = 1; i <= count; i++) {
        p = (struct NODE *)malloc(sizeof(struct NODE));
        if (p == NULL) {
            printf("Khong the cap bo nho\n");
            return NULL;
        }
        printf("Nhap so thu %d: ", i);
        scanf("%d", &p->num);
        Head = themN(Head, p); 
    }

    return Head; 
}

// void xuatFIFO(struct NODE **head) {
//     printf("FIFO:\n");
//     struct NODE *removedNode;
//     while ((removedNode = xoaN(head)) != NULL) {
//         printf("%d ", removedNode->num);
//         free(removedNode); // Giải phóng bộ nhớ nút đã lấy
//     }
//     printf("\n");
// }

int main() {
    struct NODE *Head = nhap(); 
    printf("Day da nhap: ");
    xuat(Head); 
   //xuatFIFO(&Head); // Xuất số theo thứ tự FIFO
    return 0;
}