CC	= gcc
CFLAGS	= -g -O2 -Wall
LDFLAGS	= -g

YACC	= bison -y
YFLAGS	=

LEX	= flex
LFLAGS	=

all:

test: main.o y.tab.o lex.yy.o symtab.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
lex.yy.o: y.tab.h
y.tab.o: symbol.h

lex.yy.c: test.l
	$(LEX) $(LFLAGS) $<

y.tab.c y.tab.h: test.y
	$(YACC) $(YFLAGS) -d $<

y.output: test.y
	$(YACC) $(YFLAGS) -d -v $<

clean:
	rm -f *~
	rm -f main.o y.tab.o lex.yy.o symtab.o type.o \
	      y.tab.h y.tab.c y.output \
	      lex.yy.c
