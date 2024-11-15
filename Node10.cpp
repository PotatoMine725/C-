#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void Tach(struct Node *goc, struct Node **chan, struct Node **le) {
    struct Node *tmp = goc;
    while (tmp != NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->so = tmp->so;
        newNode->tiep = NULL;

        if (tmp->so % 2 == 0) {
            *chan = addN(*chan, newNode);
        } else {
            *le = addN(*le, newNode);
        }
        tmp = tmp->tiep;
    }
}

void xep(struct Node **head) {
    if (*head == NULL)
        return; 
    int daXep;
    struct Node *pTg;
    struct Node *lptr = NULL;

    do {
        daXep = 0;
        pTg = *head;

        while (pTg->tiep != lptr) {
            if (pTg->so > pTg->tiep->so) {
                int temp = pTg->so;
                pTg->so = pTg->tiep->so;
                pTg->tiep->so = temp;
                daXep = 1;
            }
            pTg = pTg->tiep;
        }
        lptr = pTg;
    } while (daXep);
}
int main() {
    struct Node *goc = NULL;
    struct Node *dChan = NULL;
    struct Node *dLe = NULL;
    srand(time(NULL));
    int n;
    printf("Nhap n: ");
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->so = rand() % 100 + 1;
        goc = addN(goc, newNode);
    }

    printf("Danh sach ban dau:\n");
    outN(goc);

    
    Tach(goc, &dChan, &dLe);
    xep(&dChan);
    xep(&dLe);

    printf("Danh sach chan:\n");
    outN(dChan);

    printf("Danh sach le:\n");
    outN(dLe);

    return 0;
}
