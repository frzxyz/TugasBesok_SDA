#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
// Tim
typedef struct tim
{
    char *namaTim, *loseBy;
    struct tim *next, *prev, *left, *right;
    int gol, jumlahGol, score;
} Tim;

// Menyimpan grup
typedef struct group
{
    char *namaGroup;
    Tim *pointer;
} Group;

Group *group[4];
Tim *tim;
Tim *tree;

Tim *makeTim(char *namaTim);
/*
Membuat Node tim dan inisialisasi node tersebut dengan next dan prev bernilai NULL.
IS: Node belum tim belum terbentuk
FS: Node sudah Terbentuk
*/
Group *makeGroup(char *namaGroup, FILE *fp);
/*
Membuat Group serta memanggil modul addteam untuk menyambungkan antara array grup dengan node-node team, serta mengambil nama tim dari file.
IS: Grup belum dibuat dan node team belum terbentuk.
FS: Grup telah dibuat dan tersambung ke node team-teamnya.
*/
void addteam(Group *group, char *namatim);
/*
Modul Untuk menyambungkan antara array grup dan team dan memanggil fungsi maketim untuk membuat node tim.
IS: Node team belum terbuat dan belum tersambung satu sama lain.
FS: Node team sudah terbuat dan sudah tersambung satu sama lain.
*/
void displayGroup(Group **group, int numsGroup);
/*
Modul untuk menampilkan group beserta team-team dalam grup tersebut.
IS: Grup dan team-teamnya belum dapat ditampilkan.
FS: Grup dan team-teamnya sudah dapat ditampilkan.
*/