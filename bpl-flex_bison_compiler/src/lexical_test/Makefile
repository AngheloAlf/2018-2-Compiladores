all: lexi
	gcc *.c -o lexical.out -std=gnu11

lexi:
	flex -o flex_lexical.c lexical.l

clean:
	rm *.out flex_*.c
