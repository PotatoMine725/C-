#include <stdio.h>
#include <stdlib.h>

struct NODE {
    int num;
    struct NODE *next;
};

struct NODE *addN(struct NODE *head, struct NODE *num) {
    struct NODE *tg;
    if (head == NULL) 
        head = num; 
    else {
        tg = head;
        while (tg->next != NULL) 
            tg = tg->next;
        tg->next = num; 
    }
    return head;
}

void outN(struct NODE *head) {
    struct NODE *tg = head;
    while (tg != NULL) {
        printf("%d ", tg->num);
        tg = tg->next;
    }
    printf("\n");
}

void freeList(struct NODE *head) {
    struct NODE *tg;
    while (head != NULL) {
        tg = head;
        head = head->next;
        free(tg);
    }
}

int main() {
    struct NODE *Head = NULL, *p;
    int i = 1;
    do {
        p = (struct NODE *)malloc(sizeof(struct NODE));
        if (p == NULL) {
            printf("Khong the cap phat bo nho\n");
            return 1;
        }
        printf("Nhap so thu %d: ", i);
        scanf("%d", &p->num);
        p->next = NULL;

        if (p->num != 0) { 
            Head = addN(Head, p);
            i++;
        } else {
            free(p); 
        }
    } while (p->num != 0);

    outN(Head); 
    freeList(Head); 
    return 0;
}