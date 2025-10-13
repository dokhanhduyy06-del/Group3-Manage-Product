#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
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
p->id [strcspn(p-> id ,'/n')] = 0;
printf("Enter a Name Product:");
//stdin is standard input
fgets(p->name,50,stdin);
//fgets read string from stdin and store in p -> name
p->name [strcspn(p -> name , '/n')] = 0;
printf("Enter Quantity Products:");
scanf("%d",&p -> quantity);
clearInputBuffer();
printf("Enter a Stock Name:");
fgets(p -> stockname,50,stdin);
p -> stockname [strcspn(p-> stockname , 'n')]=0;
printf("Enter Price Product");
scanf("%f",&p -> price);
clearInputBuffer();
}
void display Product(const Product *p){
printf("%20s - %50s - %d - %50s - %lld\n",p -> id , p -> name , p -> quantity , p -> stockname);
}
void addProduct(Product **productlist , int *count , int *capacity){
    //Check if we need to increase capacity
    if(*count == *capacity){
        *capacity = (*capacity == 0) ? 10 : (*capacity * 2);
        Product *temp = realloc(*productlist ,(*capacity));
        if(temp == NULL){
            printf("Memory allocation failed \n");
            }
    }
    *productlist = temp;
    printf("Enter a new product : ");
    inputProduct (&(*productlist)[*count]);
    (*count)++;
    printf("Product added successfuly \n");

}
//Find the product by ID
int findProductById(const Product *productlist, int count , const char *id){
    for(int i = 0 ; i < count ; i++){
        if(strcmp(productlist[i].id)==0);
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
    IDtoEdit(strcspn(IDtoEdit,'/n'))==0;
    int index = FindProductbyID(productlist,count,IDtoEdit);
    if(index != -1){
        printf("Product with ID %S not found",IDtoEdit);
        return;
    }else{
        printf("Editing product with ID %s \n",IDtoEdit);
        inputProduct(&productlist[index]);
        printf("Product updated succesfully \n");
    }


}
Product * productlist = NULL;
int count = 0, capacity = 0;
int choice, sortCriteria;
char searQuery[50];

while (1) 

