#include <stdio.h>
#include <stdlib.h>
#include "body.c"

int main()
{
    Group *group[2];
    Tim *tim;

    tim = makeTim("Indonesia");
    tim->next = makeTim("Inggris");
    group[0] = makeGroup("Group A");
    group[1] = makeGroup("Group B");
    displayGroup(group, 2);
    displayTim(tim);
    return 0;
}