#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    char id[15];
    char name[50];
    int quantity;
    char stockName[30];
    float unitPrice;
} Product;

#endif
