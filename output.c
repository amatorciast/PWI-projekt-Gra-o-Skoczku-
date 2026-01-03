#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include <stdio.h>
#include "lib.h"

void windows_dzialaj();
void wsadzanie_przeciwnikow_na_plansze(char[8][8]);
void wsadzanie_ruchu_przeciwnikow(char[8][8]);
void obliczanie_mozliwych_ruchow(int, int, char[8][8]);

//tablica z klockami do budowy planszy:
char* klocki[27]={
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
    "🭁🭌",
    "🭆🭩",
    "🭵🭪",
    "🮭🮬",
    "🭅🭐",
    "🭩🭩",
    "🭨🭪",
    " ", //[17]
    "  ⏷  ⏷  ",
    "⏵ ",
    " ⏴",
    "  ⏶  ⏶  ",
    " ",
    "🮢",//[23]
    "🮠",
    "🮣",
    "🮡",
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
    char pionki[8][8];
    wsadzanie_przeciwnikow_na_plansze(pionki);
    char ataki[8][8];
    wsadzanie_ruchu_przeciwnikow(ataki);
    char skoczek_x=-1;
    char skoczek_y=-1;
    char ruchy [8][8];
    obliczanie_mozliwych_ruchow(skoczek_x, skoczek_y, ruchy); //poki co nie robi nic :/


    //usuwanie tego co bylo w terminalu
    printf("\e[1;1H\e[2J\e[3J");

    /*obczajanie rozmiaru terminala
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int odstep = (w.ws_col - 8*8) / 2;
    if (odstep < 0) odstep=0;
    */


    //petla co wypisuje plansze
    for (int i=0; i<32;i++)
    {
        //printf("%*s ", odstep, klocki[17]);
        for (int k=0;k<8;k++)
        {
            if(i%4==0 || i%4==3)
            {
                printf("%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy[i/4][k] ],klocki[i%4 + ruchy[i/4][k]*18]);
            } 
            else if(i%4==1) printf("%s" "%s%s%s" "%s%s" "%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy[i/4][k] ], klocki[4 + ruchy[i/4][k]*15], klocki[22+ataki[i/4][k]], kolory[pionki[i/4][k]==-1? 2 : 3], klocki[5+0+2*pionki[i/4][k]], kolory[3 -ruchy[i/4][k] ], klocki[22+3*ataki[i/4][k]], klocki[4 + ruchy[i/4][k]*16]);
            else printf("%s" "%s%s%s" "%s%s" "%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy[i/4][k] ], klocki[4 + ruchy[i/4][k]*15], klocki[22+2*ataki[i/4][k]], kolory[pionki[i/4][k]==-1? 2 : 3], klocki[5+1+2*pionki[i/4][k]], kolory[3 -ruchy[i/4][k] ], klocki[22+4*ataki[i/4][k]], klocki[4 + ruchy[i/4][k]*16]);
        }
        printf("\n");
    }
}


//rzeczy do zrobienia:
//uwzględnienie polozenia gracza

//pomysly do uwzglednienia:
//jak szybko skoncze - animacja?? wyswietla sie najpierw plansza z samymi figurami, potem dodatkowo gdzie celuja przeciwnicy, a na koniec gdzie moze skoczyc skoczek


//funkcje pomocnicze:
void wsadzanie_przeciwnikow_na_plansze(char pionki[8][8])
{
    for (int i=0; i<8;i++)
        for (int j=0; j<8;j++)
            pionki[i][j]=0;

    for (int i=0; i<64;i++)
        if (enemies[i].alive == 1 && enemies[i].curr_x>=0 && enemies[i].curr_y>=0)
            pionki[enemies[i].curr_x][enemies[i].curr_y]=enemies[i].figure+1;

    return;
}

void wsadzanie_ruchu_przeciwnikow(char ataki[8][8])
{
    for (int i=0; i<8;i++)
        for (int j=0; j<8;j++)
            ataki[i][j]=0;

    for (int i=0; i<64;i++)
        if (enemies[i].alive == 1 && enemies[i].next_x>=0 && enemies[i].next_y>=0 && enemies[i].next_x<8 && enemies[i].next_y<8)
            ataki[enemies[i].next_x][enemies[i].next_y]=1;

    return;
}
    
void obliczanie_mozliwych_ruchow(int x, int y, char skoczek[8][8])
{
    for (int i=0; i<8;i++)
        for (int j=0;j<8;j++)
            skoczek[i][j]=0;

    if (x==-1) return;
    if (x+2<8 && y+1<8) skoczek[x+2][y+1]=1;
    if (x+2<8 && y-1>-1) skoczek[x+2][y-1]=1;
    if (x-2>-1 && y+1<8) skoczek[x-2][y+1]=1;
    if (x-2>-1 && y-1>-1) skoczek[x-2][y-1]=1;
    if (x+1<8 && y+2<8) skoczek[x+1][y+2]=1;
    if (x+1<8 && y-2>-1) skoczek[x+1][y-2]=1;
    if (x-1>-1 && y+2<8) skoczek[x-1][y+2]=1;
    if (x-1>-1 && y-2>-1) skoczek[x-1][y-2]=1;
    skoczek[x][y]=1;
    return;
}

void windows_dzialaj() 
{
#ifdef _WIN32
    //UTF-8
    SetConsoleOutputCP(CP_UTF8);

    //kolorki
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

