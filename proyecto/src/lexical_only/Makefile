all: lexi
	echo "Done"


lexi:
	flex -o flex_lexical.c lexical.l
	gcc *.c -o lexical -std=gnu11

sintac:
	bison -o bison_sintactical.c -d sintactical.y


clean:
	rm lexical flex_lexical.c
