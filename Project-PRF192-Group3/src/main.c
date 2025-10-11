#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "product.h"
#define DATA_FILE "products.dat"
#define MAX_PRODUCTS 100

// Product functions
void inputProductInfo(Product *product);
void displayProduct(const Product *product);
float calculateTotalValue(const Product *product);

// Validation functions
int validateProductID(const char* id);
int validateProductName(const char* name);
int validateQuantity(int quantity);
int validateStockName(const char* stockName);
int validateUnitPrice(float unitPrice);

// CRUD functions
void addProduct(Product *products, int *count);
void deleteProduct(Product *products, int *count, const char *id);
void updateProduct(Product *products, int count, const char *id);
void viewAllProducts(const Product *products, int count);

// Search functions
Product* searchProductByID(const char* id, Product* products, int productCount);
void searchProductByName(const char* name, Product* products, int productCount);

// Sort functions
void sortProductsByName(Product *products, int count);
void sortProductsByQuantity(Product *products, int count, int ascending);
void sortProductsByPrice(Product *products, int count, int ascending);

// Statistics functions
void statisticByStock(Product *products, int productCount);
float calculateTotalStockValue(Product *products, int productCount);

// File I/O functions
void saveToFile(const char *filename, Product *products, int productCount);
int loadFromFile(const char *filename, Product *products, int maxProducts);

// Menu functions
void displayMenu();
void displaySortMenu();
int getUserChoice();
void returnChoice();
void exitProgram();

// ========== VALIDATION IMPLEMENTATIONS ==========
int validateProductID(const char *id) {
    if (strlen(id) == 0 || strlen(id) > 14) {
        printf("Invalid Product ID. Must be 1-14 characters.\n");
        return 0;
    }
    return 1;
}

int validateProductName(const char *name) {
    if (strlen(name) == 0 || strlen(name) > 49) {
        printf("Invalid Product Name. Must be 1-49 characters.\n");
        return 0;
    }
    return 1;
}

int validateQuantity(int quantity) {
    if (quantity < 0) {
        printf("Invalid Quantity. Cannot be negative.\n");
        return 0;
    }
    return 1;
}

int validateStockName(const char *stockName) {
    if (strlen(stockName) == 0 || strlen(stockName) > 29) {
        printf("Invalid Stock Name. Must be 1-29 characters.\n");
        return 0;
    }
    return 1;
}

int validateUnitPrice(float unitPrice) {
    if (unitPrice < 0) {
        printf("Invalid Unit Price. Cannot be negative.\n");
        return 0;
    }
    return 1;
}

