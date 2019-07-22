# Compiler
CC			= @gcc
LANG_EXT	= c
HEADER_EXT	= h
OBJ_EXT		= o
FLAGS		= -Wall -Wextra -Wpedantic -std=gnu11
OPTIM		= -O2
OTHER		= 
SHARED_FLAG	= -fPIC -shared
LIBS		= 

# Commands
ECHO		= @echo
COPY		= @cp
COPY_FLAGS	= -R
MOVE		= @mv
MAKEDIR		= @mkdir
MKDIR_FLAGS	= -p
REMOVE		= @rm
RM_FLAGS	= -rf
INSTALL_COM	= @install

# SRC_FILES	= $(wildcard *.$(LANG_EXT))
# OBJ_O		= $(patsubst %.$(LANG_EXT), %.$(OBJ_EXT), $(SRC_FILES))
# OUT_FILES	= $(patsubst %.$(LANG_EXT), %, $(SRC_FILES))

SRC_FILES	= tarea-1-1.c tarea-1-2.c tarea-1-3.c
OBJ_O		= $(patsubst %.$(LANG_EXT), %.$(OBJ_EXT), $(SRC_FILES))
OUT_FILES	= $(patsubst %.$(LANG_EXT), %, $(SRC_FILES))

FLEX_FILES	= $(wildcard *.l)
FLEX_C		= $(patsubst %.l, flex_%.$(LANG_EXT), $(FLEX_FILES))

all: $(OBJ_O) $(OUT_FILES) $(FLEX_C)
	$(ECHO) Done

clean:
	$(REMOVE) $(FLEX_C) $(RM_FLAGS) $(OUT_FILES) $(OBJ_O)

flex_%.$(LANG_EXT): %.l
	$(ECHO) flex -o $@ $< 
	@flex -o $@ $<
	$(CC) $@ $(patsubst %.l, %.$(LANG_EXT), $<) -o $(patsubst %.l, %, $<) -std=gnu11 $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES) $(OTHER)

%.$(OBJ_EXT): %.$(LANG_EXT)
	$(ECHO) $(CC) $< -c 
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES) $(OTHER)

%: %.$(OBJ_EXT)
	$(ECHO) $(CC) $< -o
	$(CC) $< -o $@ $(FLAGS) $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES) $(OTHER)
