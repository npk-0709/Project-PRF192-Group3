CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -I./src
SRC = src/main.c
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