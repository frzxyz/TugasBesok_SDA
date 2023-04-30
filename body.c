#include "header.h"
#include "conio.h"

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
        printf(" GROUP %s\n", group[i]->namaGroup);
        printf("+------------------------------------------+\n");
        printf("|    Team        |    Score   |    Goal    |\n");
        printf("|----------------+------------+------------|\n");
        Tim *current;
        current = group[i]->pointer;
        while (current != NULL)
        {
            printf("| %-15s|      %-6d|     %-7d|\n", current->namaTim, current->score, current->jumlahGol);
            if (current->next != NULL)
            {
                printf("|----------------+------------+------------|\n");
            }
            else
            {
                printf("+------------------------------------------+\n");
            }
            current = current->next;
        }
        printf("\n\n");
    }
}

void sortTeamByScore(Group **group)
{
    for (int i = 0; i < 4; i++)
    {
        Tim *current = group[i]->pointer;
        int swapped;
        do
        {
            swapped = 0;
            while (current != NULL && current->next != NULL)
            {
                if (current->score < current->next->score)
                {
                    Tim *temp = current;
                    current = current->next;
                    if (temp->prev != NULL)
                    {
                        temp->prev->next = current;
                        current->prev = temp->prev;
                    }
                    else
                    {
                        current->prev = NULL;
                        group[i]->pointer = current;
                    }
                    if (current->next != NULL)
                    {
                        current->next->prev = temp;
                        temp->next = current->next;
                    }
                    else
                    {
                        temp->next = NULL;
                    }
                    current->next = temp;
                    temp->prev = current;
                    swapped = 1;
                }
                else
                {
                    current = current->next;
                }
            }
            current = group[i]->pointer;
        } while (swapped);
    }
}

void sortTeamByGoal(Group **group)
{
    for (int i = 0; i < 4; i++)
    {
        Tim *current = group[i]->pointer;
        int swapped;
        do
        {
            swapped = 0;
            while (current != NULL && current->next != NULL)
            {
                if ((current->jumlahGol < current->next->jumlahGol) && (current->score == current->next->score))
                {
                    Tim *temp = current;
                    current = current->next;
                    if (temp->prev != NULL)
                    {
                        temp->prev->next = current;
                        current->prev = temp->prev;
                    }
                    else
                    {
                        current->prev = NULL;
                        group[i]->pointer = current;
                    }
                    if (current->next != NULL)
                    {
                        current->next->prev = temp;
                        temp->next = current->next;
                    }
                    else
                    {
                        temp->next = NULL;
                    }
                    current->next = temp;
                    temp->prev = current;
                    swapped = 1;
                }
                else
                {
                    current = current->next;
                }
            }
            current = group[i]->pointer;
        } while (swapped);
    }
}

Tim *searchTeam(Group **group, char *key)
{
    Tim *current;
    for (int i = 0; i < 4; i++)
    {
        current = group[i]->pointer;
        while (current != NULL)
        {
            if (strcmp(current->namaTim, key) == 0)
            {
                return current;
            }
            else
            {
                current = current->next;
            }
        }
    }
    return current;
}

