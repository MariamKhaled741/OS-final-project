# Compiler to use
CC = gcc

# Compiler flags: -Wall for all warnings, -g for debugging info
CFLAGS = -Wall -g

# Source files:
# Note: builtins.c is excluded for now to avoid 'multiple definition' 
# errors since functions are also defined in myShell.c
SRCS = myShell.c execution.c error_handler.c 

# Object files (automatically derived from SRCS)
OBJS = $(SRCS:.c=.o)

# Name of the final executable
TARGET = myShell

# Default rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f *.o $(TARGET)
