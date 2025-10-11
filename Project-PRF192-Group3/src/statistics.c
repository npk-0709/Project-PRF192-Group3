#include <stdio.h>
#include <string.h>
#include "product.h"
#include "statistics.h"

void statisticByStock(Product products[], int productCount) {
    int stockCount = 0;
    char stockNames[50][30]; // Assuming a maximum of 50 different stock names
    int stockQuantities[50] = {0};

    for (int i = 0; i < productCount; i++) {
        int found = 0;
        for (int j = 0; j < stockCount; j++) {
            if (strcmp(products[i].stockName, stockNames[j]) == 0) {
                stockQuantities[j] += products[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(stockNames[stockCount], products[i].stockName);
            stockQuantities[stockCount] = products[i].quantity;
            stockCount++;
        }
    }

    printf("Product statistics by stock name:\n");
    for (int i = 0; i < stockCount; i++) {
        printf("Stock Name: %s, Total Quantity: %d\n", stockNames[i], stockQuantities[i]);
    }
}