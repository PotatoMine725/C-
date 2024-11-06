#include <stdio.h>
#include <stdlib.h>

struct BT {
    int coSo;
    int soMu;
};

struct Node {
    struct BT data;
    struct Node *next;
};

struct Node* themN(struct Node *dau, struct Node *moi) {
    if (dau == NULL) {
        dau = moi;
    } else {
        struct Node *tg = dau;
        while (tg->next != NULL) {
            tg = tg->next; 
        }
        tg->next = moi; 
    }
    moi->next = NULL; 
    return dau; 
}

struct Node* taoNut() {
    struct Node *nutMoi = (struct Node *)malloc(sizeof(struct Node)); 
    if (nutMoi == NULL) {
        printf("Khong the cap phat bo nho\n");
        exit(1); 
    }
    printf("Nhap co so: ");
    scanf("%d", &nutMoi->data.coSo); 
    printf("Nhap so mu: ");
    scanf("%d", &nutMoi->data.soMu); 
    nutMoi->next = NULL; 
    return nutMoi; 
}

struct Node* nhapDanhSach(struct Node *head) {
    char tiepTuc;
    do {
        struct Node *nutMoi = taoNut(); 
        head = themN(head, nutMoi); 

        printf("Ban co muon nhap tiep khong? (y/n): ");
        scanf(" %c", &tiepTuc); 
    } while (tiepTuc == 'y' || tiepTuc == 'Y'); 
    return head; 
}

void xuat(struct Node *dau) {
    struct Node *tg = dau;
    while (tg != NULL) {
        int coSoXuat = tg->data.coSo;
        if (coSoXuat % 2 != 0) {
            coSoXuat += 1; 
        }
        printf("%dx^%d ", coSoXuat, tg->data.soMu);
        tg = tg->next;
        if (tg != NULL) {
            printf("+ ");
        }
    }
    printf("\n");
}

int main() {
    struct Node *head = NULL; 
    head = nhapDanhSach(head); 
    printf("Danh sach da nhap:\n");
    xuat(head);
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp); 
    }

    return 0;
}