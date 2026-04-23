CC = gcc
CFLAGS = -Wall -g
OBJS = myShell.o execution.o error_handler.o builtins.o signals.o
TARGET = myShell

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

myShell.o: myShell.c execution.h error_handler.h builtins.h signals.h
	$(CC) $(CFLAGS) -c myShell.c

signals.o: signals.c signals.h
	$(CC) $(CFLAGS) -c signals.c

execution.o: execution.c execution.h error_handler.h builtins.h
	$(CC) $(CFLAGS) -c execution.c

builtins.o: builtins.c builtins.h
	$(CC) $(CFLAGS) -c builtins.c

error_handler.o: error_handler.c error_handler.h
	$(CC) $(CFLAGS) -c error_handler.c

clean:
	rm -f *.o $(TARGET)
