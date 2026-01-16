#ifdef _WIN32
    #include <windows.h>
    #define sleep(ms) Sleep(ms*1000)
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #define sleep(ms) sleep(ms)
#endif

#include <stdio.h>
#include "lib.h"

char* klocki[32]={ //tablica z klockami do budowy planszy:
    "🭗 ",
    "🬼 ",
    " 🭢",
    " 🭇",
    "  ",
    "  ",
    "  ",
    "◖◗", //[7]
    "🭃🭎",
    "🬪🬜",
    "🭁🭌",
    "🭆🭩",
    "🭵🭡",
    "🮭🮬",
    "🭅🭐",
    "🭩🭩",
    "🭨🭪",
    "🭩🭑",
    "🭖🭰",
    " ", //[19]
    "    ",
    "⏷  ⏷",
    "",
    "    ",
    "⏶  ⏶",
    "⏵ ",
    " ⏴",
    " ",
    "🮢",//[28]
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
    windows_dzialaj();
    char pionki[8][8]={0};
    wsadzanie_przeciwnikow_na_plansze(pionki);
    char ataki[8][8]={0};
    wsadzanie_ruchu_przeciwnikow(ataki);
    char ruchy [8][8]={0};
    obliczanie_mozliwych_ruchow(ruchy);

    //usuwanie tego co bylo w terminalu
    printf("\e[1;1H\e[2J\e[3J");

    //petla co wypisuje plansze
    for (int i=0; i<32;i++)
    {
        for (int k=0;k<8;k++)
        {
            if(i%4==0 || i%4==3)
            {
                printf("%s" "%s%s" "%s%s" "%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3], klocki[i%4/2], kolory[2], klocki[i%4 +20 + ruchy[i/4][k]], kolory[3], klocki[i%4/2+2]);
            } 
            else if(i%4==1) printf("%s" "%s%s%s%s" "%s%s" "%s%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[2], klocki[4 + ruchy[i/4][k]*21], kolory[3], klocki[27+ataki[i/4][k]], kolory[pionki[i/4][k]==6? 2 : 3], klocki[5+0+2*pionki[i/4][k]], kolory[3], klocki[27+3*ataki[i/4][k]], kolory[2], klocki[4 + ruchy[i/4][k]*22]);
            else            printf("%s" "%s%s%s%s" "%s%s" "%s%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[2], klocki[4 + ruchy[i/4][k]*21], kolory[3], klocki[27+2*ataki[i/4][k]], kolory[pionki[i/4][k]==6? 2 : 3], klocki[5+1+2*pionki[i/4][k]], kolory[3], klocki[27+4*ataki[i/4][k]], kolory[2], klocki[4 + ruchy[i/4][k]*22]);
        }
        printf("\n");
    }
}


//funkcje pomocnicze:
void wsadzanie_przeciwnikow_na_plansze(char pionki[8][8])
{
    for (int i=0; i<64;i++)
        if (game.enemies[i].alive == 1 && game.enemies[i].curr_x>=0 && game.enemies[i].curr_y>=0)
            pionki[game.enemies[i].curr_x][game.enemies[i].curr_y]=game.enemies[i].figure+1;

    pionki[game.x][game.y]=6; //wsadzenie gracza
    return;
}

void wsadzanie_ruchu_przeciwnikow(char ataki[8][8])
{
    for (int i=0; i<64;i++)
        if (game.enemies[i].alive == 1 && game.enemies[i].next_x>=0 && game.enemies[i].next_y>=0 && game.enemies[i].next_x<8 && game.enemies[i].next_y<8)
            ataki[game.enemies[i].next_x][game.enemies[i].next_y]=1;

    return;
}
    
void obliczanie_mozliwych_ruchow(char skoczek[8][8])
{
    if (game.x==-1) return;
    if (game.x+2<8 && game.y+1<8) skoczek[game.x+2][game.y+1]=1;
    if (game.x+2<8 && game.y-1>-1) skoczek[game.x+2][game.y-1]=1;
    if (game.x-2>-1 && game.y+1<8) skoczek[game.x-2][game.y+1]=1;
    if (game.x-2>-1 && game.y-1>-1) skoczek[game.x-2][game.y-1]=1;
    if (game.x+1<8 && game.y+2<8) skoczek[game.x+1][game.y+2]=1;
    if (game.x+1<8 && game.y-2>-1) skoczek[game.x+1][game.y-2]=1;
    if (game.x-1>-1 && game.y+2<8) skoczek[game.x-1][game.y+2]=1;
    if (game.x-1>-1 && game.y-2>-1) skoczek[game.x-1][game.y-2]=1;
    skoczek[game.x][game.y]=1;
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
    dwMode |= 0x0004;
    SetConsoleMode(hOut, dwMode);
#endif
}

