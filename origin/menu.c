#include "lib.h"
#include <stdio.h>
#include <string.h>

void save(Game_info* game) {
    cease();
    printf("Podaj nazwę pliku, w którym chcesz zapisać stan gry (maks 64 znaki):\n");
    char file_name[100];
    scanf(" %64s", file_name);
    strcat(file_name, ".txt");

    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        save_error(1); 
    }
    // zapisywanie enemies
    for(int i = 0; i < 64; i++){
        enemy e = game->enemies[i];
        fprintf(file, "%d %d %d %d %d %d \n", e.alive, e.curr_x, e.curr_y, e.next_x, e.next_y, e.figure);
    }
    // zapisywanie x, y; is_started; score; since_last_enemy; difficulty
    fprintf(file, "%d %d %d %d %d %d \n", game->x, game->y, game->is_started, game->score, game->since_last_enemy, game->difficulty);
    // zapisywanie score_list
    for(int i=0; i<10; i++) {
        fprintf(file, "%d\n", game->score_list[i]);
    }

    fclose(file);
    printf("Gra zostałą zapisana do pliku %s.\n", file_name);
    printf("wpisz dowolny klawisz aby kontynuować do trwającej gry\n");
    char order;
    while(true) {
        if (scanf(" %c", &order)) return;
    }
}

void save_error(int error_type){
    cease();
    // 0 - is_started == 0
    // 1 - błąd otwarcia pliku
    cease();
    if(error_type == 1) printf("Błąd otwarcia pliku do zapisu\n");
    else printf("Nie ma rozpoczętej gry do zapisania\n");
    printf("Wpisz dowolny klawisz aby kontynuować do poprzedniego widoku\n");
    char order;
    while(true) {
        if (scanf(" %c", &order)) return;
    }
}

int load(Game_info* game) {
    cease();
    printf("Podaj nazwę pliku, z którego chcesz wczytać stan gry:\n");
    char file_name[100];
    scanf(" %64s", file_name);
    strcat(file_name, ".txt");

    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        load_error(1);
        return 0;
    }
    // wczytywanie enemies
    int temp_alive;
    for(int i = 0; i < 64; i++){
        enemy* e = &game->enemies[i];
        fscanf(file, "%d %d %d %d %d %d", &temp_alive, &e->curr_x, &e->curr_y, &e->next_x, &e->next_y, &e->figure);
        e->alive = (bool)temp_alive;
    }
    // wczytywanie x, y; is_started; score; since_last_enemy; difficulty
    fscanf(file, "%d %d %d %d %d %d", &game->x, &game->y, &game->is_started, &game->score, &game->since_last_enemy, &game->difficulty);
    // wczytywanie score_list
    for(int i=0; i<10; i++) {
        fscanf(file, " %d", &game->score_list[i]);
    }

    fclose(file);
    printf("Gra zostala pomyślnie wczytana z pliku %s.\n", file_name);
    printf("wpisz dowolny klawisz aby kontynuować do wczytanej gry\n");
    char order;
    while(true) {
        if (scanf(" %c", &order)) return 1;
    }
}

void load_error(int error_type){
    cease();
    // 0 - błąd podczas wczytywania pliku
    // 1 - błąd otwarcia pliku
    if(error_type == 1) printf("Błąd podczas otwierania pliku do wczytania. Najprawdopodobniej plik z podaną nazwą nie istnieje\n");
    else printf("Błąd podczas wczytywania zawartości pliku\n");
    printf("wpisz dowolny klawisz aby kontynuować do poprzedniego widoku\n");
    char order;
    while(true) {
        if (scanf(" %c", &order)) return;
    }
}

void print_score_quick() {
    printf("Score: %d\n", game.score);
    return;
}

void pause() {
    int selection = 0;
    int menu_input;
    print_pause(selection);
    while(true){
        menu_input  = get_input();
        int menu_update = 0
        if (menu_input == 0 || menu_input == 1) return menu_input; // sa dwa sposoby na wybranie opcji, standardowe wczesniejsze wcisniecie 0-1 lub nowe "a","d" i spacja 
        if(menu_input == 11  || menu_input == 12){
            menu_update = 1;
            if(selection == 0) selection = 1;
            else selection = 0;
        }
        if(menu_update) print_pause(selection);
        if(menu_input == 10) return selection;
    }
}

int menu() {
    int selection = 0;
    int menu_input;
    print_menu(selection);
    while(true) {
        menu_input  = get_input();
        int menu_update = 0
        if (menu_input >= 0 && menu_input <= 5) return menu_input; 
        if(menu_input == 11){
            if (selection == 0) selection = 5;
            else selection--;
            menu_update = 1;
        }
        if(menu_input == 12){
            if (selection == 5) selection = 0;
            else selection++;
            menu_update = 1;
        }
        if(menu_update) print_menu(selection);
        if(menu_input == 10) return selection;
    }
}

void game_reset() {
    enemy_init();
    game.x = 0;
    game.y = 0;
    game.is_started = 0;
    game.score = 0;
    game.since_last_enemy = 0;
    game.difficulty = 0;
}

int zgon() {
    int selection = 0;
    int menu_input;
    print_zgon(selection);
    add_score(game.score, game.score_list);
    game_reset();
    
    while(true){
        menu_input = get_input();
        int menu_update = 0;
        if (menu_input >= 0 && menu_input <= 2) return menu_input; 
        if(menu_input == 11){
            if (selection == 0) selection = 2;
            else selection--;
            menu_update = 1;
        }
        if(menu_input == 12){
            if (selection == 2) selection = 0;
            else selection++;
            menu_update = 1;
        }
        if(menu_update) print_zgon(selection);
        if(menu_input == 10) return selection;
    }
}