#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
//#include <uchar.h>
//#include "lib.h"

//klocki do budowy planszy
// "┌───┐ " "┌─┬─┐ " "╔═══╗ " "╔═╤═╗ "
// "└───┘ " "└─┴─┘ " "╚═══╝ " "╚═╧═╝ "
// "│   │ " "├   ┤ " "║   ║ " "╟   ╢ "
// "🭗    🭢" "🬼    🭇" ⃞
// "🭽▔▔▔▔▔▔🭾" "🭼▁▁▁▁▁▁🭿" "▏    ▕"

typedef struct{
    char map[8][8];
    int x,y;
}Game_info;

Game_info obliczanie_mozliwych_ruchow(int, int);
Game_info symulowanie_planszy_z_pionkami();

//tablica z klockami do budowy planszy.
char* klocki[24]={
    "🭗      🭢",
    "        ",
    "        ",
    "🬼      🭇",
    "   ",
    "  ",
    "  ",
    "🭆🭩",//🭆🭩  🭆🭩 ewentualnie ktorys z tych
    "🭵🭐",//🭵🭡  🭵🭪
    "◖◗",
    "🭅🭐",
    "🬪🬜",
    "🭃🭎",
    "🮭🮬",
    "🭅🭐",
    "🭩🭩",//krol do poprawy
    "🭅🭐",
    "🮬🮭",//krolowa do poprawy
    "🭖🭡",
    " ",
    "  ⏷  ⏷  ",
    "⏵  ",
    "  ⏴",
    "  ⏶  ⏶  "
//Pozycja danych figur jest zależna od tego jak jest oznaczana w map[][] (np kon to 1, wiec jest pierwszy w tablicy)
// W ten sposób nie musze robić ifa dla kazdej figury w pętli wypisującej.
// Póki nie wiem jak dokładnie będą zapisane dane o planszy, które otrzymam,
//to działam na zmyślonych, a ostatecznie się dostosuję i to zmienie.
//Najpewniej informacje o tym gdzie poruszą się przeciwnicy, gdzie moze skoczyc skoczek, będę musiał specjalnie pod siebie przerobić
};

char* kolory[6]={ //tablica ze wszystkimi kolorkami
    "\x1b[48;2;219;160;125m", //jasny-plansza
    "\x1b[48;2;117;55;13m", //ciemny-plansza
    "\x1b[38;2;163;98;59m", //jasny-pionki
    "\x1b[38;2;43;19;3m", //ciemny-pionki
    "\x1b[0m", //brak
    ""
};



void set_output(/*Game_info pionki*/)
{
    Game_info pionki= symulowanie_planszy_z_pionkami();
    Game_info ruchy=obliczanie_mozliwych_ruchow(pionki.x,pionki.y);


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
        printf("%*s ", odstep, klocki[19]);
        for (int k=0;k<8;k++)
        {
            if(i%4==0 || i%4==3)
            {
                printf("%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy.map[i/4][k] ],klocki[i%4 + ruchy.map[i/4][k]*20]);
            } else printf("%s%s%s%s%s%s%s" "\x1b[0m", kolory[(i/4+k)%2], kolory[3 -ruchy.map[i/4][k] ], klocki[4 + ruchy.map[i/4][k]*17], kolory[pionki.map[i/4][k]==1? 2 : 3], klocki[5+(i%4-1)+2*pionki.map[i/4][k]], kolory[3 -ruchy.map[i/4][k] ], klocki[4 + ruchy.map[i/4][k]*18]);
        }
        printf("\n");
    }
}


//rzeczy do zrobienia:
//uwzględnienie ruchu przeciwnika

//pomysly do uwzglednienia:
//jak szybko skoncze - animacja?? wyswietla sie najpierw plansza z samymi figurami, potem dodatkowo gdzie celuja przeciwnicy, a na koniec gdzie moze skoczyc skoczek


/*
int main()
{
    int test;
    while (1)
    {
        scanf("%d", &test);
        set_output();
    }
    test=test;
    return 0;
}
*/

    
Game_info obliczanie_mozliwych_ruchow(int x, int y)
{
    Game_info skoczek;
    for (int i=0; i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            skoczek.map[i][j]=0;
        }
    }
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

Game_info symulowanie_planszy_z_pionkami()
{
    Game_info symulacja;
    for (int i=0; i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            symulacja.map[i][j]=0;
        }
    }
    symulacja.map[1][7]=2;
    symulacja.map[3][3]=2;
    symulacja.map[7][1]=2;
    symulacja.map[2][0]=3;
    symulacja.map[7][5]=3;
    symulacja.map[4][3]=4;
    symulacja.map[0][2]=5;
    symulacja.map[5][4]=6;
    symulacja.map[3][6]=1;
    symulacja.x=3;
    symulacja.y=6;
    return symulacja;
}