// ========== PRODUCT IMPLEMENTATIONS ==========
void inputProductInfo(Product *product) {
    char tempId[15], tempName[50], tempStockName[30];
    int tempQuantity;
    float tempUnitPrice;
    
    do {
        printf("Enter product ID (max 14 chars): ");
        scanf("%14s", tempId);
        getchar();
    } while (!validateProductID(tempId));
    strcpy(product->id, tempId);
    
    do {
        printf("Enter product name (max 49 chars): ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = 0;
    } while (!validateProductName(tempName));
    strcpy(product->name, tempName);
    
    do {
        printf("Enter quantity: ");
        scanf("%d", &tempQuantity);
    } while (!validateQuantity(tempQuantity));
    product->quantity = tempQuantity;
    
    getchar();
    do {
        printf("Enter stock name (max 29 chars): ");
        fgets(tempStockName, sizeof(tempStockName), stdin);
        tempStockName[strcspn(tempStockName, "\n")] = 0;
    } while (!validateStockName(tempStockName));
    strcpy(product->stockName, tempStockName);
    
    do {
        printf("Enter unit price: ");
        scanf("%f", &tempUnitPrice);
    } while (!validateUnitPrice(tempUnitPrice));
    product->unitPrice = tempUnitPrice;
}

void displayProduct(const Product *product) {
    printf("ID: %s | Name: %s | Quantity: %d | Stock: %s | Price: %.2f\n",
           product->id, product->name, product->quantity,
           product->stockName, product->unitPrice);
}

float calculateTotalValue(const Product *product) {
    return product->quantity * product->unitPrice;
}

// ========== CRUD IMPLEMENTATIONS ==========
void addProduct(Product *products, int *count) {
    int i;
    if (*count >= MAX_PRODUCTS) {
        printf("Cannot add more products. Maximum limit reached (%d).\n", MAX_PRODUCTS);
        return;
    }
    
    Product newProduct;
    printf("\n=== Add New Product ===\n");
    inputProductInfo(&newProduct);
    
    for (i = 0; i < *count; i++) {
        if (strcmp(products[i].id, newProduct.id) == 0) {
            printf("Error: Product with ID '%s' already exists!\n", newProduct.id);
            return;
        }
    }
    
    products[*count] = newProduct;
    (*count)++;
    printf("Product added successfully! Total products: %d\n", *count);
}

void deleteProduct(Product *products, int *count, const char *id) {
    int i, j;
    for (i = 0; i < *count; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Deleting product: ");
            displayProduct(&products[i]);
            
            for (j = i; j < *count - 1; j++) {
                products[j] = products[j + 1];
            }
            (*count)--;
            printf("Product deleted successfully! Total products: %d\n", *count);
            return;
        }
    }
    printf("Product with ID '%s' not found.\n", id);
}

void updateProduct(Product *products, int count, const char *id) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(products[i].id, id) == 0) {
            char newId[15];
            printf("Current product information:\n");
            displayProduct(&products[i]);
            printf("\n=== Update Product ===\n");
            
            strcpy(newId, products[i].id);
            inputProductInfo(&products[i]);
            strcpy(products[i].id, newId);
            
            printf("Product updated successfully!\n");
            return;
        }
    }
    printf("Product with ID '%s' not found.\n", id);
}

void viewAllProducts(const Product *products, int count) {
    int i;
    if (count == 0) {
        printf("No products available.\n");
        return;
    }
    
    printf("\n=== Product List (Total: %d) ===\n", count);
    printf("%-15s %-50s %-10s %-30s %-10s %-12s\n", 
           "ID", "Name", "Quantity", "Stock Name", "Unit Price", "Total Value");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    
    for (i = 0; i < count; i++) {
        printf("%-15s %-50s %-10d %-30s %-10.2f %-12.2f\n",
               products[i].id, products[i].name, products[i].quantity,
               products[i].stockName, products[i].unitPrice,
               calculateTotalValue(&products[i]));
    }
}

// ========== SEARCH IMPLEMENTATIONS ==========
static void toLowerStr(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = tolower((unsigned char)src[i]);
        i++;
    }
    dest[i] = '\0';
}

Product* searchProductByID(const char* id, Product* products, int productCount) {
    int i;
    for (i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            return &products[i];
        }
    }
    return NULL;
}

void searchProductByName(const char* name, Product* products, int productCount) {
    char lowerName[50], lowerProductName[50];
    int i, found = 0;
    toLowerStr(lowerName, name);
    
    printf("\n=== Products matching '%s' ===\n", name);
    
    for (i = 0; i < productCount; i++) {
        toLowerStr(lowerProductName, products[i].name);
        if (strstr(lowerProductName, lowerName) != NULL) {
            displayProduct(&products[i]);
            found++;
        }
    }
    
    if (found == 0) {
        printf("No products found matching '%s'.\n", name);
    } else {
        printf("Total: %d product(s) found.\n", found);
    }
}

