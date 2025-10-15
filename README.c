#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
//Define Product structure
typedef struct{
    char id[20];
    char name[50];
    int quantity;
    char stockname[50];
    long long price;
}Product;
//clear input buffer function to avoid infinite loop
void clearInputBuffer(){
    int c;
    while((c = getchar()!= '\n'&& c!= EOF));
}
void inputProduct(Product *p){
printf("Enter ID Product:");
fgets(p->id,20,stdin);
//strcspn removes newline character from string if present /n
p->id [strcspn(p-> id ,"\n")] = 0;
    
printf("Enter a Name Product:");
//stdin is standard input
fgets(p->name,50,stdin);
//fgets read string from stdin and store in p -> name
p->name [strcspn(p -> name , "\n")] = 0;
    
printf("Enter Quantity Products:");
scanf("%d",&p -> quantity);
clearInputBuffer();
    
printf("Enter a Stock Name:");
fgets(p -> stockname,50,stdin);
p -> stockname [strcspn(p-> stockname , "\n")]=0;
    
printf("Enter Price Product");
scanf("%f",&p -> price);
clearInputBuffer();
}
void displayProduct(const Product *p){
printf("%20s - %50s - %d - %50s - %lld\n",p -> id , p -> name , p -> quantity , p -> stockname);
}
void addProduct(Product **productlist , int *count , int *capacity){
    //Check if we need to increase capacity
    if(*count == *capacity){
        *capacity = (*capacity == 0) ? 10 : (*capacity * 2);
        Product *temp = realloc(*productlist ,(*capacity) * sizeof(Product));
        if(temp == NULL){
            printf("Memory allocation failed \n");
            return;
            }
             *productlist = temp;
    }
    printf("Enter a new product : ");
    inputProduct(&(*productlist)[*count]);
    (*count)++;
    printf("Product added successfuly \n");

}
//Find the product by ID
int findProductById(const Product *productlist, int count , const char *id){
    for(int i = 0 ; i < count ; i++){
        if(strcmp(productlist[i].id,id)==0);
        return i;
    }
    return -1;
}
//Edit product function
void EditProduct(Product *productlist,int count){
    char IDtoEdit[20];
    printf("=================EDIT PRODUCT =================\n");
    printf("Enter a ID to edit:");
    fgets(IDtoEdit,20,stdin);
    IDtoEdit[(strcspn(IDtoEdit,"/n"))]==0;
    int index = findProductById(productlist,count,IDtoEdit);
    if(index != -1){
        printf("Product with ID %S not found",IDtoEdit);
        return;
    }else{
        printf("Editing product with ID %s \n",IDtoEdit);
        inputProduct(&productlist[index]);
        printf("Product updated succesfully \n");
    }
}
//Delete product function
    void deleteProduct(Product **productlist , int *count){
        char IDtoDelete[20];
        printf("================DELETE PRODUCT=================\n");
        printf("Enter a ID to delete:");
        fgets(IDtoDelete,20,stdin);
        IDtoDelete[strcspn(IDtoDelete,"/n")] == 0;
        int index = findProductById(*productlist,*count,IDtoDelete);
        if(index != -1){
            if(index  != *count -1){
                (*productlist)[index]=(*productlist)[*count -1];
                (*count)--;
            }
            printf("Deleted product with ID %s successfully \n",IDtoDelete);
        }else{
            printf("Product with ID %s not found \n",IDtoDelete);
        }
     }
//Display all products function
    void displayAllProducts(const Product *productlist , int count){
        printf("================DISPLAY All PRODUTCS=================\n");
        for(int i =0 ; i < count ;i++){
            displayProduct(&productlist[i]);
        }
    }
//Statistitic Product in Inventory
    void statisticProducts(const Product *productlist , int count){
        if(count == 0){
            printf("No products in inventory to statistic");
            return;
        }
        char stocktoFind[50];
        printf("Enter a stock name to statistic");
        fgets(stocktoFind,50,stdin);
        stocktoFind[strcspn(stocktoFind,"/n")] == 0;
        int totalQuantity = 0;
        long long ProductCount =0;
        printf("=================PRODUCT IN STOCK==================\n");
        printf("%20s,%50s,%d,%50s,%lld\n","ID","Name","Quantity","Stock Name,""Price");
        printf("---------------------------------------------------\n");
        for(int i = 0 ; i < count ; i++){
            if(strcmp(productlist[i].stockname,stocktoFind)==0){
                displayProduct(&productlist[i]);
                totalQuantity += productlist[i].quantity;
                ProductCount++;
            }
        }
        if(ProductCount > 0){
            printf("---------------------------------------------------\n");
            printf("Stock Name : %s \n",stocktoFind);
            printf("Total Product :%d \n",totalQuantity);
            printf("Total Product Type : %lld \n",ProductCount);
        }else{
            printf("No products found in stock %s",stocktoFind);
        }
    }

void searchProduct(Product *products, int count, const char *query) {
    printf("Search Results:\n");
    for (int i = 0; i < count; i++) {
        if (strcasecmp(products[i].name, query) == 0 || strcasecmp(products[i].id, query) == 0) {
            displayProduct(&products[i]);
        }
    }
}
int compareByName(const void *a, const void *b) {
    return strcmp(((Product *)a)->name, ((Product *)b)->name);
    
}

int compareByQuantity(const void *a, const void *b) {
    return ((Product *)a)->quantity - ((Product *)b)->quantity;
}

int compareByPrice(const void *a, const void *b) {
    return ((Product *)a)->price > ((Product *)b)->price ? 1 : -1;
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
            break;
        default:
            printf("Invalid sort criteria!\n");
            break;
    }
}
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
