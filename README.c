#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Define Product structure
typedef struct {
    char id[20];
    char name[50];
    int quantity;
    char stockname[50];
    long long price;
} Product;

// Clear input buffer function to avoid infinite loop
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Input product function
void inputProduct(Product *p) {
    printf("Enter ID Product: ");
    fgets(p->id, sizeof(p->id), stdin);
    p->id[strcspn(p->id, "\n")] = 0;

    printf("Enter a Name Product: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = 0;

    printf("Enter Quantity Products: ");
    scanf("%d", &p->quantity);
    clearInputBuffer();

    printf("Enter a Stock Name: ");
    fgets(p->stockname, sizeof(p->stockname), stdin);
    p->stockname[strcspn(p->stockname, "\n")] = 0;

    printf("Enter Price Product: ");
    scanf("%lld", &p->price);
    clearInputBuffer();
}

// Display product function
void displayProduct(const Product *p) {
    printf("%20s | %50s | %d | %50s | %lld\n", p->id, p->name, p->quantity, p->stockname, p->price);
}

// Add product function
void addProduct(Product **productlist, int *count, int *capacity) {
    if (*count == *capacity) {
        *capacity = (*capacity == 0) ? 10 : (*capacity * 2);
        Product *temp = realloc(*productlist, (*capacity) * sizeof(Product));
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        *productlist = temp;
    }
    printf("Enter a new product: \n");
    inputProduct(&(*productlist)[*count]);
    (*count)++;
    printf("Product added successfully.\n");
}

// Find the product by ID
int findProductById(const Product *productlist, int count, const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(productlist[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// Edit product function
void editProduct(Product *productlist, int count) {
    char IDtoEdit[20];
    printf("=================EDIT PRODUCT =================\n");
    printf("Enter an ID to edit: ");
    fgets(IDtoEdit, sizeof(IDtoEdit), stdin);
    IDtoEdit[strcspn(IDtoEdit, "\n")] = 0;

    int index = findProductById(productlist, count, IDtoEdit);
    if (index == -1) {
        printf("Product with ID %s not found.\n", IDtoEdit);
        return;
    } else {
        printf("Editing product with ID %s \n", IDtoEdit);
        inputProduct(&productlist[index]);
        printf("Product updated successfully.\n");
    }
}

// Delete product function
void deleteProduct(Product **productlist, int *count) {
    char IDtoDelete[20];
    printf("================DELETE PRODUCT=================\n");
    printf("Enter an ID to delete: ");
    fgets(IDtoDelete, sizeof(IDtoDelete), stdin);
    IDtoDelete[strcspn(IDtoDelete, "\n")] = 0;

    int index = findProductById(*productlist, *count, IDtoDelete);
    if (index != -1) {
        (*productlist)[index] = (*productlist)[*count - 1];
        (*count)--;
        printf("Deleted product with ID %s successfully.\n", IDtoDelete);
    } else {
        printf("Product with ID %s not found.\n", IDtoDelete);
    }
}

// Display all products function
void displayAllProducts(const Product *productlist, int count) {
    printf("================DISPLAY ALL PRODUCTS=================\n");
    if (count == 0) {
        printf("No products available.\n");
        return;
    }
    printf("%-20s | %-50s | %-5s | %-20s | %-10s\n", "ID", "Name", "Quantity", "Stock Name", "Price");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        displayProduct(&productlist[i]);
    }
}

// Statistic Products in Inventory
void statisticProducts(const Product *productlist, int count) {
    if (count == 0) {
        printf("No products in inventory to statistic.\n");
        return;
    }
    char stocktoFind[50];
    printf("Enter a stock name to statistic: ");
    fgets(stocktoFind, sizeof(stocktoFind), stdin);
    stocktoFind[strcspn(stocktoFind, "\n")] = 0;

    int totalQuantity = 0;
    long long productCount = 0;
    printf("=================PRODUCT IN STOCK==================\n");
    printf("%20s | %50s | %d | %50s | %lld\n", "ID", "Name", "Quantity", "Stock Name", "Price");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(productlist[i].stockname, stocktoFind) == 0) {
            displayProduct(&productlist[i]);
            totalQuantity += productlist[i].quantity;
            productCount++;
        }
    }

    if (productCount > 0) {
        printf("---------------------------------------------------\n");
        printf("Stock Name: %s\n", stocktoFind);
        printf("Total Quantity: %d\n", totalQuantity);
        printf("Total Product Types: %lld\n", productCount);
    } else {
        printf("No products found in stock %s.\n", stocktoFind);
    }
}

// Search product function
void searchProduct(const Product *products, int count, const char *query) {
    printf("Search Results:\n");
    for (int i = 0; i < count; i++) {
        if (strstr(products[i].name, query) || strstr(products[i].id, query)) {
            displayProduct(&products[i]);
        }
    }
}

// Sort products functions
int compareByName(const void *a, const void *b) {
    return strcmp(((Product *)a)->name, ((Product *)b)->name);
}

int compareByQuantity(const void *a, const void *b) {
    return ((Product *)a)->quantity - ((Product *)b)->quantity;
}

int compareByPrice(const void *a, const void *b) {
    return ((Product *)a)->price - ((Product *)b)->price;
}

void sortProducts(Product *products, int count, int criteria) {
    switch (criteria) {
        case 1:
            qsort(products, count, sizeof(Product), compareByName);
            break;
        case 2:
            qsort(products, count, sizeof(Product), compareByQuantity);
            break;
        case 3:
            qsort(products, count, sizeof(Product), compareByPrice);
            displayAllProducts(products, count);
            break;
        default:
            printf("Invalid sort criteria!\n");
            return;
    }
    printf("Products sorted successfully.\n");
}

// Show menu function
void showMenu() {
    printf("\n\n===== PRODUCT MANAGEMENT MENU (C) =====\n");
    printf("1. Add Product \n");
    printf("2. Edit Product \n");
    printf("3. Delete Product \n");
    printf("4. Search Product \n");
    printf("5. Sort Product \n");
    printf("6. Display All Products \n");
    printf("7. Statistics By Stock \n");
    printf("8. Exit Program \n");
    printf("==============================\n");
    printf("Choose an option: ");
}

int main() {
    Product *products = NULL;
    int count = 0, capacity = 0;
    int choice, sortCriteria;
    char searchQuery[50];

    while (1) {
        showMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addProduct(&products, &count, &capacity);
                break;
            case 2:
                if (count == 0) {
                    printf("No products to edit.\n");
                } else {
                    editProduct(products, count);
                }
                break;
            case 3:
                if (count == 0) {
                    printf("No products to delete.\n");
                } else {
                    deleteProduct(&products, &count);
                }
                break;
            case 4:
                if (count == 0) {
                    printf("No products to search.\n");
                } else {
                    printf("Enter name or ID to search: ");
                    fgets(searchQuery, sizeof(searchQuery), stdin);
                    searchQuery[strcspn(searchQuery, "\n")] = 0;
                    searchProduct(products, count, searchQuery);
                }
                break;
            case 5:
                if (count == 0) {
                    printf("No products to sort.\n");
                } else {
                    printf("Sort by: \n1. Name\n2. Quantity\n3. Price\n");
                    printf("Choose a criteria: ");
                    scanf("%d", &sortCriteria);
                    clearInputBuffer();
                    sortProducts(products, count, sortCriteria);
                    displayAllProducts(products, count);
                }
                break;
            case 6:
                displayAllProducts(products, count);
                break;
            case 7:
                statisticProducts(products, count);
                break;
            case 8:
                printf("Exiting program....\n");
                free(products);
                return 0;
            default:
                printf("Invalid option! Please try again.\n");
                break;
        }
    }
}
