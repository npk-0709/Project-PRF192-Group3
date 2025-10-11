#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validation.h"

// Function to validate product ID
int validateProductID(const char *id) {
    if (strlen(id) == 0 || strlen(id) > 15) {
        printf("Invalid Product ID. It must be between 1 and 15 characters.\n");
        return 0;
    }
    return 1;
}

// Function to validate product name
int validateProductName(const char *name) {
    if (strlen(name) == 0 || strlen(name) > 50) {
        printf("Invalid Product Name. It must be between 1 and 50 characters.\n");
        return 0;
    }
    return 1;
}

// Function to validate quantity
int validateQuantity(int quantity) {
    if (quantity < 0) {
        printf("Invalid Quantity. It cannot be negative.\n");
        return 0;
    }
    return 1;
}

// Function to validate stock name
int validateStockName(const char *stockName) {
    if (strlen(stockName) == 0 || strlen(stockName) > 30) {
        printf("Invalid Stock Name. It must be between 1 and 30 characters.\n");
        return 0;
    }
    return 1;
}

// Function to validate unit price
int validateUnitPrice(float unitPrice) {
    if (unitPrice < 0) {
        printf("Invalid Unit Price. It cannot be negative.\n");
        return 0;
    }
    return 1;
}

// Function to validate input for product information
int validateProductInfo(const char *id, const char *name, int quantity, const char *stockName, float unitPrice) {
    return validateProductID(id) && validateProductName(name) && validateQuantity(quantity) &&
           validateStockName(stockName) && validateUnitPrice(unitPrice);
}