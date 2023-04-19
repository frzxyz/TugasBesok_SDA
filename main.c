#include "body.c"

int main()
{   
    FILE *fp = fopen("Team.txt", "r");
    group [0] = makeGroup("A",fp);
    group [1] = makeGroup("B",fp);
    group [2] = makeGroup("C",fp);
    group [3] = makeGroup("D",fp);
    match();
    sortTeamByScore(group);
    sortTeamByGoal(group);
    sortTeamByHeadToHead(group);
    displayGroup(group,4);
    fclose(fp);
    return 0;
}