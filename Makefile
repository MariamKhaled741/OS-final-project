CC = gcc
CFLAGS = -Wall -g

all: myShell

myShell: myShell.o error_handler.o
	$(CC) $(CFLAGS) -o myShell myShell.o error_handler.o

myShell.o: myShell.c error_handler.h
	$(CC) $(CFLAGS) -c myShell.c

error_handler.o: error_handler.c error_handler.h
	$(CC) $(CFLAGS) -c error_handler.c

clean:
	rm -f *.o myShell
