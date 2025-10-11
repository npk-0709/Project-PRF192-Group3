#include <stdio.h>
#include <string.h>
#include "product.h"
#include "sort.h"

void sortProductsByName(Product *products, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(products[j].name, products[j + 1].name) > 0) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void sortProductsByQuantity(Product *products, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((ascending && products[j].quantity > products[j + 1].quantity) ||
                (!ascending && products[j].quantity < products[j + 1].quantity)) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void sortProductsByPrice(Product *products, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((ascending && products[j].unitPrice > products[j + 1].unitPrice) ||
                (!ascending && products[j].unitPrice < products[j + 1].unitPrice)) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}