#include "lib.h"
#include <stdio.h>

void save(Game_info) {
    return;
}
void save_error() {
    return;
}
Game_info load() {
    Game_info dummy;
    dummy.is_started = 0;
    return dummy;
}
void print_score() {
    return;
}

int pause() {
    printf("Wybierz opcję:\n0: resume\n1: menu\n");
    int order;
    while (1) {
        if (scanf(" %d", &order) && (order == 0 || order == 1)) return order;
    }
    return -1;

}

int menu() {
    printf("\e[1;1H\e[2J\e[3J");
    printf("Wybierz opcję:\n0: start\n1: zapisz\n2: wczytaj\n3: wypisz wynik\n4: zakończ\n");
    int order;
    while(1) {
        if (scanf(" %d", &order) && (order == 0 || order == 1 || order == 2 || order == 3 || order == 4)) return order;
    }
    return -1;
    //działa tylko 0 i 4 - reszta to nie moja działka
    
}
