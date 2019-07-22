CC      = gcc
CFLAGS  = -Wall -Wpedantic -std=gnu11
OPTIMIZ = -O2
INCLUDE = 

NAME    = tarea-1-4

all: tarea

tarea:
	flex -o flex_$(NAME).c $(NAME).l
	$(CC) *.c -o $(NAME) $(CFLAGS) $(OPTIMIZ) $(INCLUDE)

clean:
	rm $(NAME) flex_$(NAME).c