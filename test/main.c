#include "header.h"
#include <string.h>
#include <conio.h>

int main()
{   
    FILE *fp = fopen("Team.txt", "r");
    group [0] = makeGroup("A",fp);
    group [1] = makeGroup("B",fp);
    group [2] = makeGroup("C",fp);
    group [3] = makeGroup("D",fp);
    fclose(fp);
    ui();
    /*for(int i = 1; i <=3; i++){
        displayGroup(group,4);
        printf("\n\nPress any key to continue...\n\n");
        getch();
        if(i == 1){
            match1();
        }
        else if(i == 2){
            match2();
        }
        else if(i == 3){
            match3();
        }
        sortTeamByScore(group);
        sortTeamByGoal(group);
        sortTeamByHeadToHead(group);
    }
    displayGroup(group,4);
    clearTeam(group);
    tree = createTree();
    PrintHistory(group);*/
    getch();
    return 0;
    
}