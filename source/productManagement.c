#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATA_FILE "products.txt"
#define MAX_PRODUCTS 100
#define MAX_ID_LENGTH 15
#define MAX_NAME_LENGTH 50
#define MAX_STOCK_NAME_LENGTH 30

typedef struct
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    int quantity;
    char stockName[MAX_STOCK_NAME_LENGTH];
    float unitPrice;
} Product;

#define VALIDATE_PRODUCT_ID 1
#define VALIDATE_PRODUCT_NAME 2
#define VALIDATE_QUANTITY 3
#define VALIDATE_STOCK_NAME 4
#define VALIDATE_UNIT_PRICE 5

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n');
}

int validateInput(int type, const void *value)
{
    switch (type)
    {
    case VALIDATE_PRODUCT_ID:
    {
        const char *id = (const char *)value;
        if (strlen(id) == 0 || strlen(id) > 14)
        {
            printf("Invalid Product ID. Must be 1-14 characters.\n");
            return 0;
        }
        return 1;
    }

    case VALIDATE_PRODUCT_NAME:
    {
        const char *name = (const char *)value;
        if (strlen(name) == 0 || strlen(name) > 49)
        {
            printf("Invalid Product Name. Must be 1-49 characters.\n");
            return 0;
        }
        return 1;
    }

    case VALIDATE_QUANTITY:
    {
        int quantity = *(const int *)value;
        if (quantity < 0)
        {
            printf("Invalid Quantity. Cannot be negative.\n");
            return 0;
        }
        return 1;
    }

    case VALIDATE_STOCK_NAME:
    {
        const char *stockName = (const char *)value;
        if (strlen(stockName) == 0 || strlen(stockName) > 29)
        {
            printf("Invalid Stock Name. Must be 1-29 characters.\n");
            return 0;
        }
        return 1;
    }

    case VALIDATE_UNIT_PRICE:
    {
        float unitPrice = *(const float *)value;
        if (unitPrice < 0)
        {
            printf("Invalid Unit Price. Cannot be negative.\n");
            return 0;
        }
        return 1;
    }

    default:
        printf("Unknown validation type.\n");
        return 0;
    }
}
void displayProduct(Product p)
{
    float totalValue = p.quantity * p.unitPrice;
    printf("| %-10s | %-24s | %-8d | %-15s | %-13.2f VND | %-15.2f VND |\n",
           p.id, p.name, p.quantity, p.stockName, p.unitPrice, totalValue);
}
// chuyen chuoi thanh chuoi thuong
void toLowerStr(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = tolower(src[i]);
        i++;
    }
    dest[i] = '\0';
}

