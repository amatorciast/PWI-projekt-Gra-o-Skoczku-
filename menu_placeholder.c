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

void print_score_quick() {
    printf("Score: %d\n", game.score);
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
    printf("Wybierz opcję:\n0: start\n1: zapisz\n2: wczytaj\n3: wypisz wynik\n4: zakończ\n5: instrukcja\n");
    int order;
    while(1) {
        if (scanf(" %d", &order) && (order == 0 || order == 1 || order == 2 || order == 3 || order == 4 || order == 5)) return order;
    }
    return -1;
    //działa tylko 0 i 4 - reszta to nie moja działka
    
}

void game_reset() {
    for (int i= 0; i < 64; i ++) {
        enemy_death(i);
    }
    game.x = 0;
    game.y = 0;
    game.is_started = 0;
    game.score = 0;
    game.since_last_enemy = 0;
    game.difficulty = 0;
}

void zgon() {
    printf("Doświadczasz śmierci z wynikiem %d.\nWybierz opcję:\n0: zagraj ponownie\n1: menu\n2: zakończ\n", game.score);
    game_reset();
    int order;
    while (1) {
        if (scanf(" %d", &order)) {
            switch(order) {
                case 0:
                return;
                break;
                case 1:
                menu();
                break;
                case 2:
                end_game();
                break;
            }
        }
        }
    }

