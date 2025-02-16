# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
PROD_CFLAGS = -Wall -Wextra -std=c11 -O2

# Target executable name
TARGET = region_allocator

# Source files
LIB_SRCS = arena.c
MAIN_SRCS = main.c

# Object files
LIB_OBJS = $(LIB_SRCS:.c=.o)
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(MAIN_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJS) $(LIB_OBJS)

# Compilation step for main and library files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(LIB_OBJS) $(MAIN_OBJS)

# Run the program
run: $(TARGET)
	./$(TARGET)

prod: CFLAGS = $(PROD_CFLAGS)
prod: clean $(TARGET)

.PHONY: all clean run

