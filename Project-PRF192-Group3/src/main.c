#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "crud.h"
#include "search.h"
#include "sort.h"
#include "statistics.h"
#include "fileio.h"
#include "validation.h"

void displayMenu();
int getUserChoice();

int main() {
    int choice;

    // Load existing product data from file
    loadFromFile();

    do {
        displayMenu();
        choice = getUserChoice();

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                deleteProduct();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                viewAllProducts();
                break;
            case 5:
                searchProductByID();
                break;
            case 6:
                searchProductByName();
                break;
            case 7:
                sortProductsByName();
                break;
            case 8:
                sortProductsByQuantity();
                break;
            case 9:
                sortProductsByPrice();
                break;
            case 10:
                statisticByStock();
                break;
            case 11:
                saveToFile();
                break;
            case 0:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}