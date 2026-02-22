# Makefile for libio (static + shared)

CC = clang
AR = ar
CFLAGS = -Wall -Wextra -Werror -fPIC
LDFLAGS = -shared

SRC_DIR = src
INC_DIR = src/include

# Source and header files
SRC = $(SRC_DIR)/libio.c
OBJ = $(SRC_DIR)/libio.o
HEADER = $(INC_DIR)/libio.h

# Targets
all: libio.a libio.so

# Static library
libio.a: $(OBJ)
	$(AR) rcs $@ $^

# Shared library
libio.so: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile object file
$(OBJ): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean build files
clean:
	rm -f $(SRC_DIR)/*.o *.a *.so

.PHONY: all clean
