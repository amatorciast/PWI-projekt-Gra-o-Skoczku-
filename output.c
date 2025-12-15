#include <stdio.h>
//#include <uchar.h>
//#include "lib.h"

//klocki do budowy planszy
// "┌───┐ " "┌─┬─┐ " "╔═══╗ " "╔═╤═╗ "
// "└───┘ " "└─┴─┘ " "╚═══╝ " "╚═╧═╝ "
// "│   │ " "├   ┤ " "║   ║ " "╟   ╢ "



void set_output()
{
    //tablica ktora bedzie przechowywac wszystkie klocki do budowy planszy, poki co nie uwzglednia przeciwnikow i gdzie sie porusza
    char* tablica_klockow[6][2]={
        {"┌───┐ ", "╔═══╗ "},
        {"┌─┬─┐ ", "╔═╤═╗ "},
        {"└───┘ ", "╚═══╝ "},
        {"└─┴─┘ ", "╚═╧═╝ "},
        {"│   │ ", "║   ║ "},
        {"├   ┤ ", "╟   ╢ "}
    };
    char *plansza_w_budowie[8*3][8];
    
    //petla nr 1: sprawdza z jakich elementow maja skladac sie pola na planszy i je zapisuje
    for (int i=0; i<8;i++)
    {
        for (int k=0;k<8;k++)
        {
            //do zrobienia: sprawdzanie czy pole i,k zawiera ktoras figure/miejsce, gdzie poruszy sie przeciwnik/miejsce do ruszenia sie skoczka/
            //do zrobienia: wstawienie do odpowiednika i,k wlasciwego klocka
            //poki co: budowanie pustej planszy
            plansza_w_budowie[i*3+0][k]=tablica_klockow[0][0];
            plansza_w_budowie[i*3+1][k]=tablica_klockow[4/*+cos*/][0];
            plansza_w_budowie[i*3+2][k]=tablica_klockow[2][0];
        }
        printf("\n");
    }

    //petla nr 2: wypisuje plansze
    for (int i=0; i<24;i++)
    {
        for (int j=0;j<8;j++)
        {
            //do zrobienia: kolorki
            printf("%s", plansza_w_budowie[i][j]);
        }
        printf("\n");
    }
}

//pomysly do uwzglednienia:
//moze lepiej zrobic jedna petle i wypisywac od razu przy sprawdzeniu??? chyba oszczedniejsze, ale wydaje mi sie to byc brzydkim rozwiazaniem
//pytanie: jak w map[8][8] zapisac, ze na jednym polu jest i przeciwnik, i inny przeciwnik chce sie tam poruszyc, i jeszcze skoczek moze tam skoczyc??? moze binarnie?? np 01000010 - wieza i mozna skoczyc
//serio ktos to czyta??? jesli tak, to pozdro
//jesli czyta to Andrei, to super robota z tymi lib.h i reszta
//czy drugi rząd danego pola budować z trzech różnych elementów (sciana, pionek, sciana) czy przygotować elementy na kazdego pionka???
//jak szybko skoncze - animacja?? wyswietla sie najpierw plansza z samymi figurami, potem dodatkowo gdzie celuja przeciwnicy, a na koniec gdzie moze skoczyc skoczek


/*
int main()
{
    int test;
    scanf("%d", &test);
    set_output();
    test=test;
    return 0;
}
    */


