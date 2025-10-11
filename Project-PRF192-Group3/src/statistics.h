#ifndef STATISTICS_H
#define STATISTICS_H

#include "product.h"

// Function to count the number of products per stock name
void statisticByStock(Product *products, int productCount);

// Function to calculate the total value of stock
float calculateTotalValue(Product *products, int productCount);

#endif // STATISTICS_H