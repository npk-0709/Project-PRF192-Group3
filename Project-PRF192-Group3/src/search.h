// src/search.h

#ifndef SEARCH_H
#define SEARCH_H

#include "product.h"

// Function to search for a product by its ID
Product* searchProductByID(const char* id, Product* products, int productCount);

// Function to search for products by name (case insensitive)
void searchProductByName(const char* name, Product* products, int productCount);

#endif // SEARCH_H