#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// 1. Struct Product được giữ nguyên, nhưng bỏ trường 'count' không cần thiết
typedef struct {
    char name[50];
    double price;
    int quantity;
} Product;

// 2. Chỉ cần MỘT mảng để lưu tất cả sản phẩm
Product products[MAX]; 
int count = 0; // Biến đếm số lượng sản phẩm hiện có

// Hàm tiện ích (không đổi)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// 3. Tất cả các hàm bây giờ sẽ thao tác trên mảng 'products'
void addProduct() {
    if (count >= MAX) {
        printf("Danh sach da day!\n");
        return;
    }
    printf("Nhap ten san pham: ");
    clearInputBuffer();
    fgets(products[count].name, sizeof(products[count].name), stdin);
    removeNewline(products[count].name);

    printf("Nhap gia: ");
    scanf("%lf", &products[count].price);

    printf("Nhap so luong: ");
    scanf("%d", &products[count].quantity);

    count++;
    printf("Da them san pham!\n");
}

void displayProducts() {
    if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("\n--- DANH SACH SAN PHAM ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Ten: %s | Gia: %.2f | So luong: %d\n",
               i + 1, products[i].name, products[i].price, products[i].quantity);
    }
}

void editProduct() {
    if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    displayProducts();
    int index, choice;
    printf("Nhap so thu tu san pham muon chinh sua: ");
    scanf("%d", &index);
    if (index < 1 || index > count) {
        printf("So thu tu khong hop le!\n");
        return;
    }
    index--; // Chuyển từ số thứ tự (bắt đầu từ 1) sang chỉ số mảng (bắt đầu từ 0)

    printf("Chon thong tin can chinh sua:\n");
    printf("1. Ten san pham\n2. Gia\n3. So luong\nNhap lua chon: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
        case 1:
            printf("Nhap ten moi: ");
            fgets(products[index].name, sizeof(products[index].name), stdin);
            removeNewline(products[index].name);
            break;
        case 2:
            printf("Nhap gia moi: ");
            scanf("%lf", &products[index].price);
            break;
        case 3:
            printf("Nhap so luong moi: ");
            scanf("%d", &products[index].quantity);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return;
    }
    printf("Da cap nhat san pham!\n");
}

void deleteProduct() {
    if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    displayProducts();
    int index;
    printf("Nhap so thu tu san pham muon xoa: ");
    scanf("%d", &index);
    if (index < 1 || index > count) {
        printf("So thu tu khong hop le!\n");
        return;
    }
    index--; 
    
    // Ghi đè sản phẩm cần xóa bằng sản phẩm kế tiếp nó
    for (int i = index; i < count - 1; i++) {
        products[i] = products[i + 1]; // Gán cả struct, code gọn hơn nhiều!
    }
    count--;
    printf("Da xoa san pham!\n");
}

void searchProduct() {
     if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    int choice;
    printf("Tim theo:\n1. Ten\n2. Gia\n3. So luong\nNhap lua chon: ");
    scanf("%d", &choice);
    clearInputBuffer();

    int found = 0;
    switch(choice) {
        case 1: {
            char keyword[50];
            printf("Nhap ten can tim: ");
            fgets(keyword, sizeof(keyword), stdin);
            removeNewline(keyword);
            for (int i = 0; i < count; i++) {
                if (strcmp(products[i].name, keyword) == 0) {
                    printf("Tim thay: %s | Gia: %.2f | So luong: %d\n", products[i].name, products[i].price, products[i].quantity);
                    found = 1;
                }
            }
            break;
        }
        case 2: {
            double price;
            printf("Nhap gia can tim: ");
            scanf("%lf", &price);
            for (int i = 0; i < count; i++) {
                if (products[i].price == price) {
                     printf("Tim thay: %s | Gia: %.2f | So luong: %d\n", products[i].name, products[i].price, products[i].quantity);
                     found = 1;
                }
            }
            break;
        }
        case 3: {
            int qty;
            printf("Nhap so luong can tim: ");
            scanf("%d", &qty);
            for (int i = 0; i < count; i++) {
                if (products[i].quantity == qty) {
                    printf("Tim thay: %s | Gia: %.2f | So luong: %d\n", products[i].name, products[i].price, products[i].quantity);
                    found = 1;
                }
            }
            break;
        }
        default:
            printf("Lua chon khong hop le!\n");
            return;
    }

    if (!found) {
        printf("Khong tim thay san pham nao phu hop!\n");
    }
}

void sortProduct() {
    if (count < 2) { // Không cần sắp xếp nếu có 0 hoặc 1 sản phẩm
        printf("Danh sach khong can sap xep.\n");
        return;
    }
    int choice;
    printf("Sap xep theo:\n1. Ten (A-Z)\n2. Gia (Thap den cao)\n3. So luong (It den nhieu)\nNhap lua chon: ");
    scanf("%d", &choice);

    Product temp; // Chỉ cần một biến tạm kiểu Product để hoán đổi
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int shouldSwap = 0;
            if (choice == 1 && strcmp(products[i].name, products[j].name) > 0) shouldSwap = 1;
            else if (choice == 2 && products[i].price > products[j].price) shouldSwap = 1;
            else if (choice == 3 && products[i].quantity > products[j].quantity) shouldSwap = 1;

            if (shouldSwap) {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach!\n");
    displayProducts(); // Hiển thị danh sách sau khi sắp xếp
}

void saveToFile() {
    FILE *f = fopen("products.txt", "w");
    if (f == NULL) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s|%.2f|%d\n", products[i].name, products[i].price, products[i].quantity);
    }
    fclose(f);
    printf("Da luu danh sach vao file products.txt!\n");
}

void loadFromFile() {
    FILE *f = fopen("products.txt", "r");
    if (f == NULL) {
        // Không cần thông báo lỗi nếu file chưa tồn tại
        return;
    }
    count = 0;
    while (count < MAX && fscanf(f, "%49[^|]|%lf|%d\n", products[count].name, &products[count].price, &products[count].quantity) == 3) {
        count++;
    }
    fclose(f);
    printf("Da tai danh sach tu file products.txt!\n");
}

int main() {
    loadFromFile(); // Tự động tải dữ liệu khi chương trình bắt đầu
    int choice;
    do {
        printf("\n=== QUAN LY SAN PHAM ===\n");
        printf("1. Them san pham\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Chinh sua san pham\n");
        printf("4. Xoa san pham\n");
        printf("5. Tim kiem san pham\n");
        printf("6. Sap xep san pham\n");
        printf("7. Luu vao file\n");
        // Bỏ chức năng đọc file khỏi menu vì đã tự động hóa
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: editProduct(); break;
            case 4: deleteProduct(); break;
            case 5: searchProduct(); break;
            case 6: sortProduct(); break;
            case 7: saveToFile(); break;
            case 0:
                printf("Thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    return 0;
}
