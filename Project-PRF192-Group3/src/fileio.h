#ifndef FILEIO_H
#define FILEIO_H

#include "product.h"

// Function to save product data to a file
void saveToFile(const char *filename, Product *products, int productCount);

// Function to load product data from a file
int loadFromFile(const char *filename, Product *products, int maxProducts);

#endif // FILEIO_H