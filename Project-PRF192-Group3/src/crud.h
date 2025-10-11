#ifndef CRUD_H
#define CRUD_H

#include "product.h"

// Function declarations for CRUD operations
void addProduct(Product *products, int *productCount);
void deleteProduct(Product *products, int *productCount, const char *id);
void updateProduct(Product *products, int productCount, const char *id);
void viewAllProducts(const Product *products, int productCount);

#endif // CRUD_H