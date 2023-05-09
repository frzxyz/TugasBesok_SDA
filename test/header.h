#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
//Abstrak data untuk node team.
typedef struct match_result {
    char *versus;
    int goals;
    char *status;
    struct match_result *next;
} MatchResult;

typedef struct tim {
    char *namaTim;
    struct tim *next, *prev, *left, *right;
    MatchResult *matchResultHead;
    int gol, score, win, draw, lose, MP, SG;
} Tim;

//Abstrak data untuk grup.
typedef struct group
{
    char *namaGroup;
    Tim *pointer;
} Group;

Group *group[4];
Tim *tim;
Tim *tree;
MatchResult *match_result;

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
void sortTeamByScore(Group **group);
/*
Modul untuk mengurutkan tim berdasarkan skor tertinggi ke terendah menggunakan metode bubble sort
IS: Score setiap team belum terurut dari tertinggi ke terendah.
FS: Score setiap team sudah terurut dari tertinggi ke terendah.
*/
void sortTeamByGoal(Group **group);
/*
Modul untuk mengurutkan tim berdasarkan gol tertinggi ke gol terendah jika skor sama
IS: Score sama dan jumlah gol belum terurut dari tertinggi ke terendah.
FS: Score sama dan jumlah gol telah terurut dari tertinggi ke terendah.
*/
Tim *searchTeam(Group **group, char *key);
/*
Fungsi untuk mencari nama dari tim dan akan mengembalikan nama tim tersebut jika ketemu
IS: Nama tim untuk dicari diketahui dan belum ketemu.
FS: Nama tim diketahui dan sudah ketemu.
*/
void resultmatch(char *tim1, char *tim2);
/*
Modul untuk mengadakan pertandingan antara dua tim dengan score menggunakan fungsi random
IS: Menang,kalah,score,jumlah gol kedua tim belum diketahui.
FS: Menang,kalah,score,jumlah gol kedua tim sudah diketahui.
*/
void match();
/*
Modul untuk menyimpan setiap tim yang akan bertanding dengan memanggil prosedur resultmatch
IS: Tim-Tim dari setiap grup belum bertanding.
FS: Tim-Tim dari setiap grup telah bertanding.
*/
Tim *Penalty(char *Team1, char *Team2);
/*
Fungsi untuk menentukan hasil pinalti antara kedua tim.
IS: Hasil pinalti belum diketahui.
FS: Hasil pinalti telah diketahui.
*/
void sortTeamByHeadToHead(Group **group);
/*
Modul untuk mengurutkan team berdasarkan head to head.
IS: Tim dengan Skor yang sama di grup masih belum bisa ditentukan pemenangnya
FS: Tim denagn skor yang sama di grup sudah bisa ditentukan pemenangnya
*/
Tim *createTree();
/*
Fungsi untuk membuat tree dan memanggil modul movetoparent.
IS: Tree belum terbuat.
FS: Tree sudah terbuat
*/
Tim *winnerMoveToParent(Tim *leftChild, Tim *rightChild);
/*
Fungsi untuk menaikan tim yang menang ke parent tree dari child sebelumnya.
IS: Tim yang menang belum naik ke parent.
FS: Tim yang menang telah naik ke parent.
*/
void MatchTree(Tim *left, Tim *right);
/*
Modul untuk melakukan dan menentukan hasil pertandingan ketika berada di bracket (tree)
IS: Hasil pertandingan belum diketahui.
FS: Hasil pertandingan telah diketahui.
*/
void clearTeam(Group **group);
/*
Modul untuk menghapus seluruh tim.
IS: Seluruh tim belum reset setiap variable nodenya.
FS: Seluruh tim telah reset setiap variable nodenya.
*/
void PrintTree1(Tim *root);
/*
Modul untuk menampilkan tree.
IS: Tree dan namatim belum tampil.
FS: Tree dan namatim sudah tampil.
*/
void PrintTree2(Tim *root);
/*
Modul untuk menampilkan tree.
IS: Tree dan namatim belum tampil.
FS: Tree dan namatim sudah tampil.
*/
void PrintTree3(Tim *root);
/*
Modul untuk menampilkan tree.
IS: Tree dan namatim belum tampil.
FS: Tree dan namatim sudah tampil.
*/
void PrintTree4(Tim *root);
/*
Modul untuk menampilkan tree.
IS: Tree dan namatim belum tampil.
FS: Tree dan namatim sudah tampil.
*/
void printMatchHistory(Tim *tim);
/*
Modul untuk menampilkan history tim yang dicari.
IS: History team belum tampil.
FS: History team sudah tampil
*/
void PrintHistory(Group **group);
/*
Modul untuk mencari team dan memanggil modul printmatchhistory.
IS: Tim yang akan ditampilkan match historynya belum ketemu dan belum tampil.
FS: Tim yang akan ditampilkan match historynya sudah ketemu dan sudah tampil.
*/
void add_history(Tim *team, int goal, char *status, char *versus);
/*
Modul untuk menambahkan history pertandingan setiap tim.
IS: History pertandingan setiap tim belum disimpan.
FS: History pertandingan setiap tim sudah disimpan
*/
int isMatchResultEmpty(Tim *tim);
/*
Fungsi untuk mengecek apakah history masih kosong atau tidak dan akan mengembalikan
pointer head.
*/
void ui();
