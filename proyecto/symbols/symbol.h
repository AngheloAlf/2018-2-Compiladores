/**
 * @file  symbol.h
 *¨@brief Symbol table entry for BPL
 */

#ifndef SYMBOL_H
#define SYMBOL_H

struct symbol {
	const char *name;
	unsigned int level;
};

struct symbol *add(const char *name);
struct symbol *lookup(const char *name);

void enter_scope(void), leave_scope(void);

void dump_symtab(void);

inline void dump_symbol(const struct symbol *sp)
{
	printf("Name: \"%s\", level: %d\n",
	       sp->name, sp->level);
}

#endif
