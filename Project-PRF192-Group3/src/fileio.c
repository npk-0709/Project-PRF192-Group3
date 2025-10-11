#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "product.h"

#define MAX_PRODUCTS 100

// Function to save product data to a binary file
void saveToFile(Product *products, int count) {
    FILE *file = fopen("data/products.dat", "wb");
    if (file == NULL) {
        perror("Unable to open file for writing");
        return;
    }
    fwrite(products, sizeof(Product), count, file);
    fclose(file);
}

// Function to load product data from a binary file
int loadFromFile(Product *products) {
    FILE *file = fopen("data/products.dat", "rb");
    if (file == NULL) {
        perror("Unable to open file for reading");
        return 0;
    }
    int count = fread(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    return count;
}