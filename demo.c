// Product Structure Definition
struct Product {
    char id[20];       // Product ID
    char name[50];     // Product Name
    int quantity;      // Quantity in stock
    char stockName[50]; // Stock name
    float unitPrice;   // Unit price
};

// Assume a global list of products, e.g., an array or dynamic list
#define MAX_PRODUCTS 100
struct Product productList[MAX_PRODUCTS];
int numProducts = 0; // Current number of products

// Menu & Main Flow

void displayMenu() {
    // Display the main menu options
    printf("Main Menu:\n");
    printf("1. Add new product\n");
    printf("2. Delete product by ID\n");
    printf("3. Update product information\n");
    printf("4. View all products\n");
    printf("5. Search product by ID\n");
    printf("6. Search product by name\n");
    printf("7. Sort products by name\n");
    printf("8. Sort products by quantity\n");
    printf("9. Sort products by price\n");
    printf("10. Calculate total stock value\n");
    printf("11. Statistics by stock\n");
    printf("12. Save to file\n");
    printf("13. Load from file\n");
    printf("14. Exit\n");
}

int getUserChoice() {
    // Get and validate user input for menu choice
    int choice;
    scanf("%d", &choice);
    while (choice < 1 || choice > 14) {
        printf("Invalid choice. Please enter a number from 1 to 14.\n");
        scanf("%d", &choice);
    }
    return choice;
}

void returnChoice() {
    // Return to previous menu (simulate by redisplaying menu)
    printf("Returning to previous menu...\n");
    displayMenu(); // Or redirect to parent menu if nested
}

void exitProgram() {
    // Exit the program
    printf("Exiting program...\n");
    exit(0); // Terminate execution
}

// Product CRUD

void addProduct() {
    // Add a new product to the list
    if (numProducts >= MAX_PRODUCTS) {
        printf("Product list is full!\n");
        return;
    }
    struct Product newProduct;
    inputProductInfo(&newProduct); // Input details
    productList[numProducts] = newProduct;
    numProducts++;
    printf("Product added successfully.\n");
}

void deleteProduct() {
    // Delete product by ID
    char id[20];
    printf("Enter product ID to delete: ");
    scanf("%s", id);
    int index = -1;
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(productList[i].id, id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }
    // Shift elements to remove the product
    for (int i = index; i < numProducts - 1; i++) {
        productList[i] = productList[i + 1];
    }
    numProducts--;
    printf("Product deleted successfully.\n");
}