void searchProductByID(int productCount, Product products[])
{
    int i, found = 0;
    char searchID[MAX_ID_LENGTH];

    if (productCount == 0)
    {
        printf("No products available to search.\n");
        return;
    }

    printf("Enter product ID to search: ");
    scanf("%14s", searchID);
    // xoa con lai trong buffer
    scanf("%*[^\n]");
    getchar();

    for (i = 0; i < productCount; i++)
    {
        if (strcmp(products[i].id, searchID) == 0)
        {
            printf("\nPRODUCT FOUND!\n");
            printf("| %-10s | %-24s | %-8s | %-15s | %-15s | %-17s |\n",
                   "ID", "Name", "Quantity", "Stock Name", "Unit Price", "Total Value");
            printf("====================================================================================================\n");
            displayProduct(products[i]);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with ID '%s' not found.\n", searchID);
    }
}

void searchProductByName(int productCount, Product products[])
{
    int i, found = 0;
    char searchName[MAX_NAME_LENGTH];
    char lowerName[MAX_NAME_LENGTH];
    char lowerProductName[MAX_NAME_LENGTH];

    if (productCount == 0)
    {
        printf("No products available to search.\n");
        return;
    }

    printf("Enter product name to search: ");
    scanf(" %49[^\n]", searchName);
    clearInputBuffer();

    searchName[strcspn(searchName, "\n")] = '\0';
    toLowerStr(lowerName, searchName);

    printf("\n=== Products matching '%s' ===\n", searchName);
    printf("| %-10s | %-24s | %-8s | %-15s | %-15s | %-17s |\n",
           "ID", "Name", "Quantity", "Stock Name", "Unit Price", "Total Value");
    printf("====================================================================================================\n");

    for (i = 0; i < productCount; i++)
    {
        toLowerStr(lowerProductName, products[i].name);

        if (strstr(lowerProductName, lowerName) != NULL)
        {
            displayProduct(products[i]);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No products found matching '%s'.\n", searchName);
    }
    else
    {
        printf("Total: %d product(s) found.\n", found);
    }
}

Product inputProductInfo(void)
{
    Product p;
    int valid = 0;
    int c;
    do
    {
        printf("Enter product ID: ");
        if (scanf(" %14s", p.id) != 1)
        {
            clearInputBuffer();
            printf("Error reading input.\n");
            continue;
        }
        clearInputBuffer();

        valid = validateInput(VALIDATE_PRODUCT_ID, p.id);
    } while (!valid);

    do
    {
        printf("Enter product name: ");
        if (scanf("%49[^\n]", p.name) != 1)
        {
            clearInputBuffer();
            printf("Error reading input.\n");
            continue;
        }
        clearInputBuffer();

        valid = validateInput(VALIDATE_PRODUCT_NAME, p.name);
    } while (!valid);

    do
    {
        printf("Enter quantity: ");
        if (scanf("%d", &p.quantity) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            valid = 0;
            continue;
        }
        clearInputBuffer();

        valid = validateInput(VALIDATE_QUANTITY, &(p.quantity));
    } while (!valid);

    do
    {
        printf("Enter stock name: ");
        if (scanf(" %29[^\n]", p.stockName) != 1)
        {
            clearInputBuffer();

            printf("Error reading input.\n");
            continue;
        }
        clearInputBuffer();

        valid = validateInput(VALIDATE_STOCK_NAME, p.stockName);
    } while (!valid);

    do
    {
        printf("Enter unit price: ");
        if (scanf("%f", &p.unitPrice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            valid = 0;
            continue;
        }
        clearInputBuffer();

        valid = validateInput(VALIDATE_UNIT_PRICE, &(p.unitPrice));
    } while (!valid);

    return p;
}

void addProduct(Product *products, int *count)
{

    if (*count >= MAX_PRODUCTS)
    {
        printf("You can't add more products. The list has reached its limit (%d).\n", MAX_PRODUCTS);
        return;
    }

    Product newProduct;
    printf("\n=== ADD NEW PRODUCT ===\n");
    newProduct = inputProductInfo();

    for (int i = 0; i < *count; i++)
    {
        if (strcmp(products[i].id, newProduct.id) == 0) // so sanh xem id co trung khong
        {
            printf("A product with this ID already exists.\n");
            return;
        }
    }

    products[*count] = newProduct;
    (*count)++; // Tang so luong san pham len 1
    printf("Product added successfully. Total products: %d\n", *count);
}

void deleteProduct(Product *products, int *count, const char *id)
{
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            printf("Product with ID %s found. Deleting...\n", id);
            displayProduct(products[i]);

            for (int j = i; j < *count - 1; j++)
            {
                products[j] = products[j + 1];
            }
            (*count)--; // giam so luong san pham di 1
            printf("Product deleted successfully. Total products: %d\n", *count);
            return;
        }
    }
    printf("Product with ID %s not found.\n", id);
}

void updateProduct(Product *products, int *count, const char *id)
{
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            printf("Current product information:\n");
            displayProduct(products[i]);

            printf("\nEnter new information:\n");
            char oldID[MAX_ID_LENGTH];
            strcpy(oldID, products[i].id); // copy id cu de giu nguyen

            Product newData = inputProductInfo(); // nhap thong tin moi
            products[i] = newData;
            strcpy(products[i].id, oldID);
            printf("Product updated successfully.\n");
            return;
        }
    }
    printf("Product with ID %s not found.\n", id);
}

void viewAllProducts(Product *products, int count)
{
    if (count == 0)
    {
        printf("No products available.\n");
        return;
    }

    printf("\n=== ALL PRODUCTS (%d products) ===\n", count);
    printf("| %-10s | %-24s | %-8s | %-15s | %-15s | %-17s |\n",
           "ID", "Name", "Quantity", "Stock Name", "Unit Price", "Total Value");
    printf("==========================================================================================================\n");

    for (int i = 0; i < count; i++)
    {
        displayProduct(products[i]);
    }
    printf("==========================================================================================================\n");
}

float calculateTotalValue(Product p)
{
    return p.quantity * p.unitPrice;
}

float calculateTotalStockValue(Product *products, int productCount)
{
    float total = 0.0;
    for (int i = 0; i < productCount; i++)
    {
        total += calculateTotalValue(products[i]);
    }
    return total;
}

