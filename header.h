#include <stdio.h>
#include <stdlib.h>

// Tim
typedef struct tim
{
    char *namaTim;
    struct tim *next, *prev;
} Tim;

// Menyimpan grup
typedef struct group
{
    char *namaGroup;
    Tim *pointer;
} Group;