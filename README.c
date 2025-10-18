#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char names[MAX][50];
double prices[MAX];
int quantities[MAX];
int count = 0;


void addProduct() {
    printf("Enter product name (Ex: Banh_Mi): ");
    scanf("%s", names[count]);
    printf("Nhap gia: ");
    scanf("%lf", &prices[count]);
    printf("Nhap so luong: ");
    scanf("%d", &quantities[count]);
    count++;
    printf("Da them san pham!\n");
}


void displayProducts() {
	int i;
    if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("\n--- DANH SACH SAN PHAM ---\n");
    for (i = 0; i < count; i++) {
        printf("%d. Ten: %s | Gia: %.2f | So luong: %d\n",
               i + 1, names[i], prices[i], quantities[i]);
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
    index--;

    printf("Chon thong tin can chinh sua:\n");
    printf("1. Ten san pham\n2. Gia\n3. So luong\nNhap lua chon: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Nhap ten moi: ");
            scanf("%s", names[index]);
            break;
        case 2:
            printf("Nhap gia moi: ");
            scanf("%lf", &prices[index]);
            break;
        case 3:
            printf("Nhap so luong moi: ");
            scanf("%d", &quantities[index]);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return;
    }
    printf("Da cap nhat san pham!\n");
}


void deleteProduct() {
	int i;
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
    for (i = index; i < count - 1; i++) {
        strcpy(names[i], names[i + 1]);
        prices[i] = prices[i + 1];
        quantities[i] = quantities[i + 1];
    }
    count--;
    printf("Da xoa san pham!\n");
}


void searchProduct() {
	int i;
    if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    int choice;
    printf("Tim theo:\n1. Ten\n2. Gia\n3. So luong\nNhap lua chon: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char keyword[50];
        printf("Nhap ten can tim: ");
        scanf("%s", keyword);
        for (i = 0; i < count; i++) {
            if (strcmp(names[i], keyword) == 0) {
                printf("Tim thay: %s | Gia: %.2f | So luong: %d\n", names[i], prices[i], quantities[i]);
                return;
            }
        }
        printf("Khong tim thay san pham!\n");
    } else if (choice == 2) {
        double price;
        printf("Nhap gia can tim: ");
        scanf("%lf", &price);
        for (i = 0; i < count; i++) {
            if (prices[i] == price) {
                printf("Tim thay: %s | Gia: %.2f | So luong: %d\n", names[i], prices[i], quantities[i]);
                return;
            }
        }
        printf("Khong tim thay san pham!\n");
    } else if (choice == 3) {
        int qty;
        printf("Nhap so luong can tim: ");
        scanf("%d", &qty);
        for (int i = 0; i < count; i++) {
            if (quantities[i] == qty) {
                printf("Tim thay: %s | Gia: %.2f | So luong: %d\n", names[i], prices[i], quantities[i]);
                return;
            }
        }
        printf("Khong tim thay san pham!\n");
    } else {
        printf("Lua chon khong hop le!\n");
    }
}


void sortProduct() {
	int i, j;
    if (count == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    int choice;
    printf("Sap xep theo:\n1. Ten\n2. Gia\n3. So luong\nNhap lua chon: ");
    scanf("%d", &choice);

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            int swap = 0;
            if (choice == 1 && strcmp(names[i], names[j]) > 0) swap = 1;
            else if (choice == 2 && prices[i] > prices[j]) swap = 1;
            else if (choice == 3 && quantities[i] > quantities[j]) swap = 1;

            if (swap) {
                char tempName[50];
                double tempPrice;
                int tempQty;
                strcpy(tempName, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempName);
                tempPrice = prices[i]; prices[i] = prices[j]; prices[j] = tempPrice;
                tempQty = quantities[i]; quantities[i] = quantities[j]; quantities[j] = tempQty;
            }
        }
    }
    printf("Da sap xep danh sach!\n");
}


void saveToFile() {
	int i;
    FILE *f = fopen("products.txt", "w");
    if (f == NULL) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fprintf(f, "%s %.2f %d\n", names[i], prices[i], quantities[i]);
    }
    fclose(f);
    printf("Da luu danh sach vao file products.txt!\n");
}


void loadFromFile() {
    FILE *f = fopen("products.txt", "r");
    if (f == NULL) {
        printf("Khong tim thay file products.txt!\n");
        return;
    }
    count = 0;
    while (fscanf(f, "%s %lf %d", names[count], &prices[count], &quantities[count]) == 3) {
        count++;
    }
    fclose(f);
    printf("Da tai danh sach tu file products.txt!\n");
}


int main() {
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
        printf("8. Doc tu file\n");
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
            case 8: loadFromFile(); break;
            case 0:
                printf("Thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    return 0;
}

