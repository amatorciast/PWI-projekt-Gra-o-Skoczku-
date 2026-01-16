#include "lib.h"
#include <stdio.h>
#include <string.h>

void save(Game_info* game) {
    printf("Podaj nazwę pliku, w którym chcesz zapisać stan gry (maks 64 znaki):\n");
    char file_name[100];
    scanf(" %64s", file_name);
    strcat(file_name, ".txt");

    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        save_error(1); 
    }

    // zapisywanie map
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            fprintf(file, "%c ", game->map[i][j]);
        }
        fprintf(file, "\n");
    }
    // zapisywanie enemies
    for(int i = 0; i < 64; i++){
        enemy e = game->enemies[i];
        fprintf(file, "%d %d %d %d %d %d \n", e.alive, e.curr_x, e.curr_y, e.next_x, e.next_y, e.figure);
    }
    // zapisywanie x, y; is_started; score; since_last_enemy; difficulty
    fprintf(file, "%d %d %d %d %d %d \n", game->x, game->y, game->is_started, game->score, game->since_last_enemy, game->difficulty);

    fclose(file);
    printf("Gra zostałą zapisana.\n");
    printf("wpisz dowolny klawisz aby kontynuować do trwającej gry\n");
    char order;
    while (1) {
        if (scanf(" %c", &order)) return;
    }
}

void save_error(int error_type){
    // 0 - is_started == 0
    // 1 - błąd otwarcia pliku
    if(error_type) printf("Błąd otwarcia pliku do zapisu\n");
    else printf("Nie ma rozpoczętej gry do zapisania\n");
    printf("wpisz dowolny klawisz aby kontynuować do pustego menu\n");
    char order;
    while (1) {
        if (scanf(" %c", &order)) return;
    }
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
    printf("Wybierz opcję:\n0: start\n1: zapisz\n2: wczytaj\n3: wypisz wynik\n4: zakończ\n");
    int order;
    while(1) {
        if (scanf(" %d", &order) && (order == 0 || order == 1 || order == 2 || order == 3 || order == 4)) return order;
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

