#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Group *group[4];
Tim *tim;

void addteam(Group* group, char* namatim);