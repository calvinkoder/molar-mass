/*
From The C Programming Language
Section 6.6

Code copied from https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c

Modification:
strdup definition was removed, as it is included in <string.h>
*/

#ifndef DICT_H
#define DICT_H

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 201
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

#endif