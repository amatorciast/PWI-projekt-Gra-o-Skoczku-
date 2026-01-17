#include "lib.h"
#include <stdio.h>

void show_instructions(){
    printf("Oto instrukcja poruszania się. Numer w danej pozycji oznacza, że klikcięcio go wykona ruch skoczka na tę pozycję\n");
    printf("#-------#\n");
    printf("|       |\n");
    printf("|  8 1  |\n");
    printf("| 7   2 |\n");
    printf("|   0   |\n");
    printf("| 6   3 |\n");
    printf("|  5 4  |\n");
    printf("|       |\n");
    printf("#-------#\n");
    printf("Klawisz 'p' otwiera menu pauzy\n\n");

    printf("Wpisz dowolny klawisz aby kontynuować do poprzedniego widoku\n");
    char c;
    while(true){
        if(scanf(" %c", &c) == 1) return;
    }
}