void updateProduct() {
    // Update product information by ID
    char id[20];
    printf("Enter product ID to update: ");
    scanf("%s", id);
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(productList[i].id, id) == 0) {
            inputProductInfo(&productList[i]); // Re-input details
            printf("Product updated successfully.\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void viewAllProducts() {
    // Display all products
    if (numProducts == 0) {
        printf("No products available.\n");
        return;
    }
    for (int i = 0; i < numProducts; i++) {
        printf("ID: %s, Name: %s, Quantity: %d, Stock: %s, Price: %.2f\n",
               productList[i].id, productList[i].name, productList[i].quantity,
               productList[i].stockName, productList[i].unitPrice);
    }
}

// Sort and Search

int searchProductByID(char* id) {
    // Search for product by ID, return index or -1 if not found
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(productList[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void searchProductByName() {
    // Search products by (part of) name, case insensitive
    char name[50];
    printf("Enter name or part of name to search: ");
    scanf("%s", name);
    // Convert to lowercase for case insensitivity (simplified)
    // Assume strlwr or manual conversion
    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        // Simplified case-insensitive comparison
        if (strstr(strlwr(productList[i].name), strlwr(name)) != NULL) {
            printf("ID: %s, Name: %s, Quantity: %d, Stock: %s, Price: %.2f\n",
                   productList[i].id, productList[i].name, productList[i].quantity,
                   productList[i].stockName, productList[i].unitPrice);
            found = 1;
        }
    }
    if (!found) {
        printf("No products found.\n");
    }
}

void sortProductsByName() {
    // Sort products alphabetically by name (bubble sort example)
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = 0; j < numProducts - i - 1; j++) {
            if (strcmp(productList[j].name, productList[j + 1].name) > 0) {
                // Swap
                struct Product temp = productList[j];
                productList[j] = productList[j + 1];
                productList[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by name.\n");
}

void sortProductsByQuantity(int ascending) {
    // Sort by quantity (ascending if 1, descending if 0)
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = 0; j < numProducts - i - 1; j++) {
            if ((ascending && productList[j].quantity > productList[j + 1].quantity) ||
                (!ascending && productList[j].quantity < productList[j + 1].quantity)) {
                // Swap
                struct Product temp = productList[j];
                productList[j] = productList[j + 1];
                productList[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by quantity.\n");
}

void sortProductsByPrice(int ascending) {
    // Sort by unit price (ascending if 1, descending if 0)
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = 0; j < numProducts - i - 1; j++) {
            if ((ascending && productList[j].unitPrice > productList[j + 1].unitPrice) ||
                (!ascending && productList[j].unitPrice < productList[j + 1].unitPrice)) {
                // Swap
                struct Product temp = productList[j];
                productList[j] = productList[j + 1];
                productList[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by price.\n");
}

// Product Management

void inputProductInfo(struct Product* p) {
    // Input all details of a product
    printf("Enter ID: ");
    scanf("%s", p->id);
    printf("Enter Name: ");
    scanf("%s", p->name);
    printf("Enter Quantity: ");
    scanf("%d", &p->quantity);
    printf("Enter Stock Name: ");
    scanf("%s", p->stockName);
    printf("Enter Unit Price: ");
    scanf("%f", &p->unitPrice);
    validateInput(p); // Validate the input
}

float calculateTotalValue() {
    // Calculate total stock value (sum of quantity * unit price)
    float total = 0.0;
    for (int i = 0; i < numProducts; i++) {
        total += productList[i].quantity * productList[i].unitPrice;
    }
    return total;
}

void statisticByStock() {
    // Count number of products per stock name
    // Assume using a map or array for unique stocks (simplified)
    printf("Statistics by stock:\n");
    // For each unique stockName, count occurrences
    // Example: Loop and group (inefficient but pseudocode)
    for (int i = 0; i < numProducts; i++) {
        int count = 1;
        for (int j = i + 1; j < numProducts; j++) {
            if (strcmp(productList[i].stockName, productList[j].stockName) == 0) {
                count++;
            }
        }
        printf("Stock %s: %d products\n", productList[i].stockName, count);
        // Skip duplicates in output (not shown)
    }
}

// File I/O

void saveToFile() {
    // Save data to file
    FILE* file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s %s %d %s %.2f\n",
                productList[i].id, productList[i].name, productList[i].quantity,
                productList[i].stockName, productList[i].unitPrice);
    }
    fclose(file);
    printf("Data saved to file.\n");
}

void loadFromFile() {
    // Load data from file
    FILE* file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    numProducts = 0;
    while (fscanf(file, "%s %s %d %s %f",
                  productList[numProducts].id, productList[numProducts].name,
                  &productList[numProducts].quantity, productList[numProducts].stockName,
                  &productList[numProducts].unitPrice) != EOF) {
        numProducts++;
    }
    fclose(file);
    printf("Data loaded from file.\n");
}

// Validation & Exception Handling

void validateInput(struct Product* p) {
    // Input validation (example: check non-negative quantity and price)
    if (p->quantity < 0) {
        printf("Quantity cannot be negative. Setting to 0.\n");
        p->quantity = 0;
    }
    if (p->unitPrice < 0) {
        printf("Price cannot be negative. Setting to 0.\n");
        p->unitPrice = 0.0;
    }
    // Add more validations as needed (e.g., unique ID check)
}