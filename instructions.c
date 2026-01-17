#include "lib.h"
#include <stdio.h>

void show_instructions(){
    printf("Oto instrukcja poruszania się. Numer w danej pozycji oznacza, że klikcięcio go wykona ruch skoczka na tę pozycję\n");
    printf("#-------#\n");
    printf("|       |\n");
    printf("|  3 2  |\n");
    printf("| 4   1 |\n");
    printf("|   0   |\n");
    printf("| 5   8 |\n");
    printf("|  6 7  |\n");
    printf("|       |\n");
    printf("#-------#\n");
    printf("Klawisz 'p' otwiera menu pauzy\n\n");

    printf("Wpisz dowolny klawisz aby kontynuować do poprzedniego widoku\n");
    char c;
    while(true){
        if(scanf(" %c", &c) == 1) return;
    }
}