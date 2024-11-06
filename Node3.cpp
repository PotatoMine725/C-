#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE {
    int num;
    struct NODE *next;
};

struct NODE *themN(struct NODE *head, struct NODE *num) {
    if (head == NULL) {
        head = num;
    } else {
        struct NODE *tg = head;
        while (tg->next != NULL)
            tg = tg->next;
        tg->next = num;
    }
    num->next = NULL;  
    return head;
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

struct NODE *sapxep(struct NODE *head) {
    struct NODE *dayDaXep = NULL;
    struct NODE *dayHienTai = head;

    while (dayHienTai != NULL) {
        struct NODE *next = dayHienTai->next;

        if (dayDaXep == NULL || dayDaXep->num >= dayHienTai->num) {
            dayHienTai->next = dayDaXep;
            dayDaXep = dayHienTai;
        } else {
            struct NODE *tam = dayDaXep;
            while (tam->next != NULL && tam->next->num < dayHienTai->num) {
                tam = tam->next;
            }
            dayHienTai->next = tam->next;
            tam->next = dayHienTai;
        }
        dayHienTai = next;
    }
    return dayDaXep;
}

struct NODE *chen(struct NODE *head, int num) {
    struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));
    if (newNode == NULL) {
        printf("Khong the cap bo nho\n");
        return head;
    }
    newNode->num = num;
    newNode->next = NULL; 

    if (head == NULL || head->num >= newNode->num) {
        newNode->next = head;
        return newNode;
    }
    struct NODE *truoc = head;
    while (truoc->next != NULL && truoc->next->num < newNode->num) {
        truoc = truoc->next;
    }
    newNode->next = truoc->next;
    truoc->next = newNode;
    return head;
}

struct NODE *xoaSo(struct NODE *head, int num) {
    struct NODE *tam = head;
    struct NODE *truoc = NULL;
    while (tam != NULL && tam->num != num) {
        truoc = tam;
        tam = tam->next;
    }
    if (tam == NULL) {
        printf("Khong tim thay so %d trong danh sach.\n", num);
        return head;
    }
    if (truoc == NULL) {
        head = tam->next;
    } else {
        truoc->next = tam->next;
    }
    free(tam);
    return head;
}

int kiemTraSo(struct NODE *head, int num) {
    struct NODE *tam = head;

    while (tam != NULL) {
        if (tam->num == num) {
            return 1;
        }
        tam = tam->next;
    }

    return 0;
}

struct NODE *ghep(struct NODE *head1, struct NODE *head2) {
    if (head1 == NULL) return head2;
    struct NODE *tg = head1;
    while (tg->next != NULL) {
        tg = tg->next;
    }
    tg->next = head2;
    return head1;
}

int main() {
    struct NODE *Head = NULL;
    struct NODE *Head2 = NULL;
    int choice = -1, n;

    Head = nhap();
    printf("Day so vua nhap: ");
    xuat(Head);
    Head = sapxep(Head);
    printf("Day so sau khi sap xep: ");
    xuat(Head);

    do {
        printf("\n--- Menu ---\n");
        printf("1. Chen so\n");
        printf("2. Xoa so\n");
        printf("3. Kiem tra so\n");
        printf("4. Ghep 2 day so\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so muon chen: ");
                scanf("%d", &n);
                Head = chen(Head, n);
                printf("Danh sach sau khi chen: ");
                xuat(Head);
                break;

            case 2:
                printf("Nhap so muon xoa: ");
                scanf("%d", &n);
                Head = xoaSo(Head, n);
                printf("Danh sach sau khi xoa: ");
                xuat(Head);
                break;

            case 3:
                printf("Nhap so muon kiem tra: ");
                scanf("%d", &n);
                if (kiemTraSo(Head, n)) {
                    printf("So %d co trong danh sach.\n", n);
                } else {
                    printf("So %d khong co trong danh sach.\n", n);
                }
                break;

            case 4:
			    if (Head == NULL) {
			        printf("Danh sach dau tien chua co phan tu. Vui long nhap truoc.\n");
			        Head = nhap();
			        Head = sapxep(Head);
			        printf("Danh sach dau tien sau khi nhap va sap xep: ");
			        xuat(Head);
			    }
			    else {
			        fflush(stdin);
			        printf("Nhap day so thu hai:\n");
			        Head2 = nhap();
			        Head = ghep(Head, Head2);
			        Head = sapxep(Head);
			        printf("Danh sach sau khi ghep va sap xep: ");
			        xuat(Head);
			    }
			    break; 

            case 0:
                printf("Thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    xoamem(Head);
    return 0;
}
