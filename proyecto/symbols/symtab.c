/**
 * @file  symtab.h
 * @brief Symbol table for BPL
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "symbol.h"

/* Private parts */

#define NHASH   1009  /* Should be pŕime */

struct symtab {
	struct symbol s;

	struct symtab *hash_next, *scope_next;
};

static struct symtab *symtab[NHASH];

static struct scope {
	struct scope *next;
	struct symtab *list;
} *scope;

static unsigned int level = 0;

#define BITS	64    /* Wordsize */
#define SHIFT    7

__attribute__((const))
static unsigned hash(const char *str)
{
	unsigned long h = 0;

	while(*str)
		h = ((h << SHIFT) ^ (h >> (BITS - SHIFT))) ^ *str++;
	
	return h % NHASH;
}

/* Interface */

struct symbol *add(const char *name)
{
	unsigned int h = hash(name);
	struct symtab *p;

	for(p = symtab[h];
	    p && p->s.level == level && strcmp(name, p->s.name) != 0;
	    p = p->hash_next)
		;

	if(p && p->s.level == level) {
		/* Found a previous definition of the name */
		return NULL;
	}
	else {
		/* No previous definition, add it */
		p = calloc(1, sizeof(*p));
		/* Name, type, level */
		p->s.name = name;
		p->s.level = level;
		/* Hash list... */
		p->hash_next = symtab[h];
		symtab[h] = p;
		/* ... and level list */
		p->scope_next = scope->list;
		scope->list = p;
		return &p->s;
	}
}

struct symbol *lookup(const char *name)
{
	for(struct symtab *p = symtab[hash(name)]; p; p = p->hash_next)
		if(strcmp(name, p->s.name) == 0)
			return &p->s;
	return NULL;
}

void enter_scope()
{
	struct scope *p;

	level++;
	p = calloc(1, sizeof(*p));
	p->next = scope;
	scope = p;
}

static void free_symtab(struct symtab *sp)
{
	unsigned int h = hash(sp->s.name);

	free((void *)sp->s.name);
	symtab[h] = symtab[h]->hash_next;
	free(sp);
}

void leave_scope()
{
	/* Clean out any entries at the level we are leaving */
        struct symtab *p = scope->list;
	while(p) {
		struct symtab *q = p->scope_next;
		free_symtab(p);
		p = q;
	}
			
	/* Delete the entry for the level */
	struct scope *r = scope;
	scope = scope->next;
	free(r);

	level--;
}

/** Testing/debugging **/

#include <stdio.h>

void dump_symtab(void)
{
	printf("Current level: %d\n", level);
	printf("By level:\n");
	int lvl = level;
	for(struct scope *p = scope; p; p = p->next) {
		printf("Level %d:\n", lvl--);
		for(struct symtab *q = p->list; q; q = q->scope_next) {
			dump_symbol(&q->s);
		}
	}

	struct symtab *p;
        printf("\nBy hash chain:\n");
	for(int i = 0; i < NHASH; i++) {
		if(symtab[i]) {
			printf("Hash %d\n", i);
			for(p = symtab[i]; p; p = p->hash_next)
				dump_symbol(&p->s);
		}
	}

}
