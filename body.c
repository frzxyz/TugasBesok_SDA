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
        printf("%s", group[i]->namaGroup);
        Tim *current;
        current = group[i]->pointer;
        while (current != NULL)
        {
            printf("\n");
            printf("%-15s\tSkor: %-5d\tJumlah Gol: %-15d", current->namaTim,current->score,current->jumlahGol);
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
                    if (temp->prev != NULL) {
                        temp->prev->next = current;
                        current->prev = temp->prev;
                    } else {
                        current->prev = NULL;
                        group[i]->pointer = current;
                    }
                    if (current->next != NULL) {
                        current->next->prev = temp;
                        temp->next = current->next;
                    } else {
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
                if ((current->jumlahGol < current->next->jumlahGol)&&(current->score==current->next->score))
                {
                    Tim *temp = current;
                    current = current->next;
                    if (temp->prev != NULL) {
                        temp->prev->next = current;
                        current->prev = temp->prev;
                    } else {
                        current->prev = NULL;
                        group[i]->pointer = current;
                    }
                    if (current->next != NULL) {
                        current->next->prev = temp;
                        temp->next = current->next;
                    } else {
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


Tim *searchTeam(Group **group, char* key){
    Tim *current;
    for (int i = 0; i < 4; i++)
    {   
        current = group[i]->pointer;
        while (current!=NULL)
        {
            if(strcmp(current->namaTim,key)==0){
                return current;
            }
            else{
                current = current->next;
            }
        }
    }
    return current;
}

void resultmatch(char* tim1, char* tim2)
{
    time_t t;
    int result;
    bool cek= true;
    Tim* team1 = searchTeam(group,tim1);
    Tim* team2 = searchTeam(group,tim2);
    srand((unsigned) time(&t));
    result = 1+rand() %3;
    if (result==1){
        team1->score = team1->score+0;
        team2 -> score = team2->score+3;
        while(cek==true){
            srand((unsigned) time(&t));
            team1->gol=rand() %8;
            team2->gol=rand() %8;
            if(team1->gol<team2->gol){
                team1->jumlahGol=team1->jumlahGol+team1->gol;
                team2->jumlahGol=team2->jumlahGol+team2->gol;
                cek=false;
            }
        }
    }
    else if (result==2){
        team1->score = team1->score+3;
        team2 -> score = team2->score+0;
        while(cek==true){
            srand((unsigned) time(&t));
            team1->gol=rand() %8;
            team2->gol=rand() %8;
            if(team1->gol>team2->gol){
                team1->jumlahGol=team1->jumlahGol+team1->gol;
                team2->jumlahGol=team2->jumlahGol+team2->gol;
                cek=false;
            }
        }
    }
    if (result==3){
        team1->score = team1->score+1;
        team2 -> score = team2->score+1;
        while(cek==true){
            srand((unsigned) time(&t));
            team1->gol=rand() %8;
            team2->gol=rand() %8;
            if(team1->gol==team2->gol){
                team1->jumlahGol=team1->jumlahGol+team1->gol;
                team2->jumlahGol=team2->jumlahGol+team2->gol;
                cek=false;
            }
        }
    }
    printf("Hasil Match Antara %s VS %s Sudah Ditentukan dengan skor %d : %d\n",team1->namaTim,team2->namaTim,team1->gol,team2->gol);
}

void match()
{
    resultmatch("Prancis","Brasil");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Portugal","Belanda");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Prancis","Portugal");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Brasil","Belanda");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Prancis","Belanda");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Brasil","Portugal");
    printf("\n\nPress any key to continue...");
    getch();

    resultmatch("Senegal","Inggris");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Amerika","Australia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Senegal","Amerika");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Inggris","Australia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Senegal","Australia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Inggris","Amerika");
    printf("\n\nPress any key to continue...");
    getch();

    resultmatch("Argentina","Polandia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Maroko","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Argentina","Maroko");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Polandia","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Argentina","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Polandia","Maroko");
    printf("\n\nPress any key to continue...");
    getch();

    resultmatch("Jepang","Spanyol");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Korea","Swiss");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Jepang","Korea");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Spanyol","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Jepang","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch("Spanyol","Korea");
    printf("\n\nPress any key to continue...\n");
    getch();
}