// ========== SORT IMPLEMENTATIONS ==========
void sortProductsByName(Product *products, int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (strcmp(products[j].name, products[j + 1].name) > 0) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void sortProductsByQuantity(Product *products, int count, int ascending) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
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
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if ((ascending && products[j].unitPrice > products[j + 1].unitPrice) ||
                (!ascending && products[j].unitPrice < products[j + 1].unitPrice)) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

// ========== STATISTICS IMPLEMENTATIONS ==========
void statisticByStock(Product *products, int productCount) {
    int i, j;
    char stockNames[50][30];
    int stockCounts[50] = {0};
    float stockValues[50] = {0.0};
    int uniqueStocks = 0;
    float grandTotal = 0.0;
    
    if (productCount == 0) {
        printf("No products available for statistics.\n");
        return;
    }

    for (i = 0; i < productCount; i++) {
        int found = 0;
        for (j = 0; j < uniqueStocks; j++) {
            if (strcmp(products[i].stockName, stockNames[j]) == 0) {
                stockCounts[j]++;
                stockValues[j] += calculateTotalValue(&products[i]);
                found = 1;
                break;
            }
        }
        if (!found && uniqueStocks < 50) {
            strcpy(stockNames[uniqueStocks], products[i].stockName);
            stockCounts[uniqueStocks] = 1;
            stockValues[uniqueStocks] = calculateTotalValue(&products[i]);
            uniqueStocks++;
        }
    }

    printf("\n=== Product Statistics by Stock Name ===\n");
    printf("%-30s %-15s %-15s\n", "Stock Name", "Product Count", "Total Value");
    printf("---------------------------------------------------------------\n");
    
    for (i = 0; i < uniqueStocks; i++) {
        printf("%-30s %-15d %-15.2f\n", stockNames[i], stockCounts[i], stockValues[i]);
        grandTotal += stockValues[i];
    }
    
    printf("---------------------------------------------------------------\n");
    printf("Total Stocks: %d | Total Products: %d | Grand Total Value: %.2f\n", 
           uniqueStocks, productCount, grandTotal);
}

float calculateTotalStockValue(Product *products, int productCount) {
    int i;
    float total = 0.0;
    for (i = 0; i < productCount; i++) {
        total += calculateTotalValue(&products[i]);
    }
    return total;
}

// ========== FILE I/O IMPLEMENTATIONS ==========
void saveToFile(const char *filename, Product *products, int productCount) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error: Unable to open file for writing");
        return;
    }
    
    fwrite(&productCount, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
    printf("Data saved successfully to '%s' (%d products).\n", filename, productCount);
}

int loadFromFile(const char *filename, Product *products, int maxProducts) {
    int count;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Note: File '%s' not found. Starting with empty product list.\n", filename);
        return 0;
    }
    
    fread(&count, sizeof(int), 1, file);
    
    if (count > maxProducts) {
        printf("Warning: File contains %d products but maximum is %d. Loading first %d products.\n",
               count, maxProducts, maxProducts);
        count = maxProducts;
    }
    
    fread(products, sizeof(Product), count, file);
    fclose(file);
    printf("Data loaded successfully from '%s' (%d products).\n", filename, count);
    return count;
}

// ========== MENU IMPLEMENTATIONS ==========
void displayMenu() {
    printf("\n");
    printf("==============================================\n");
    printf("=   Product Management System - Main Menu   =\n");
    printf("==============================================\n");
    printf("=  1. Add Product                            =\n");
    printf("=  2. Delete Product                         =\n");
    printf("=  3. Update Product                         =\n");
    printf("=  4. View All Products                      =\n");
    printf("=  5. Search Product by ID                   =\n");
    printf("=  6. Search Product by Name                 =\n");
    printf("=  7. Sort Products                          =\n");
    printf("=  8. Statistics by Stock Name               =\n");
    printf("=  9. Save to File                           =\n");
    printf("=  10. Load from File                        =\n");
    printf("=  0. Exit                                   =\n");
    printf("==============================================\n");
}

