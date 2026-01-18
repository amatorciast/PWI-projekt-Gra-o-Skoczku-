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
    // 0 - is_started == 0
    // 1 - błąd otwarcia pliku
    if(error_type == 1) printf("Błąd otwarcia pliku do zapisu\n");
    else printf("Nie ma rozpoczętej gry do zapisania\n");
    printf("wpisz dowolny klawisz aby kontynuować do poprzedniego widoku\n");
    char order;
    while(true) {
        if (scanf(" %c", &order)) return;
    }
}

int load(Game_info* game) {
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
    printf("Wybierz opcję:\n0: resume\n1: menu\n");
    int order;
    while(true) {
        if (scanf(" %d", &order)){
            if (order == 0)  return;
            else if (order == 1){
                menu_check();
                return;
            }
            else printf("Niepoprawna liczba, wybierz 0 lub 1: ");
        } else{
            printf("Nie wprowadziłeś liczby, wybierz 0 lub 1: ");
            //Jeśli wejście nie jest liczbą to trzeba wyczyścić bufor, bo scanf ciągle próbuje wczytać inta, ciągle mu się to nie udaje, bo w buforze jest inny znak i program utyka w miejscu
            while (getchar() != '\n');
        }
    }

    return;
}

int menu() {
    printf("\e[1;1H\e[2J\e[3J");
    printf("Wybierz opcję:\n0: start\n1: zapisz\n2: wczytaj\n3: wypisz wynik\n4: zakończ\n5: instrukcja\n");
    int order;
    while(true) {
        if (scanf(" %d", &order)){
            if (order == 0 || order == 1 || order == 2 || order == 3 || order == 4 || order == 5) return order;
            else printf("Niepoprawna liczba, wybierz liczbę od 0 do 5: ");
        } else{
            printf("Nie wprowadziłeś liczby, wybierz liczbę od 0 do 5: ");
            //Jeśli wejście nie jest liczbą to trzeba wyczyścić bufor, bo scanf ciągle próbuje wczytać inta, ciągle mu się to nie udaje, bo w buforze jest inny znak i program utyka w miejscu
            while (getchar() != '\n');
        }
    }
    return -1;
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
    printf("Doświadczasz śmierci z wynikiem %d.\nWybierz opcję:\n0: zagraj ponownie\n1: menu\n2: zakończ\n", game.score);
    add_score(game.score, game.score_list);
    game_reset();
    int order;
    while(true) {
        if (scanf(" %d", &order)) {
            if(order == 0 || order == 1) return order;
            else if(order == 2) end_game();
            else printf("Niepoprawna liczba, wybierz 0, 1 lub 2: ");
        } else{
            printf("Nie wprowadziłeś liczby, wybierz 0, 1 lub 2: ");
            //Jeśli wejście nie jest liczbą to trzeba wyczyścić bufor, bo scanf ciągle próbuje wczytać inta, ciągle mu się to nie udaje, bo w buforze jest inny znak i program utyka w miejscu
            while (getchar() != '\n');
        }
    }
}