void resultmatch(char *tim1, char *tim2)
{
    time_t t;
    int result;
    bool cek = true;
    Tim *team1 = searchTeam(group, tim1);
    Tim *team2 = searchTeam(group, tim2);
    srand((unsigned)time(&t));
    result = 1 + rand() % 3;
    if (result == 1)
    {
        team1->score = team1->score + 0;
        team1->loseBy = team2->namaTim;
        team2->score = team2->score + 3;
        while (cek == true)
        {
            srand((unsigned)time(&t));
            team1->gol = rand() % 8;
            team2->gol = rand() % 8;
            if (team1->gol < team2->gol)
            {
                team1->jumlahGol = team1->jumlahGol + team1->gol;
                team2->jumlahGol = team2->jumlahGol + team2->gol;
                cek = false;
            }
        }
    }
    else if (result == 2)
    {
        team1->score = team1->score + 3;
        team2->score = team2->score + 0;
        team2->loseBy = team1->namaTim;
        while (cek == true)
        {
            srand((unsigned)time(&t));
            team1->gol = rand() % 8;
            team2->gol = rand() % 8;
            if (team1->gol > team2->gol)
            {
                team1->jumlahGol = team1->jumlahGol + team1->gol;
                team2->jumlahGol = team2->jumlahGol + team2->gol;
                cek = false;
            }
        }
    }
    if (result == 3)
    {
        team1->score = team1->score + 1;
        team2->score = team2->score + 1;
        team2->loseBy = team1->namaTim;
        team1->loseBy = team2->namaTim;
        while (cek == true)
        {
            srand((unsigned)time(&t));
            team1->gol = rand() % 8;
            team2->gol = rand() % 8;
            if (team1->gol == team2->gol)
            {
                team1->jumlahGol = team1->jumlahGol + team1->gol;
                team2->jumlahGol = team2->jumlahGol + team2->gol;
                cek = false;
            }
        }
    }
    printf("Result %-7s VS %-7s = %d : %d\n", team1->namaTim, team2->namaTim, team1->gol, team2->gol);
}

void match()
{
    resultmatch("Prancis", "Brasil");
    getch();
    resultmatch("Portugal", "Belanda");
    getch();
    resultmatch("Prancis", "Portugal");
    getch();
    resultmatch("Brasil", "Belanda");
    getch();
    resultmatch("Prancis", "Belanda");
    getch();
    resultmatch("Brasil", "Portugal");
    getch();
    printf("\n\n");

    resultmatch("Senegal", "Inggris");
    getch();
    resultmatch("Amerika", "Australia");
    getch();
    resultmatch("Senegal", "Amerika");
    getch();
    resultmatch("Inggris", "Australia");
    getch();
    resultmatch("Senegal", "Australia");
    getch();
    resultmatch("Inggris", "Amerika");
    getch();
    printf("\n\n");

    resultmatch("Argentina", "Polandia");
    getch();
    resultmatch("Maroko", "Kroasia");
    getch();
    resultmatch("Argentina", "Maroko");
    getch();
    resultmatch("Polandia", "Kroasia");
    getch();
    resultmatch("Argentina", "Kroasia");
    getch();
    resultmatch("Polandia", "Maroko");
    getch();
    printf("\n\n");

    resultmatch("Jepang", "Spanyol");
    getch();
    resultmatch("Korea", "Swiss");
    getch();
    resultmatch("Jepang", "Korea");
    getch();
    resultmatch("Spanyol", "Swiss");
    getch();
    resultmatch("Jepang", "Swiss");
    getch();
    resultmatch("Spanyol", "Korea");
    printf("\n\nPress any key to continue...\n\n");
    getch();
}

Tim *Penalty(char *Team1, char *Team2)
{
    time_t t;
    int result;
    bool cek = true;
    Tim *winner;
    Tim *team1 = searchTeam(group, Team1);
    Tim *team2 = searchTeam(group, Team2);
    srand((unsigned)time(&t));
    result = 1 + rand() % 2;
    if (result == 1)
    {
        while (cek == true)
        {
            srand((unsigned)time(&t));
            team1->gol = rand() % 5;
            team2->gol = rand() % 5;
            if (team1->gol > team2->gol)
            {
                team1->jumlahGol = team1->jumlahGol + team1->gol;
                team2->jumlahGol = team2->jumlahGol + team2->gol;
                cek = false;
                winner = team2;
            }
        }
    }
    else if (result == 2)
    {
        while (cek == true)
        {
            srand((unsigned)time(&t));
            team1->gol = rand() % 5;
            team2->gol = rand() % 5;
            if (team1->gol < team2->gol)
            {
                team1->jumlahGol = team1->jumlahGol + team1->gol;
                team2->jumlahGol = team2->jumlahGol + team2->gol;
                cek = false;
                winner = team1;
            }
        }
    }
    printf("Result Penalty %-7s VS %-7s = %d : %d\n", team1->namaTim, team2->namaTim, team1->gol, team2->gol);
    return winner;
}

