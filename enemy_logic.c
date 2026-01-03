#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Game_info game;

void enemy_init() {
    srand(time(NULL));
    for (int i = 0; i < 64; i++) {
        game.enemies[i].alive = 0;
    }
}

void enemy_spawn() {
    for (int i = 0; i < 64; i++) {  
        if (game.enemies[i].alive == 0) {
            game.enemies[i].alive = 1;
            game.enemies[i].curr_x = -1;
            game.enemies[i].curr_y = -1;
            game.enemies[i].figure = rand() % 5;
            if (game.enemies[i].figure != 0) {
                game.enemies[i].next_x = rand() % 8;
                game.enemies[i].next_y = rand() % 8;
            } else {
                //pionki są specjalne
                game.enemies[i].next_y = 0;
                game.enemies[i].next_x = rand() % 8;
            }
            return;
        }
    }
}

void enemy_death(int indx) {
    game.enemies[indx].alive = 0;
}

void enemy_move() {
    for (int i = 0; i < 64; i++) {
        if (game.enemies[i].alive == 1) {
            if (game.enemies[i].next_x > 7 || game.enemies[i].next_x < 0 || game.enemies[i].next_y > 7 || game.enemies[i].next_y < 0) {
                enemy_death(i);
                continue;
            }
            game.enemies[i].curr_x = game.enemies[i].next_x;
            game.enemies[i].curr_y = game.enemies[i].next_y;
            if (game.enemies[i].figure == 0) {
                //pionek
                game.enemies[i].next_x = game.enemies[i].curr_x;
                game.enemies[i].next_y = game.enemies[i].curr_y + 1;
            } else if (game.enemies[i].figure == 1) {
                //wieza
                if (rand()%2 == 0) game.enemies[i].next_x = game.enemies[i].curr_x + (rand()%15) - 8;
                else game.enemies[i].next_y = game.enemies[i].curr_y + (rand()%15) - 8;
 
            } else if (game.enemies[i].figure == 2) {
                //skoczek
                int temp_x = rand() % 2;
                int temp_y;
                if (temp_x == 1) {
                    temp_x = 2;
                    temp_y = 1;
                } else {
                    temp_x = 1;
                    temp_y = 2;
                }
                if (rand()%2 == 1) temp_x *= -1;
                game.enemies[i].next_x = game.enemies[i].curr_x + temp_x;
                if (rand()%2 == 1) temp_y *= -1;
                game.enemies[i].next_y = game.enemies[i].curr_y + temp_y;

                
            } else if (game.enemies[i].figure == 3) {
                //biskup
                int temp = rand() % 8;
                if (rand()%2 == 1) temp *= -1;
                game.enemies[i].next_x = game.enemies[i].curr_x + temp;
                if (rand()%2 == 1) temp *= -1;
                game.enemies[i].next_y = game.enemies[i].curr_y + temp;
            } else if (game.enemies[i].figure == 4) {
                //hetman
                if (rand()%2 == 1) {
                    int temp = rand() % 8;
                    if (rand()%2 == 1) temp *= -1;
                    game.enemies[i].next_x = game.enemies[i].curr_x + temp;
                    if (rand()%2 == 1) temp *= -1;
                    game.enemies[i].next_y = game.enemies[i].curr_y + temp;
                } else {
                    if (rand()%2 == 0) game.enemies[i].next_x = game.enemies[i].curr_x + (rand()%15) - 8;
                    else game.enemies[i].next_y = game.enemies[i].curr_y + (rand()%15) - 8;
                }
            }
        }
    }
}

//poniżej test i proof of concept, że działa
//WAŻNE! dla testów odkomentuj deklarację Game_info game; w 6 linijce 
int main() {
    enemy_init();
    char order;
    while (scanf(" %c", &order)) {
        if (order == 't') {
            enemy_move();
            
            set_output(); //teraz mozna testowac i logike przeciwnikow i output

        } else if (order == 's') {
            enemy_spawn();
        }
    }
}
