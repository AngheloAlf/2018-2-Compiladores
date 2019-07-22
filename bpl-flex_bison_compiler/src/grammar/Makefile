FLAGS = -Wfatal-errors -Wshadow -Wpedantic -std=gnu11
RELEASE_FLAGS = -O2 -DNDEBUG
DEBUG_FLAGS = -g3 -Og

all: debug
	@echo OK

release: bpl_lib sintac lexi
	gcc *.c temp/*.c asm_gen/*.c -o out/grammar.out -Ilibs -I. $(RELEASE_FLAGS) $(FLAGS)

debug: bpl_lib sintac lexi debug_obj
	gcc *.o temp/*.c -o out/grammar.out -Ilibs -I. $(DEBUG_FLAGS) $(FLAGS)

debug_obj:
	gcc *.c asm_gen/*.c -c -Ilibs -I. $(DEBUG_FLAGS) $(FLAGS) -Wall -Wextra

lexi: tempfolder
	flex -o temp/flex_lexical.c lexical.l

sintac: tempfolder
	bison -v -o temp/bison_sintactical.c -d sintactical.y

tempfolder:
	mkdir -p temp out

bpl_lib: tempfolder
	cd bpllib && gcc *.s -c
	ar -cvq out/libbplstd.a bpllib/*.o

clean:
	rm -rf *.out flex_*.c bison_*.c bison_*.h *.output *.o temp/ out/ bpllib/*.o bpllib/*.a

