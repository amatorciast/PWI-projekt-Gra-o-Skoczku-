#include "lib.h"
#include <stdio.h>

int get_input(){
    int ch = getchar();
    if (ch >= '0' && ch <= '8'){
        return ch - '0'; //0-8: ruchy skoczka
    }
    else if (ch == 'p' || ch == 'P'){
        return 9; //pauza
    }
    return -1; //nieprawidłowy input
}

void input_error(){
    printf("Nie możesz wyjść poza planszę\n");
    printf("wpisz dowolny klawisz aby kontynuować i wprowadzić prawidłowy ruch\n");
    char order;
    while(true) {
        if (scanf(" %c", &order)) break;
    }
}