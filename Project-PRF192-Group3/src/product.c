#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

// Function to add a new product
void addProduct(Product *products, int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Cannot add more products. Maximum limit reached.\n");
        return;
    }
    
    Product newProduct;
    printf("Enter product ID: ");
    scanf("%s", newProduct.id);
    printf("Enter product name: ");
    scanf(" %[^\n]", newProduct.name);
    printf("Enter quantity: ");
    scanf("%d", &newProduct.quantity);
    printf("Enter stock name: ");
    scanf(" %[^\n]", newProduct.stockName);
    printf("Enter unit price: ");
    scanf("%f", &newProduct.unitPrice);
    
    products[*count] = newProduct;
    (*count)++;
    printf("Product added successfully.\n");
}

// Function to delete a product by ID
void deleteProduct(Product *products, int *count, const char *id) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(products[i].id, id) == 0) {
            for (int j = i; j < *count - 1; j++) {
                products[j] = products[j + 1];
            }
            (*count)--;
            printf("Product deleted successfully.\n");
            return;
        }
    }
    printf("Product with ID %s not found.\n", id);
}

// Function to update product information
void updateProduct(Product *products, int count, const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Updating product ID: %s\n", products[i].id);
            printf("Enter new product name: ");
            scanf(" %[^\n]", products[i].name);
            printf("Enter new quantity: ");
            scanf("%d", &products[i].quantity);
            printf("Enter new stock name: ");
            scanf(" %[^\n]", products[i].stockName);
            printf("Enter new unit price: ");
            scanf("%f", &products[i].unitPrice);
            printf("Product updated successfully.\n");
            return;
        }
    }
    printf("Product with ID %s not found.\n", id);
}

// Function to view all products
void viewAllProducts(Product *products, int count) {
    if (count == 0) {
        printf("No products available.\n");
        return;
    }
    
    printf("Product List:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %s, Name: %s, Quantity: %d, Stock Name: %s, Unit Price: %.2f\n",
               products[i].id, products[i].name, products[i].quantity,
               products[i].stockName, products[i].unitPrice);
    }
}