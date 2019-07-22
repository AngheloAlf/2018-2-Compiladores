all: sintac lexi
	gcc *.c -o grammar -std=gnu11


lexi:
	flex -o flex_lexical.c lexical.l

sintac:
	bison -v -o bison_sintactical.c -d sintactical.y


clean:
	rm -f grammar flex_lexical.c bison_sintactical.c bison_sintactical.h
