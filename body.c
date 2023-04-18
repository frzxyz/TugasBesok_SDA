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

void resultmatch(Group** group,char* tim1, char* tim2)
{
    srand(time(NULL)); 
    int result;
    bool cek= true;
    Tim* team1 = searchTeam(group,tim1);
    Tim* team2 = searchTeam(group,tim2);
    result = 1+rand()%3;
    if (result==1){
        team1->score = team1->score+0;
        team2 -> score = team2->score+3;
        while(cek==true){
            team1->gol=rand()%7;
            team2->gol=rand()%7;
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
            team1->gol=rand()%7;
            team2->gol=rand()%7;
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
            team1->gol=rand()%7;
            team2->gol=rand()%7;
            if(team1->gol==team2->gol){
                team1->jumlahGol=team1->jumlahGol+team1->gol;
                team2->jumlahGol=team2->jumlahGol+team2->gol;
                cek=false;
            }
        }
    }
    printf("Hasil Match Sudah Ditentukan\n");
}

void match()
{
    resultmatch(group,"Prancis","Brasil");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Portugal","Belanda");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Prancis","Portugal");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Brasil","Belanda");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Prancis","Belanda");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Brasil","Portugal");
    printf("\n\nPress any key to continue...");
    getch();

    resultmatch(group,"Senegal","Inggris");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Amerika","Australia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Senegal","Amerika");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Inggris","Australia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Senegal","Australia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Inggris","Amerika");
    printf("\n\nPress any key to continue...");
    getch();

    resultmatch(group,"Argentina","Polandia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Maroko","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Argentina","Maroko");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Polandia","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Argentina","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Polandia","Maroko");
    printf("\n\nPress any key to continue...");
    getch();

    resultmatch(group,"Jepang","Spanyol");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Korea","Swiss");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Jepang","Korea");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Spanyol","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Jepang","Kroasia");
    printf("\n\nPress any key to continue...");
    getch();
    resultmatch(group,"Spanyol","Korea");
    printf("\n\nPress any key to continue...");
    getch();
}
