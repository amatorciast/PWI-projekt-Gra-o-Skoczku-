#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
//#include <uchar.h>
#include "lib.h"

void wsadzanie_przeciwnikow_na_plansze(Game_info*);
void wsadzanie_ruchu_przeciwnikow(Game_info*);
Game_info obliczanie_mozliwych_ruchow(int, int);

//tablica z klockami do budowy planszy:
char* klocki[25]={
    "🭗      🭢",
    "        ",
    "        ",
    "🬼      🭇",
    "  ",
    "  ",
    "  ",
    "◖◗", //[7]
    "🭃🭎",
    "🬪🬜",
    "🭃🭎",
    "🭆🭩",
    "🭵🭐",
    "🮭🮬",
    "🭅🭐",
    "🭩🭩",
    "🭖🭡",
    " ", //[17]
    "  ⏷  ⏷  ",
    "⏵ ",
    " ⏴",
    "  ⏶  ⏶  ",
    " ",
    "\\",
    "/"
};

char* kolory[6]={ //tablica ze wszystkimi kolorkami:
    "\x1b[48;2;219;160;125m", //jasny-plansza
    "\x1b[48;2;117;55;13m", //ciemny-plansza
    "\x1b[38;2;163;98;59m", //jasny-pionki
    "\x1b[38;2;43;19;3m", //ciemny-pionki
    "\x1b[0m", //brak
    ""
};



void set_output()
{
    Game_info pionki;
    wsadzanie_przeciwnikow_na_plansze(&pionki);
    Game_info ataki;
    wsadzanie_ruchu_przeciwnikow(&ataki);
    pionki.x=-1;
    Game_info ruchy= obliczanie_mozliwych_ruchow(pionki.x,pionki.y); //poki co nie robi nic :/


    //usuwanie tego co bylo w terminalu
    printf("\e[1;1H\e[2J\e[3J");

    //obczajanie rozmiaru terminala
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int odstep = (w.ws_col - 8*8) / 2;
    if (odstep < 0) odstep=0;


    //petla co wypisuje plansze
    for (int i=0; i<32;i++)
    {
        printf("%*s ", odstep, klocki[17]);
        for (int k=0;k<8;k++)
        {
            if(i%4==0 || i%4==3)
            {
                printf("%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy.map[i/4][k] ],klocki[i%4 + ruchy.map[i/4][k]*18]);
            } 
            else if(i%4==1) printf("%s" "%s%s%s" "%s%s" "%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy.map[i/4][k] ], klocki[4 + ruchy.map[i/4][k]*15], klocki[22+ataki.map[i/4][k]], kolory[pionki.map[i/4][k]==-1? 2 : 3], klocki[5+0+2*pionki.map[i/4][k]], kolory[3 -ruchy.map[i/4][k] ], klocki[22+2*ataki.map[i/4][k]], klocki[4 + ruchy.map[i/4][k]*16]);
            else printf("%s" "%s%s%s" "%s%s" "%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy.map[i/4][k] ], klocki[4 + ruchy.map[i/4][k]*15], klocki[22+2*ataki.map[i/4][k]], kolory[pionki.map[i/4][k]==-1? 2 : 3], klocki[5+1+2*pionki.map[i/4][k]], kolory[3 -ruchy.map[i/4][k] ], klocki[22+ataki.map[i/4][k]], klocki[4 + ruchy.map[i/4][k]*16]);
        }
        printf("\n");
    }
}


//rzeczy do zrobienia:
//uwzględnienie polozenia gracza

//pomysly do uwzglednienia:
//jak szybko skoncze - animacja?? wyswietla sie najpierw plansza z samymi figurami, potem dodatkowo gdzie celuja przeciwnicy, a na koniec gdzie moze skoczyc skoczek


//funkcje pomocnicze:
void wsadzanie_przeciwnikow_na_plansze(Game_info *pionki)
{
    for (int i=0; i<8;i++)
        for (int j=0; j<8;j++)
            pionki->map[i][j]=0;

    for (int i=0; i<64;i++)
        if (enemies[i].alive == 1 && enemies[i].curr_x>=0 && enemies[i].curr_y>=0)
            pionki->map[enemies[i].curr_x][enemies[i].curr_y]=enemies[i].figure+1;

    return;
}

void wsadzanie_ruchu_przeciwnikow(Game_info* ataki)
{
    for (int i=0; i<8;i++)
        for (int j=0; j<8;j++)
            ataki->map[i][j]=0;

    for (int i=0; i<64;i++)
        if (enemies[i].alive == 1 && enemies[i].next_x>=0 && enemies[i].next_y>=0 && enemies[i].next_x<8 && enemies[i].next_y<8)
            ataki->map[enemies[i].next_x][enemies[i].next_y]=1;

    return;
}
    
Game_info obliczanie_mozliwych_ruchow(int x, int y)
{
    Game_info skoczek;
    for (int i=0; i<8;i++)
        for (int j=0;j<8;j++)
            skoczek.map[i][j]=0;

    if (x==-1) return skoczek;
    if (x+2<8 && y+1<8) skoczek.map[x+2][y+1]=1;
    if (x+2<8 && y-1>-1) skoczek.map[x+2][y-1]=1;
    if (x-2>-1 && y+1<8) skoczek.map[x-2][y+1]=1;
    if (x-2>-1 && y-1>-1) skoczek.map[x-2][y-1]=1;
    if (x+1<8 && y+2<8) skoczek.map[x+1][y+2]=1;
    if (x+1<8 && y-2>-1) skoczek.map[x+1][y-2]=1;
    if (x-1>-1 && y+2<8) skoczek.map[x-1][y+2]=1;
    if (x-1>-1 && y-2>-1) skoczek.map[x-1][y-2]=1;
    skoczek.map[x][y]=1;
    return skoczek;
}

