#include <stdio.h>
#include <string.h>
#include "product.h"
#include "validation.h"

void inputProductInfo(Product *product) {
    char tempId[15], tempName[50], tempStockName[30];
    int tempQuantity;
    float tempUnitPrice;
    
    do {
        printf("Enter product ID (max 14 chars): ");
        scanf("%14s", tempId);
        getchar(); // Clear newline
    } while (!validateProductID(tempId));
    strcpy(product->id, tempId);
    
    do {
        printf("Enter product name (max 49 chars): ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = 0; // Remove newline
    } while (!validateProductName(tempName));
    strcpy(product->name, tempName);
    
    do {
        printf("Enter quantity: ");
        scanf("%d", &tempQuantity);
    } while (!validateQuantity(tempQuantity));
    product->quantity = tempQuantity;
    
    getchar(); // Clear newline
    do {
        printf("Enter stock name (max 29 chars): ");
        fgets(tempStockName, sizeof(tempStockName), stdin);
        tempStockName[strcspn(tempStockName, "\n")] = 0; // Remove newline
    } while (!validateStockName(tempStockName));
    strcpy(product->stockName, tempStockName);
    
    do {
        printf("Enter unit price: ");
        scanf("%f", &tempUnitPrice);
    } while (!validateUnitPrice(tempUnitPrice));
    product->unitPrice = tempUnitPrice;
}

void displayProduct(const Product *product) {
    printf("ID: %s | Name: %s | Quantity: %d | Stock: %s | Price: %.2f\n",
           product->id, product->name, product->quantity,
           product->stockName, product->unitPrice);
}

float calculateTotalValue(const Product *product) {
    return product->quantity * product->unitPrice;
}