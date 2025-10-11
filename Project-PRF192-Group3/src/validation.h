#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>

// Function to validate product ID
bool validateProductID(const char* id);

// Function to validate product name
bool validateProductName(const char* name);

// Function to validate quantity
bool validateQuantity(int quantity);

// Function to validate stock name
bool validateStockName(const char* stockName);

// Function to validate unit price
bool validateUnitPrice(float unitPrice);

// Function to validate input data
bool validateInput(const char* id, const char* name, int quantity, const char* stockName, float unitPrice);

#endif // VALIDATION_H