#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    Node *Lft;
    Node *Rgt;
};

// Hàm thêm nút vào cây
Node *addN(Node *Tree, Node *ptu) {
    Node *temp, *prev;
    if (Tree == NULL) 
        Tree = ptu;
    else {
        temp = Tree;
        while (temp != NULL) {
            prev = temp;
            if (temp->data > ptu->data)
                temp = temp->Lft;
            else // Nếu bằng hoặc lớn hơn, chèn vào bên phải
                temp = temp->Rgt;
        }
        if (prev->data > ptu->data) 
            prev->Lft = ptu;
        else 
            prev->Rgt = ptu;
    }
    return Tree; 
}

// Hàm tạo nút mới
Node *createN(int value) {
    Node *p = new Node; // Sử dụng malloc nếu dùng C
    if (p != NULL) {
        p->data = value;
        p->Lft = NULL;
        p->Rgt = NULL;
    }
    return p;
}

// Hàm tìm phần tử trong cây
Node *find(Node *tree, int value) {
    while (tree != NULL) {
        if (value == tree->data) {
            return tree; // Tìm thấy
        } else if (value < tree->data) {
            tree = tree->Lft; // Tiếp tục tìm ở nhánh trái
        } else {
            tree = tree->Rgt; // Tiếp tục tìm ở nhánh phải
        }
    }
    return NULL; // Không tìm thấy
}

// Hàm xóa nút khỏi cây
Node *deleteNode(Node *tree, int value) {
    Node *nodeToDelete = find(tree, value); // Tìm nút cần xóa
    if (nodeToDelete == NULL) {
        printf("Khong tim thay phan tu %d de xoa.\n", value);
        return tree; // Nếu không tìm thấy, trả về cây không thay đổi
    }

    // Tìm nút cha của nút cần xóa
    Node *parent = NULL;
    Node *current = tree;
    while (current != NULL && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->Lft;
        } else {
            current = current->Rgt;
        }
    }

    // Nếu nút cần xóa là nút gốc
    if (current == tree) {
        // Xử lý trường hợp gốc có hai con
        if (current->Lft == NULL) {
            Node *temp = current->Rgt;
            delete current; // Giải phóng bộ nhớ
            return temp;
        } else if (current->Rgt == NULL) {
            Node *temp = current->Lft;
            delete current; // Giải phóng bộ nhớ
            return temp;
        }

        // Nút có hai con, tìm giá trị nhỏ nhất trong cây con bên phải
        Node *temp = current->Rgt;
        while (temp->Lft != NULL) {
            temp = temp->Lft;
        }

        // Đổi giá trị của nút cần xóa với giá trị nhỏ nhất tìm được
        current->data = temp->data;

        // Xóa nút nhỏ nhất trong cây con bên phải
        current->Rgt = deleteNode(current->Rgt, temp->data);
    } else {
        // Xử lý trường hợp nút không phải là gốc
        if (current->Lft == NULL) {
            if (parent->Lft == current) {
                parent->Lft = current->Rgt;
            } else {
                parent->Rgt = current->Rgt;
            }
            delete current; // Giải phóng bộ nhớ
        } else if (current->Rgt == NULL) {
            if (parent->Lft == current) {
                parent->Lft = current->Lft;
            } else {
                parent->Rgt = current->Lft;
            }
            delete current; // Giải phóng bộ nhớ
        } else {
            // Nút có hai con, tìm giá trị nhỏ nhất trong cây con bên phải
            Node *temp = current->Rgt;
            while (temp->Lft != NULL) {
                temp = temp->Lft;
            }

            // Đổi giá trị của nút cần xóa với giá trị nhỏ nhất tìm được
            current->data = temp->data;

            // Xóa nút nhỏ nhất trong cây con bên phải
            current->Rgt = deleteNode(current->Rgt, temp->data);
        }
    }

    return tree; // Trả về cây đã thay đổi
}

// Hàm xây dựng cây
Node *Build() {    
    Node *tree = NULL;
    Node *p;
    int value;

    printf("Nhap cac phan tu (nhap 0 de ket thuc):\n");
    while (1) {
        printf("Nhap phan tu: ");
        scanf("%d", &value);
        if (value == 0) break; // Dừng nhập khi gặp 0
        p = createN(value);
        tree = addN(tree, p);
    }

    return tree;
}

// Hàm duyệt cây theo thứ tự giữa (trung thứ tự)
void OutMid(Node *tree) {
    if (tree != NULL) {
        OutMid(tree->Lft);
        printf("%d ", tree->data);
        OutMid(tree->Rgt);
    }
}

// Hàm thêm nút mới
void insert(Node **tree, int value) {
    Node *newNode = createN(value);
    *tree = addN(*tree, newNode);
}

// Hàm chính
int main() {
    Node *Tree = NULL;
    int choice, value;

    do {
        printf("\n=== Menu ===\n");
        printf("1. Xay dung cay\n");
        printf("2. Tim phan tu\n");
        printf("3. Chen phan tu\n");
        printf("4. Xoa phan tu\n");
        printf("5. Duyet cay (in-order traversal)\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Tree = Build();
                break;
            case 2:
                printf("Nhap gia tri can tim: ");
                scanf("%d", &value);
                if (find(Tree, value) != NULL) {
                    printf("Tim thay phan tu: %d\n", value);
                } else {
                    printf("Khong tim thay phan tu %d trong cay.\n", value);
                }
                break;
            case 3:
                printf("Nhap gia tri can chen: ");
                scanf("%d", &value);
                insert(&Tree, value);
                printf("Da chen phan tu %d.\n", value);
                break;
            case 4:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &value);
                Tree = deleteNode(Tree, value);
                break;
            case 5:
                printf("Duyet cay (in-order): ");
                OutMid(Tree);
                printf("\n");
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);

    return 0;
}