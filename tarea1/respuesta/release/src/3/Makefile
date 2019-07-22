CC      = gcc
CFLAGS  = -Wall -Wpedantic -std=gnu11
OPTIMIZ = -O2
INCLUDE = -I../common -I../3

NAME    = tarea-1-3

all: tarea

tarea:
	$(CC) *.c ../common/*.c -o $(NAME) $(CFLAGS) $(OPTIMIZ) $(INCLUDE)

clean:
	rm $(NAME)