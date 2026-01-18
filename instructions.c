#include "lib.h"
#include "set_input.h"
#include <stdio.h>

void show_instructions(){
    printf("Oto instrukcja poruszania się. Numer w danej pozycji oznacza, że klikcięcio go wykona ruch skoczka na tę pozycję\n");
    printf("#-------#\n");
    printf("|       |\n");
    printf("|  %c %c  |\n", input_8, input_1);
    printf("| %c   %c |\n", input_7, input_2);
    printf("|   %c   |\n", input_0);
    printf("| %c   %c |\n", input_6, input_3);
    printf("|  %c %c  |\n", input_5, input_4);
    printf("|       |\n");
    printf("#-------#\n");
    printf("Klawisz '%c' otwiera menu pauzy\n\n", input_9);

    printf("Wpisz dowolny klawisz aby kontynuować do poprzedniego widoku\n");
    char c;
    while(true){
        if(scanf(" %c", &c) == 1) return;
    }
}