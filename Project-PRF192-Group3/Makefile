CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRC = src/main.c src/menu.c src/product.c src/crud.c src/search.c src/sort.c src/statistics.c src/fileio.c src/validation.c
OBJ = $(SRC:.c=.o)
TARGET = product_management

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean