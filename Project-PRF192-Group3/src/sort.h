#ifndef SORT_H
#define SORT_H

#include "product.h"

// Function prototypes for sorting products
void sortProductsByName(Product *products, int count);
void sortProductsByQuantity(Product *products, int count, int ascending);
void sortProductsByPrice(Product *products, int count, int ascending);

#endif // SORT_H