void sortTeamByHeadToHead(Group **group)
{
    for (int i = 0; i < 4; i++)
    {
        Tim *current = group[i]->pointer;
        int swapped;
        do
        {
            swapped = 0;
            while (current != NULL && current->next != NULL)
            {
                if ((current->score == current->next->score) && (current->jumlahGol == current->next->jumlahGol) && (current->loseBy == current->next->namaTim && current->next->loseBy == current->namaTim))
                {
                    Penalty(current->namaTim, current->next->namaTim);
                }
                else if (current->score == current->next->score && (current->jumlahGol == current->next->jumlahGol) && (current->loseBy == current->next->namaTim))
                {
                    Tim *temp = current;
                    current = current->next;
                    if (temp->prev != NULL)
                    {
                        temp->prev->next = current;
                        current->prev = temp->prev;
                    }
                    else
                    {
                        current->prev = NULL;
                        group[i]->pointer = current;
                    }
                    if (current->next != NULL)
                    {
                        current->next->prev = temp;
                        temp->next = current->next;
                    }
                    else
                    {
                        temp->next = NULL;
                    }
                    current->next = temp;
                    temp->prev = current;
                    swapped = 1;
                }
                else
                {
                    current = current->next;
                }
            }
            current = group[i]->pointer;
        } while (swapped);
    }
    sortTeamByGoal(group);
}

Tim *createTree()
{
    Tim *leaf1, *leaf2, *leaf3, *leaf4, *leaf5, *leaf6, *leaf7, *leaf8;
    Tim *root = (Tim *)malloc(sizeof(Tim));

    root->prev = (Tim *)malloc(sizeof(Tim));
    root->next = (Tim *)malloc(sizeof(Tim));

    root->prev->prev = (Tim *)malloc(sizeof(Tim));
    root->prev->next = (Tim *)malloc(sizeof(Tim));

    root->next->prev = (Tim *)malloc(sizeof(Tim));
    root->next->next = (Tim *)malloc(sizeof(Tim));

    root->prev->prev->prev = (Tim *)malloc(sizeof(Tim));
    root->prev->prev->next = (Tim *)malloc(sizeof(Tim));

    root->prev->next->prev = (Tim *)malloc(sizeof(Tim));
    root->prev->next->next = (Tim *)malloc(sizeof(Tim));

    root->next->prev->prev = (Tim *)malloc(sizeof(Tim));
    root->next->prev->next = (Tim *)malloc(sizeof(Tim));

    root->next->next->prev = (Tim *)malloc(sizeof(Tim));
    root->next->next->next = (Tim *)malloc(sizeof(Tim));

    leaf1 = root->prev->prev->prev;
    leaf2 = root->prev->prev->next;
    leaf3 = root->prev->next->prev;
    leaf4 = root->prev->next->next;
    leaf5 = root->next->prev->prev;
    leaf6 = root->next->prev->next;
    leaf7 = root->next->next->prev;
    leaf8 = root->next->next->next;

    return root;
}

Tim *winnerMoveToParent(Tim *leftChild, Tim *rightChild)
{
    // Check apakah leftChild atau rightChild NULL
    if (leftChild == NULL || rightChild == NULL)
    {
        return NULL;
    }

    Tim *parent = (Tim *)malloc(sizeof(Tim));

    // Menentukan pemenang
    Tim *winner;
    if (leftChild->score > rightChild->score)
    {
        winner = leftChild;
    }
    else
    {
        winner = rightChild;
    }

    // Assign the winner to the parent node
    parent->namaTim = winner->namaTim;
    parent->loseBy = NULL;
    parent->gol = 0;
    parent->jumlahGol = 0;
    parent->score = 0;

    // Set the parent's children
    parent->left = leftChild;
    parent->right = rightChild;

    // Update the parent's pointers
    leftChild->prev = parent;
    rightChild->prev = parent;
    leftChild->next = rightChild;
    rightChild->next = NULL;

    // Return the parent node
    return parent;
}
