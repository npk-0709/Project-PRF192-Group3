# Project PRF192 - Product Management System

## Overview
This project is a console-based application for managing product records. It allows users to add, edit, delete, and view products, as well as perform search and sorting operations. The application is designed to be modular, with separate files for different functionalities, ensuring maintainability and scalability.

## Project Structure
```
Project-PRF192-Group3
├── src
│   ├── main.c          # Entry point of the application
│   ├── menu.c          # Menu system implementation
│   ├── menu.h          # Menu system header
│   ├── product.c       # Product management functions
│   ├── product.h       # Product struct and declarations
│   ├── crud.c          # CRUD operations for products
│   ├── crud.h          # CRUD functions declarations
│   ├── search.c        # Search functionalities
│   ├── search.h        # Search functions declarations
│   ├── sort.c          # Sorting functions
│   ├── sort.h          # Sorting functions declarations
│   ├── statistics.c     # Product statistics functions
│   ├── statistics.h     # Statistics functions declarations
│   ├── fileio.c        # File input/output operations
│   ├── fileio.h        # File I/O functions declarations
│   ├── validation.c     # Input validation functions
│   └── validation.h     # Validation functions declarations
├── data
│   └── products.dat    # Binary file for storing product data
├── Makefile            # Build instructions
└── README.md           # Project documentation
```

## Features
- **Product Management**: Add, edit, delete, and view product records.
- **Search and Sorting**: Search products by ID or name and sort them by various criteria.
- **Statistics**: Generate statistics on products by stock name.
- **File I/O**: Load and save product data from/to files.
- **Input Validation**: Ensure data integrity through input validation.

## Setup Instructions
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Use the provided `Makefile` to compile the project:
   ```
   make
   ```
4. Run the application:
   ```
   ./main
   ```

## Usage Guidelines
- Upon starting the application, the user will be presented with a menu to choose from various options related to product management.
- Follow the prompts to add, edit, delete, or view products.
- Use the search functionality to find specific products.
- The application will save data to `data/products.dat` for persistence.

## Contribution
Contributions to the project are welcome. Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.