CC = gcc
CFLAGS = -Wall -g
OBJS = myShell.o execution.o error_handler.o builtins.o
TARGET = myShell

# ده السطر اللي كان متكرر، خليه مرة واحدة بس في أول الملف
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

myShell.o: myShell.c execution.h error_handler.h builtins.h
	$(CC) $(CFLAGS) -c myShell.c

execution.o: execution.c execution.h error_handler.h builtins.h
	$(CC) $(CFLAGS) -c execution.c

builtins.o: builtins.c builtins.h
	$(CC) $(CFLAGS) -c builtins.c

error_handler.o: error_handler.c error_handler.h
	$(CC) $(CFLAGS) -c error_handler.c

clean:
	rm -f *.o $(TARGET)
