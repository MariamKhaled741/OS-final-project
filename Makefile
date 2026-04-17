CC = gcc
CFLAGS = -Wall -Wextra
TARGET = test_errors

all: $(TARGET)

$(TARGET): error_handler.o test_errors.o
	$(CC) -o $(TARGET) error_handler.o test_errors.o

error_handler.o: error.handler.c error_handler.h
	$(CC) $(CFLAGS) -c error_handler.c

test_errors.o: test_errors.c error_handler.h
	$(CC) $(CFLAGS) -c test_errors.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean

