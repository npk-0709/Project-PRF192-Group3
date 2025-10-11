#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"
#include "product.h"

void addProduct(Product *products, int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Cannot add more products. Maximum limit reached.\n");
        return;
    }
    
    Product newProduct;
    inputProductInfo(&newProduct);
    products[*count] = newProduct;
    (*count)++;
    printf("Product added successfully.\n");
}

void deleteProduct(Product *products, int *count, const char *id) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(products[i].id, id) == 0) {
            for (int j = i; j < *count - 1; j++) {
                products[j] = products[j + 1];
            }
            (*count)--;
            printf("Product with ID %s deleted successfully.\n", id);
            return;
        }
    }
    printf("Product with ID %s not found.\n", id);
}

void updateProduct(Product *products, int count, const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Updating product with ID %s:\n", id);
            inputProductInfo(&products[i]);
            printf("Product updated successfully.\n");
            return;
        }
    }
    printf("Product with ID %s not found.\n", id);
}