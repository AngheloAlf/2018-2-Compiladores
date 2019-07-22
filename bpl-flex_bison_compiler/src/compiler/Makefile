FLAGS = -Wfatal-errors -Wshadow -Wpedantic -std=gnu11
RELEASE_FLAGS = -O2 -DNDEBUG
DEBUG_FLAGS = -g3 -Og
NAME = compiler.out
INCLUDE_PATHS = -I. -Ilibs/ -Iassembly/ -Iast/ -Istructures/

all: debug
	@echo OK

release: bpl_lib sintac lexi
	gcc *.c temp/*.c structures/*.c ast/*.c assembly/*.c -o out/$(NAME) $(INCLUDE_PATHS) $(RELEASE_FLAGS) $(FLAGS)

debug: bpl_lib sintac lexi debug_obj
	gcc *.o temp/*.c -o out/$(NAME) $(INCLUDE_PATHS) $(DEBUG_FLAGS) $(FLAGS)

debug_obj:
	gcc *.c structures/*.c ast/*.c assembly/*.c -c $(INCLUDE_PATHS) $(DEBUG_FLAGS) $(FLAGS) -Wall -Wextra

lexi: tempfolder
	flex -o temp/flex_lexical.c parser/lexical.l

sintac: tempfolder
	bison -v -o temp/bison_sintactical.c -d parser/sintactical.y

tempfolder:
	mkdir -p temp out

bpl_lib: tempfolder
	cd bpllib && gcc *.s -c
	ar -cvq out/libbplstd.a bpllib/*.o

clean:
	rm -rf *.o temp/ out/
