#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Tim *makeTim(char *namaTim)
{
    Tim *tim = (Tim *)malloc(sizeof(Tim));
    tim->namaTim = namaTim;
    tim->next = NULL;
    tim->prev = NULL;
    return tim;
}

Group *makeGroup(char *namaGroup)
{
    Group *group = (Group *)malloc(sizeof(Group));
    group->namaGroup = namaGroup;
    group->pointer = NULL;
    return group;
}

void displayGroup(Group **group, int numsGroup)
{
    for (int i = 0; i < numsGroup; i++)
    {
        printf("%s\n", group[i]->namaGroup);
        Tim *current;
        current = group[i]->pointer;
        while (current != NULL)
        {
            printf("%s\n\n", current->namaTim);
            current = current->next;
        }
    }
}

void displayTim(Tim *tim)
{
    Tim *current = tim;
    while (current != NULL)
    {
        printf("%s\n", current->namaTim);
        current = current->next;
    }
    printf("\n");
}