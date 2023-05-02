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


    // Return the parent node
    return parent;
}

void MatchTree(Tim *left, Tim *right){
    time_t t;
    int result;
    bool cek = true;
    srand((unsigned)time(&t));
    result = 1 + rand() % 2;
    if (result == 1)
    {
        left->score = left->score + 0;
        right->score = right->score + 3;
        while (cek == true)
        {
            srand((unsigned)time(&t));
            left->gol = rand() % 8;
            right->gol = rand() % 8;
            if (left->gol < right->gol)
            {
                left->jumlahGol = left->jumlahGol + left->gol;
                right->jumlahGol = right->jumlahGol + right->gol;
                cek = false;
            }
        }
    }
    else
    {
        left->score = left->score + 3;
        right->score = right->score + 0;
        while (cek == true)
        {
            srand((unsigned)time(&t));
            left->gol = rand() % 8;
            right->gol = rand() % 8;
            if (left->gol > right->gol)
            {
                left->jumlahGol = left->jumlahGol + left->gol;
                right->jumlahGol = right->jumlahGol + right->gol;
                cek = false;
            }
        }
    }
}

Tim *createTree()
{
    Tim *leaf1, *leaf2, *leaf3, *leaf4, *leaf5, *leaf6, *leaf7, *leaf8;
    Tim *Sm1, *Sm2, *Sm3, *Sm4, *final1, *final2;
    Tim *root = (Tim *)malloc(sizeof(Tim));

    root->left = (Tim *)malloc(sizeof(Tim));
    final1 = root->left;
    root->right = (Tim *)malloc(sizeof(Tim));
    final2 = root->right;

    root->left->left = (Tim *)malloc(sizeof(Tim));
    Sm1 = root->left->left;
    root->left->right = (Tim *)malloc(sizeof(Tim));
    Sm2 = root->left->right;

    root->right->left = (Tim *)malloc(sizeof(Tim));
    Sm3 = root->right->left; 
    root->right->right = (Tim *)malloc(sizeof(Tim));
    Sm4 = root->right->right;

    root->left->left->left = (Tim *)malloc(sizeof(Tim));
    leaf1 = group[0]->pointer;
    root->left->left->left =leaf1;

    root->left->left->right = (Tim *)malloc(sizeof(Tim));
    leaf2 = group[1]->pointer->next;
    root->left->left->right=leaf2;

    root->left->right->left = (Tim *)malloc(sizeof(Tim));
    leaf3 = group[1]->pointer;
    root->left->right->left = leaf3;

    root->left->right->right = (Tim *)malloc(sizeof(Tim));
    leaf4 = group[0]->pointer->next;
    root->left->right->right = leaf4;

    root->right->left->left = (Tim *)malloc(sizeof(Tim));
    leaf5 = group[2]->pointer;
    root->right->left->left = leaf5;

    root->right->left->right = (Tim *)malloc(sizeof(Tim));
    leaf6 = group[3]->pointer->next;
    root->right->left->right = leaf6;

    root->right->right->left = (Tim *)malloc(sizeof(Tim));
    leaf7 = group[3]->pointer;
    root->right->right->left = leaf7;

    root->right->right->right = (Tim *)malloc(sizeof(Tim));
    leaf8 = group[2]->pointer->next;
    root->right->right->right = leaf8;

    MatchTree(leaf1,leaf2);
    Sm1=winnerMoveToParent(leaf1,leaf2);

    MatchTree(leaf3,leaf4);
    Sm2=winnerMoveToParent(leaf3,leaf4);

    MatchTree(leaf5,leaf6);
    Sm3=winnerMoveToParent(leaf5,leaf6);

    MatchTree(leaf7,leaf8);
    Sm4=winnerMoveToParent(leaf7,leaf8);

    MatchTree(Sm1,Sm2);
    final1=winnerMoveToParent(Sm1,Sm2);

    MatchTree(Sm3,Sm4);
    final2=winnerMoveToParent(Sm3,Sm4);

    MatchTree(final1,final2);
    root=winnerMoveToParent(final1,final2);

    return root;
}

void clearTeam(Group **group){
    for (int i = 0; i < 4; i++)
    {
        
        Tim *current;
        current = group[i]->pointer;
        while (current != NULL)
        {
            current->gol = 0L;
            current->jumlahGol = 0L;
            current->score = 0L;
            current = current->next;
        }
    }
}

void PrintTree(Tim *root){
    printf("\n\t\t\t\t\t\t\t         |%-7s|", root->namaTim);
    printf("\n\t\t\t         ____________________________________|__________________________________");
    printf("\n\t\t\t        |                                                                       |");
    printf("\n\t\t        (%d) |%-7s|\t\t\t\t\t\t\t\t   |%-7s| (%d)",root->left->gol, root->left->namaTim,root->right->namaTim,root->right->gol);
    printf("\n\t          ______________|___________________\t\t\t\t          ______________|___________________");
    printf("\n\t         |                                  |\t\t\t\t         |                                  |");
    printf("\n        (%d) |%-7s|\t\t\t       |%-7s| (%d)\t\t         (%d) |%-7s|                         |%s| (%d)", root->left->left->gol, root->left->left->namaTim,root->left->right->namaTim, root->left->right->gol, root->right->left->gol,root->right->left->namaTim,root->right->right->namaTim, root->right->right->gol);
    printf("\n          _______|______\t\t     _______|_______\t\t          _______|_______\t\t     _______|_______");
    printf("\n         |              |\t\t    |               |\t\t         |               |\t\t    |               |");
    printf("\n (%d) |%-7s|\t    |%-7s| (%d)   (%d) |%-7s|        |%-7s| (%d)", root->left->left->left->gol,root->left->left->left->namaTim, root->left->left->right->namaTim, root->left->left->right->gol, root->left->right->left->gol,root->left->right->left->namaTim,root->left->right->right->namaTim, root->left->right->right->gol);
    printf(" (%d) |%-7s|\t     |%-7s| (%d)   (%d)|%-7s|\t|%-7s| (%d)", root->right->left->left->gol,root->right->left->left->namaTim, root->right->left->right->namaTim, root->right->left->right->gol, root->right->right->left->gol,root->right->right->left->namaTim,root->right->right->right->namaTim, root->right->right->right->gol);
}