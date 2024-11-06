#include <stdio.h>
#include <stdlib.h>

struct NODE {
    int num;
    struct NODE *next;
};

struct NODE *themN(struct NODE *head, struct NODE *num) {
    num->next = head;
    return num;
}

struct NODE *xoaN(struct NODE *head, int num) {
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

// Sắp xếp danh sách
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

struct NODE *ghep(struct NODE *head1, struct NODE *head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct NODE *tg = head2;
    while (tg->next != NULL) {
        tg = tg->next;
    }
    tg->next = head1;
    return head2;
}

int main() {
    struct NODE *Head = NULL;
    struct NODE *Head2 = NULL;
    int choice, n;

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
            case 1: {
                struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));
                if (newNode == NULL) {
                    printf("Khong the cap bo nho\n");
                    break;
                }
                printf("Nhap so muon chen: ");
                scanf("%d", &n);
                newNode->num = n;
                Head = themN(Head, newNode); 
                printf("Danh sach sau khi chen: ");
                Head = sapxep(Head);
                xuat(Head);
                break;
            }

            case 2: {
                printf("Nhap so muon xoa: ");
                scanf("%d", &n);
                Head = xoaN(Head, n);
                printf("Danh sach sau khi xoa: ");
                xuat(Head);
                break;
            }

            case 3: {
                printf("Nhap so muon kiem tra: ");
                scanf("%d", &n);
                struct NODE *tam = Head;
                int found = 0;
                while (tam != NULL) {
                    if (tam->num == n) {
                        found = 1;
                        break;
                    }
                    tam = tam->next;
                }
                if (found) {
                    printf("So %d co trong danh sach.\n", n);
                } else {
                    printf("So %d khong co trong danh sach.\n", n);
                }
                break;
            }

            case 4: {
                if (Head == NULL) {
                    printf("Danh sach dau tien chua co phan tu. Vui long nhap truoc.\n");
                    Head = nhap();
                    Head = sapxep(Head);
                    printf("Danh sach dau tien sau khi nhap va sap xep: ");
                    xuat(Head);
                }
                printf("Nhap day so thu hai:\n");
                Head2 = nhap();
                Head = ghep(Head, Head2);
                Head = sapxep(Head);
                printf("Danh sach sau khi ghep va sap xep: ");
                xuat(Head);
                break;
            }

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