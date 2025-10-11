#include <stdio.h>
#include "menu.h"

void displayMenu() {
    printf("=== Product Management System ===\n");
    printf("1. Add Product\n");
    printf("2. Delete Product\n");
    printf("3. Update Product\n");
    printf("4. View All Products\n");
    printf("5. Search Product by ID\n");
    printf("6. Search Product by Name\n");
    printf("7. Sort Products\n");
    printf("8. Statistics by Stock Name\n");
    printf("9. Save to File\n");
    printf("10. Load from File\n");
    printf("0. Exit\n");
    printf("=================================\n");
}

int getUserChoice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}