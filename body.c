#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

Tim *makeTim(char *namaTim)
{
    Tim *tim = (Tim *)malloc(sizeof(Tim));
    tim->namaTim = (char *)malloc(strlen(namaTim) + 1);
    strcpy(tim->namaTim, namaTim);
    tim->next = NULL;
    tim->prev = NULL;
    tim->gol = 0;
    tim->jumlahGol = 0;
    tim->score = 0;
    return tim;
}

Group *makeGroup(char *namaGroup, FILE *fp)
{
    Group *group = (Group *)malloc(sizeof(Group));
    group->namaGroup = namaGroup;
    group->pointer = NULL;
    for (int i = 0; i < 4; i++)
    {
        char timName[50];
        if (fscanf(fp, "%s", timName) == 1)
        {
            addteam(group, timName);
        }
        else
        {
            printf("Error");
        }
    }
    return group;
}

void addteam(Group *group, char *namatim)
{
    Tim *newteam = makeTim(namatim);
    if (group->pointer == NULL)
    {
        group->pointer = newteam;
    }
    else
    {
        Tim *current = group->pointer;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newteam;
        newteam->prev = current;
    }
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

void sortTeamByScore(Tim **head_ref)
{
    Tim *current, *temp;
    int swapped;
    do
    {
        swapped = 0;
        current = *head_ref;
        while (current->next != NULL)
        {
            if (current->score < current->next->score)
            {
                temp = current->next;
                current->next = temp->next;
                temp->prev = current->prev;
                current->prev = temp;
                temp->next = current;
                if (current == *head_ref)
                {
                    *head_ref = temp;
                }
                else
                {
                    current->prev->next = temp;
                }
                swapped = 1;
            }
            else
            {
                current = current->next;
            }
        }
    } while (swapped);
}

void golForAMatch(Tim **team)
{
    srand(time(NULL)); // seed the random number generator with the current time
    int min = 0;
    int max = 7;
    int randomNumber = rand() % (max - min + 1) + min;
    (*team)->gol = randomNumber;
}

void matchDecider(Tim **team1, Tim **team2)
{
    if ((*team1)->gol > (*team2)->gol)
    {
        (*team1)->score = (*team1)->score + 3;
    }
    else if ((*team1)->gol < (*team2)->gol)
    {
        (*team2)->score = (*team2)->score + 3;
    }
    else
    {
        (*team1)->score = (*team1)->score + 1;
        (*team2)->score = (*team2)->score + 1;
    }
}