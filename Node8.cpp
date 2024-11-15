#include <stdio.h>
#include <stdlib.h>

struct Node {
    int so;
    struct Node *tiep; 
};

struct Node *addN(struct Node *dau, struct Node *so) {
    if (dau == NULL) {
        dau = so;
        dau->tiep = NULL; 
    } else {
        struct Node *tg = dau;
        while (tg->tiep != NULL) {
            tg = tg->tiep;
        }
        tg->tiep = so;
        so->tiep = NULL; 
    }
    return dau;
}

void outN(struct Node *dau) {
    struct Node *tg = dau;
    while (tg != NULL) {
        printf("%d ", tg->so);
        tg = tg->tiep;
    }
    printf("\n");
}

void inN(struct Node **dau) {
    struct Node *p;
    int so;

    while (1) {
        printf("Nhap so: ");
        if (scanf("%d", &so) != 1) {
            printf("Da nhap ky tu khong phai so. Dung nhap.\n");
            while (getchar() != '\n');
            break;
        }
        p = (struct Node *)malloc(sizeof(struct Node));
        if (p == NULL) {
            printf("Khong the cap phat\n");
            return;
        }
        p->so = so;
        p->tiep = NULL;
        *dau = addN(*dau, p);
    }
}


int kiemTraSo(struct Node *head, int num) {
    struct Node *tam = head;
    while (tam != NULL) {
        if (tam->so == num) {
            return 1;
        }
        tam = tam->tiep; 
    }
    return 0;
}

struct Node *chenTaiViTri(struct Node *dau, int so, int viTri) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Khong the cap phat\n");
        return dau; 
    }
    newNode->so = so;
    newNode->tiep = NULL;
    if (viTri == 0) {
        newNode->tiep = dau; 
        return newNode;
    }
    struct Node *tg = dau;
    for (int i = 0; i < viTri-1; i++) {
        if (tg == NULL) {
            printf("Vi tri khong hop le\n");
            free(newNode); 
            return dau;
        }
        tg = tg->tiep;
    }

    newNode->tiep = tg->tiep; 
    tg->tiep = newNode; 

    return dau; 
}

struct Node *chenGiamDan(struct Node *dau, struct Node *newNode) {
    if (dau == NULL || newNode->so > dau->so) {
        newNode->tiep = dau; 
        return newNode; 
    }
    struct Node *tg = dau;
    while (tg->tiep != NULL && tg->tiep->so >= newNode->so) {
        tg = tg->tiep; 
    }
    newNode->tiep = tg->tiep; 
    tg->tiep = newNode; 

    return dau;
}

struct Node *sapXepGiamDan(struct Node *head) {
    if (head == NULL) return NULL; 
    struct Node *daXep = NULL;
    struct Node *hienTai = head;
    while (hienTai != NULL) {
        struct Node *next = hienTai->tiep; 
        hienTai->tiep = NULL; 
        daXep = chenGiamDan(daXep, hienTai); 
        hienTai = next; 
    }

    return daXep; 
}

void freeList(struct Node *dau) {
    struct Node *tg;
    while (dau != NULL) {
        tg = dau;
        dau = dau->tiep;
        free(tg);
    }
}

struct Node *ChenXep(struct Node *dau, int so) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Khong the cap phat\n");
        return dau; 
    }
    newNode->so = so;
    return chenGiamDan(dau, newNode);
}

int main() {
    struct Node *dau = NULL;
    int choice;
    int so, viTri;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Nhap danh sach\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Kiem tra so trong danh sach\n");
        printf("4. Chen so tai vi tri\n");
        printf("5. Chen so vao danh sach da sap xep\n");
        printf("6. Sap xep danh sach giam dan\n");
        printf("7. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inN(&dau); 
                break;
            case 2:
                outN(dau); 
                break;
            case 3:
                printf("Nhap so can kiem tra: ");
                scanf("%d", &so);
                if (kiemTraSo(dau, so)) {
                    printf("So %d co trong danh sach\n", so);
                } else {
                    printf("So %d khong co trong danh sach\n", so);
                }
                break;
            case 4:
                printf("Nhap so can chen: ");
                scanf("%d", &so);
                printf("Nhap vi tri can chen: ");
                scanf("%d", &viTri);
                dau = chenTaiViTri(dau, so, viTri); 
                break;
            case 5:
                printf("Nhap so can chen vao danh sach da sap xep: ");
                scanf("%d", &so);
                dau = ChenXep(dau, so); 
                break;
            case 6:
                dau = sapXepGiamDan(dau);
                printf("Danh sach da duoc sap xep giam dan\n");
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 7);

    freeList(dau);
    return 0;
}