void statisticsByStock(Product *products, int productCount)
{
    if (productCount == 0)
    {
        printf("No products available for statistics.\n");
        return;
    }

    printf("\n=== STATISTICS BY STOCK ===\n");

    int stockCount = 0;
    char uniqueStocks[MAX_PRODUCTS][MAX_STOCK_NAME_LENGTH];
    int counts[MAX_PRODUCTS] = {0};

    for (int i = 0; i < productCount; i++)
    {
        int found = 0;
        for (int j = 0; j < stockCount; j++)
        {
            if (strcmp(products[i].stockName, uniqueStocks[j]) == 0)
            {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(uniqueStocks[stockCount], products[i].stockName);
            counts[stockCount] = 1;
            stockCount++;
        }
    }

    printf("| %-15s | %-8s |\n", "Stock Name", "Count");
    printf("-------------------------------\n");
    for (int i = 0; i < stockCount; i++)
    {
        printf("| %-15s | %-8d |\n", uniqueStocks[i], counts[i]);
    }
    printf("-------------------------------\n");
}


void sortProductsByName(Product *products, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(products[j].name, products[j + 1].name) > 0)
            {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}
// dung thuat toan bubble sort de sap xep san pham theo so luong
void sortProductsByQuantity(Product *products, int count, int ascending)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if ((ascending && products[j].quantity > products[j + 1].quantity) ||
                (!ascending && products[j].quantity < products[j + 1].quantity))
            {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void sortProductsByPrice(Product *products, int count, int ascending)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if ((ascending && products[j].unitPrice > products[j + 1].unitPrice) ||
                (!ascending && products[j].unitPrice < products[j + 1].unitPrice))
            {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void saveToFile(const char *filename, Product *products, int productCount)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d\n", productCount);

    for (int i = 0; i < productCount; i++)
    {
        fprintf(file, "%s\n", products[i].id);
        fprintf(file, "%s\n", products[i].name);
        fprintf(file, "%d\n", products[i].quantity);
        fprintf(file, "%s\n", products[i].stockName);
        fprintf(file, "%.2f\n", products[i].unitPrice);
    }

    fclose(file);
    printf("Data saved successfully to %s (%d products).\n", filename, productCount);
}

int loadFromFile(const char *filename, Product *products, int maxProducts)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found. Starting with empty product list.\n");
        return 0;
    }

    int count;
    if (fscanf(file, "%d\n", &count) != 1)
    {
        printf("Error reading file format.\n");
        fclose(file);
        return 0;
    }

    if (count > maxProducts)
    {
        printf("Warning: File contains %d products but maximum is %d.\n", count, maxProducts);
        count = maxProducts;
    }

    for (int i = 0; i < count; i++)
    {
        if (fgets(products[i].id, MAX_ID_LENGTH, file) == NULL)
            break;
        products[i].id[strcspn(products[i].id, "\n")] = '\0';

        if (fgets(products[i].name, MAX_NAME_LENGTH, file) == NULL)
            break;
        products[i].name[strcspn(products[i].name, "\n")] = '\0';

        if (fscanf(file, "%d\n", &products[i].quantity) != 1)
            break;

        if (fgets(products[i].stockName, MAX_STOCK_NAME_LENGTH, file) == NULL)
            break;
        products[i].stockName[strcspn(products[i].stockName, "\n")] = '\0';

        if (fscanf(file, "%f\n", &products[i].unitPrice) != 1)
            break;
    }

    fclose(file);
    printf("Data loaded successfully from %s (%d products).\n", filename, count);
    return count;
}

void displayMenu()
{
    printf("\n");
    printf("==============================================\n");
    printf("=   Product Management System - Main Menu    =\n");
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
    printf("=  10.Load from File                         =\n");
    printf("=  0. Exit                                   =\n");
    printf("==============================================\n");
}

void displaySortMenu()
{
    printf("\n");
    printf("==============================================\n");
    printf("=          Sort Products - Submenu           =\n");
    printf("==============================================\n");
    printf("=  1. Sort by Name (A-Z)                     =\n");
    printf("=  2. Sort by Quantity (Ascending)           =\n");
    printf("=  3. Sort by Quantity (Descending)          =\n");
    printf("=  4. Sort by Price (Ascending)              =\n");
    printf("=  5. Sort by Price (Descending)             =\n");
    printf("=  0. Return to Main Menu                    =\n");
    printf("==============================================\n");
}

int getUserChoice()
{
    int choice;
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        return -1;
    }
    while (getchar() != '\n')
        ;
    return choice;
}

void returnChoice()
{
    printf("\nPress Enter to continue...");
    getchar();
}

void exitProgram()
{
    printf("\n==============================================\n");
    printf("=   Thank you for using the system!          =\n");
    printf("=   Goodbye!                                 =\n");
    printf("==============================================\n");
}

int main()
{
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    char searchId[15];

    productCount = loadFromFile(DATA_FILE, products, MAX_PRODUCTS);

    do
    {
        displayMenu();
        choice = getUserChoice();

        switch (choice)
        {
        case 1:
            addProduct(products, &productCount);
            break;

        case 2:
            printf("Enter Product ID to delete: ");
            scanf("%14s", searchId);
            getchar();
            deleteProduct(products, &productCount, searchId);
            break;

        case 3:
            printf("Enter Product ID to update: ");
            scanf("%14s", searchId);
            getchar();
            updateProduct(products, &productCount, searchId);
            break;

        case 4:
            viewAllProducts(products, productCount);
            break;

        case 5:
            searchProductByID(productCount, products);
            break;

        case 6:
            searchProductByName(productCount, products);
            break;

        case 7:
        {
            int sortChoice;
            do
            {
                displaySortMenu();
                sortChoice = getUserChoice();

                switch (sortChoice)
                {
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

                if (sortChoice != 0)
                    returnChoice();

            } while (sortChoice != 0);
        }
        break;

        case 8:
            statisticsByStock(products, productCount);
            break;

        case 9:
            saveToFile(DATA_FILE, products, productCount);
            break;

        case 10:
            productCount = loadFromFile(DATA_FILE, products, MAX_PRODUCTS);
            break;

        case 0:
            saveToFile(DATA_FILE, products, productCount);
            exitProgram();
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }

        if (choice != 0 && choice != 7)
        {
            returnChoice();
        }

    } while (choice != 0);

    return 0;
}