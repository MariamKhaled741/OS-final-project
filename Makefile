CC = gcc

CFLAGS = -Wall -g


SRCS = myShell.c execution.c builtins.c error_handler.c

OBJS = $(SRCS:.c=.o)

myShell: $(OBJS)

	$(CC) $(CFLAGS) -o myShell $(OBJS)

%.o: %.c

	$(CC) $(CFLAGS) -c $<

clean:

	rm -f *.o myShell
