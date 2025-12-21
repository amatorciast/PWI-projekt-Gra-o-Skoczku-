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
// "🭽▔▔▔▔🭾" "🭼▁▁▁▁🭿" "▏    ▕"

typedef struct{
    char map[8][8];
}Game_info;

Game_info symulowanie_planszy_z_pionkami();


char* klocki[8][2]={ //tablica z klockami do budowy planszy, poki co w wielkim chaosie
    {"🭗    🭢", "╔═══╗ "},
    {"┌─┬─┐ ", "╔═╤═╗ "},
    {"🬼    🭇", "╚═══╝ "},
    {"└─┴─┘ ", "╚═╧═╝ "},
    {"├   ┤ ", "║   ║ "},
    {"      ", "╟   ╢ "},
    {"  ♜   ", " "},
    {"  ♞   ", " "}
};

char* kolory[]={ //tablica ze wszystkimi kolorkami
    "\x1b[48;2;219;160;125m", //jasny-plansza
    "\x1b[48;2;117;55;13m", //ciemny-plansza
    "\x1b[38;2;92;41;10m", //jasny-pionki
    "\x1b[38;2;43;19;3m", //ciemny-pionki
    "\x1b[0m" //brak
};


void set_output()
{
    //usuwanie tego co bylo w terminalu
    printf("\e[1;1H\e[2J\e[3J");


    //obczajanie rozmiaru terminala
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int odstep = (w.ws_col - 6*8) / 2;
    if (odstep < 0) odstep=0;


    Game_info pionki= symulowanie_planszy_z_pionkami();
    
    //petla co wypisuje plansze
    for (int i=0; i<24;i++)
    {
        printf("%*s ", odstep, klocki[7][1]);
        for (int k=0;k<8;k++)
        {
            //do zrobienia: usunac te glupie ify
            //do zrobienia: uwzglednic reszte figur
            if (pionki.map[i/3][k]==0)
            {
                if (i%3==1) printf("%s%s%s" "\x1b[0m", kolory[(i/3+k)%2], kolory[3], klocki[5][0]);
                else printf("%s%s%s" "\x1b[0m", kolory[(i/3+k)%2], kolory[3],klocki[i%3][0]);
            }
            if (pionki.map[i/3][k]==1)
            {
                if (i%3==1) printf("%s%s" "\x1b[0m", kolory[(i/3+k)%2], klocki[7][0]);
                else printf("%s%s%s" "\x1b[0m", kolory[(i/3+k)%2], kolory[3], klocki[i%3][0]);
            }
            if (pionki.map[i/3][k]==2)
            {
                if (i%3==1) printf("%s%s" "\x1b[0m", kolory[(i/3+k)%2], klocki[6][0]);
                else printf("%s%s%s" "\x1b[0m", kolory[(i/3+k)%2], kolory[3],klocki[i%3][0]);
            }
        }
        printf("\n");
    }
}

//pomysly do uwzglednienia:
//zmniejszyc kazde pole na planszy, bo pionki sa za male. Druga opcja - zwiekszyc pionki, ale to duzo roboty
//jak szybko skoncze - animacja?? wyswietla sie najpierw plansza z samymi figurami, potem dodatkowo gdzie celuja przeciwnicy, a na koniec gdzie moze skoczyc skoczek



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
    

Game_info symulowanie_planszy_z_pionkami()
{
    Game_info symulacja;
    for (int i=0; i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if ((i+j)%12==0) symulacja.map[i][j]=2;
            //else if ((i+j)%7==0) pionki.map[i][j]=3;
            else symulacja.map[i][j]=0;
        }
    }
    symulacja.map[3][6]=1;
    return symulacja;
}


