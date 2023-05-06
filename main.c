#include "body.c"
#include "conio.h"

int main()
{   
    FILE *fp = fopen("Team.txt", "r");
    group [0] = makeGroup("A",fp);
    group [1] = makeGroup("B",fp);
    group [2] = makeGroup("C",fp);
    group [3] = makeGroup("D",fp);
    displayGroup(group,4);
    printf("\n\nPress any key to continue...\n\n");
    getch();
    match1();
    sortTeamByScore(group);
    sortTeamByGoal(group);
    sortTeamByHeadToHead(group);
    displayGroup(group,4);
    printf("\n\nPress any key to continue...\n\n");
    getch();
    match2();
    sortTeamByScore(group);
    sortTeamByGoal(group);
    sortTeamByHeadToHead(group);
    displayGroup(group,4);
    printf("\n\nPress any key to continue...\n\n");
    getch();
    match3();
    sortTeamByScore(group);
    sortTeamByGoal(group);
    sortTeamByHeadToHead(group);
    displayGroup(group,4);
    clearTeam(group);
    tree = createTree();
    printf("\n\nPress any key to exit...\n\n");
    getch();
    fclose(fp);
    return 0;
}