void displaySortMenu() {
    printf("\n");
    printf("==============================================\n");
    printf("=          Sort Products - Submenu          =\n");
    printf("==============================================\n");
    printf("=  1. Sort by Name (A-Z)                     =\n");
    printf("=  2. Sort by Quantity (Ascending)           =\n");
    printf("=  3. Sort by Quantity (Descending)          =\n");
    printf("=  4. Sort by Price (Ascending)              =\n");
    printf("=  5. Sort by Price (Descending)             =\n");
    printf("=  0. Return to Main Menu                    =\n");
    printf("==============================================\n");
}

int getUserChoice() {
    int choice;
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return choice;
}

void returnChoice() {
    printf("\nPress Enter to continue...");
    getchar();
}

void exitProgram() {
    printf("\n==============================================\n");
    printf("=   Thank you for using the system!          =\n");
    printf("=   Goodbye!                                 =\n");
    printf("==============================================\n");
}

// ========== MAIN PROGRAM ==========

int main() {
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    char searchId[15], searchName[50];

    // Load existing data
    productCount = loadFromFile(DATA_FILE, products, MAX_PRODUCTS);

    do {
        displayMenu();
        choice = getUserChoice();

        switch (choice) {
            case 1: // Add Product
                addProduct(products, &productCount);
                break;

            case 2: // Delete Product
                printf("Enter Product ID to delete: ");
                scanf("%14s", searchId);
                getchar();
                deleteProduct(products, &productCount, searchId);
                break;

            case 3: // Update Product
                printf("Enter Product ID to update: ");
                scanf("%14s", searchId);
                getchar();
                updateProduct(products, productCount, searchId);
                break;

            case 4: // View All Products
                viewAllProducts(products, productCount);
                break;

            case 5: // Search by ID
                printf("Enter Product ID to search: ");
                scanf("%14s", searchId);
                getchar();
                {
                    Product *found = searchProductByID(searchId, products, productCount);
                    if (found != NULL) {
                        printf("\nProduct found:\n");
                        displayProduct(found);
                    } else {
                        printf("Product with ID '%s' not found.\n", searchId);
                    }
                }
                break;

            case 6: // Search by Name
                printf("Enter Product Name to search: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = 0;
                searchProductByName(searchName, products, productCount);
                break;

            case 7: // Sort Products
                {
                    int sortChoice;
                    do {
                        displaySortMenu();
                        sortChoice = getUserChoice();

                        switch (sortChoice) {
                            case 1:
                                sortProductsByName(products, productCount);
                                printf("Products sorted by name (A-Z).\n");
                                viewAllProducts(products, productCount);
                                break;
                            case 2:
                                sortProductsByQuantity(products, productCount, 1);
                                printf("Products sorted by quantity (ascending).\n");
                                viewAllProducts(products, productCount);
                                break;
                            case 3:
                                sortProductsByQuantity(products, productCount, 0);
                                printf("Products sorted by quantity (descending).\n");
                                viewAllProducts(products, productCount);
                                break;
                            case 4:
                                sortProductsByPrice(products, productCount, 1);
                                printf("Products sorted by price (ascending).\n");
                                viewAllProducts(products, productCount);
                                break;
                            case 5:
                                sortProductsByPrice(products, productCount, 0);
                                printf("Products sorted by price (descending).\n");
                                viewAllProducts(products, productCount);
                                break;
                            case 0:
                                printf("Returning to main menu...\n");
                                break;
                            default:
                                printf("Invalid choice! Please try again.\n");
                        }

                        if (sortChoice != 0) returnChoice();

                    } while (sortChoice != 0);
                }
                break;

            case 8: // Statistics by Stock
                statisticByStock(products, productCount);
                break;

            case 9: // Save to File
                saveToFile(DATA_FILE, products, productCount);
                break;

            case 10: // Load from File
                productCount = loadFromFile(DATA_FILE, products, MAX_PRODUCTS);
                break;

            case 0: // Exit
                saveToFile(DATA_FILE, products, productCount);
                exitProgram();
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

        if (choice != 0 && choice != 7) {
            returnChoice();
        }

    } while (choice != 0);

    return 0;
}