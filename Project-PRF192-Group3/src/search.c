#include <stdio.h>
#include <string.h>
#include "product.h"
#include "search.h"

// Function to search for a product by ID
Product* searchProductByID(Product* products, int productCount, const char* id) {
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            return &products[i]; // Return pointer to the found product
        }
    }
    return NULL; // Return NULL if not found
}

// Function to search for products by name (case insensitive)
void searchProductByName(Product* products, int productCount, const char* name) {
    printf("Products matching '%s':\n", name);
    for (int i = 0; i < productCount; i++) {
        if (strstr(strlwr(products[i].name), strlwr(name)) != NULL) {
            printf("ID: %s, Name: %s, Quantity: %d, Stock Name: %s, Unit Price: %.2f\n",
                   products[i].id, products[i].name, products[i].quantity,
                   products[i].stockName, products[i].unitPrice);
        }
    }
}

// Helper function to convert string to lowercase
char* strlwr(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}