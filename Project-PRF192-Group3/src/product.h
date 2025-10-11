// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    char id[15];
    char name[50];
    int quantity;
    char stockName[30];
    float unitPrice;
} Product;

// Function declarations
void inputProductInfo(Product *product);
void displayProduct(const Product *product);
void calculateTotalValue(const Product *product, float *totalValue);
void statisticByStock(Product *products, int productCount);

#endif // PRODUCT_H