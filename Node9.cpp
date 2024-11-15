#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int so;
    struct node *tiep;
};

struct node *addN(struct node *dau, struct node *so) {
    if (dau == NULL) {
        dau = so;
        dau->tiep = NULL; 
    } else {
        struct node *tg = dau;
        while (tg->tiep != NULL) {
            tg = tg->tiep;
        }
        tg->tiep = so;
        so->tiep = NULL; 
    }
    return dau;
}

void outN(struct node *dau) {
    struct node *tg = dau;
    while (tg != NULL) {
        printf("%d ", tg->so);
        tg = tg->tiep;
    }
    printf("\n");
}

int check(struct node *dau, int so) {
    struct node *tg = dau;
    while (tg != NULL) {
        if (tg->so == so) {
            return 0; 
        }
        tg = tg->tiep;
    }
    return 1; 
}

struct node *Random(int n) {
    struct node *dau = NULL;
    int count = 0;
    srand(time(0)); 

    while (count < n) {
        int so = rand() % n + 1; 
        if (check(dau, so)) {
            struct node *newNode = (struct node *)malloc(sizeof(struct node));
            newNode->so = so;
            dau = addN(dau, newNode);
            count++;
        }
    }
    return dau;
}

int main() {
    int n;

    printf("Nhap n: ");
    scanf("%d", &n);

    struct node *danhSach = Random(n);
    printf("Danh sach so ngau nhien: ");
    outN(danhSach);

    struct node *tg;
    while (danhSach != NULL) {
        tg = danhSach;
        danhSach = danhSach->tiep;
        free(tg);
    }

    return 0;
}