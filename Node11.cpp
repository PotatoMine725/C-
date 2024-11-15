#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SV {
    char MSV[10];
    char ten[30];
    char lop[6];
    float dtb;
};

struct Node {
    struct SV data;
    struct Node *tiep;
};

// Hàm thêm sinh viên vào danh sách
struct Node* ThemSV(struct Node *dau, struct SV svien) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = svien;
    newNode->tiep = NULL;

    if (dau == NULL) {
        return newNode; // Nếu danh sách trống, trả về nút mới
    }

    struct Node *temp = dau;
    while (temp->tiep != NULL) {
        temp = temp->tiep;
    }
    temp->tiep = newNode; // Thêm nút mới vào cuối danh sách
    return dau;
}

// Hàm in danh sách sinh viên
void InSvien(struct Node *dau) {
    struct Node *temp = dau;
    while (temp != NULL) {
        printf("MSV: %s, Ten: %s, Lop: %s, DTB: %.2f\n", 
               temp->data.MSV, temp->data.ten, temp->data.lop, temp->data.dtb);
        temp = temp->tiep;
    }
}

// Hàm xóa sinh viên theo mã
struct Node* XoaSv(struct Node *dau, const char *MSV) {
    struct Node *temp = dau;
    struct Node *trc = NULL;

    while (temp != NULL && strcmp(temp->data.MSV, MSV) != 0) {
        trc = temp;
        temp = temp->tiep;
    }

    // Nếu không tìm thấy sinh viên
    if (temp == NULL) {
        printf("Khong tim thay sinh vien voi MSV: %s.\n", MSV);
        return dau;
    }

    // Nếu sinh viên là nút đầu
    if (trc == NULL) {
        dau = temp->tiep;
    } else {
        trc->tiep = temp->tiep;
    }
    
    free(temp); // Giải phóng bộ nhớ
    printf("Da xoa sinh vien voi MSV: %s.\n", MSV);
    return dau;
}

// Hàm tách danh sách
void TachSv(struct Node *goc, struct Node **duoi5, struct Node **tren5) {
    struct Node *htai = goc;
    while (htai != NULL) {
        if (htai->data.dtb < 5) {
            *duoi5 = ThemSV(*duoi5, htai->data);
        } else {
            *tren5 = ThemSV(*tren5, htai->data);
        }
        htai = htai->tiep;
    }
}


// Hàm giải phóng bộ nhớ
void freeList(struct Node *dau) {
    struct Node *temp;
    while (dau != NULL) {
        temp = dau;
        dau = dau->tiep;
        free(temp);
    }
}

// Hàm nhập thông tin sinh viên từ bàn phím
struct SV NhapSv() {
    struct SV svien;
    printf("Nhap MSV: ");
    scanf("%s", svien.MSV);
    printf("Nhap Ten: ");
    getchar(); // Đọc ký tự newline còn sót lại
    fgets(svien.ten, sizeof(svien.ten), stdin);
    svien.ten[strcspn(svien.ten, "\n")] = 0; // Xóa ký tự newline
    printf("Nhap Lop: ");
    scanf("%s", svien.lop);
    printf("Nhap DTB: ");
    scanf("%f", &svien.dtb);
    return svien;
}

int main() {
    struct Node *svienList = NULL;
    struct Node *Duoi5 = NULL;
    struct Node *Tren5 = NULL;
    int choice;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Them sinh vien\n");
        printf("2. Xoa sinh vien\n");
        printf("3. In danh sach sinh vien\n");
        printf("4. Tach danh sach sinh vien theo diem\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct SV svien = NhapSv();
                svienList = ThemSV(svienList, svien);
                break;
            }
            case 2: {
                char msvXoa[10];
                printf("Nhap MSV sinh vien muon xoa: ");
                scanf("%s", msvXoa);
                svienList = XoaSv(svienList, msvXoa);
                break;
            }
            case 3: {
                printf("\nDanh sach sinh vien:\n");
                InSvien(svienList);
                break;
            }
            case 4: {
                Duoi5 = NULL;
                Tren5 = NULL;
                
                TachSv(svienList, &Duoi5, &Tren5);
                printf("\nDanh sach sinh vien diem trung binh duoi 5:\n");
                InSvien(Duoi5);
                printf("\nDanh sach sinh vien diem trung binh >= 5:\n");
                InSvien(Tren5);
                break;
            }
            case 5: {
                printf("Thoat chuong trinh.\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le. Vui long chon lai.\n");
            }
        }
    } while (choice != 5);

    // Giải phóng bộ nhớ
    freeList(svienList);
    freeList(Duoi5);
    freeList(Tren5);

    return 0;
}