#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enemy enemies[64];

void enemy_init() {
    srand(time(NULL));
    for (int i = 0; i < 64; i++) {
        enemies[i].alive = 0;
    }
}

void enemy_spawn() {
    for (int i = 0; i < 64; i++) {
        if (enemies[i].alive == 0) {
            enemies[i].alive = 1;
            enemies[i].curr_x = -1;
            enemies[i].curr_y = -1;
            enemies[i].figure = rand() % 5;
            if (enemies[i].figure != 0) {
                enemies[i].next_x = rand() % 8;
                enemies[i].next_y = rand() % 8;
            } else {
                //pionki są specjalne
                enemies[i].next_y = 0;
                enemies[i].next_x = rand() % 8;
            }
            return;
        }
    }
}

void enemy_death(int indx) {
    enemies[indx].alive = 0;
}

void enemy_move() {
    for (int i = 0; i < 64; i++) {
        if (enemies[i].alive == 1) {
            if (enemies[i].next_x > 7 || enemies[i].next_x < 0 || enemies[i].next_y > 7 || enemies[i].next_y < 0) {
                enemy_death(i);
                continue;
            }
            enemies[i].curr_x = enemies[i].next_x;
            enemies[i].curr_y = enemies[i].next_y;
            if (enemies[i].figure == 0) {
                //pionek
                enemies[i].next_x = enemies[i].curr_x;
                enemies[i].next_y = enemies[i].curr_y + 1;
            } else if (enemies[i].figure == 1) {
                //wieza
                if (rand()%2 == 0) enemies[i].next_x = enemies[i].curr_x + (rand()%15) - 8;
                else enemies[i].next_y = enemies[i].curr_y + (rand()%15) - 8;
 
            } else if (enemies[i].figure == 2) {
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
                enemies[i].next_x = enemies[i].curr_x + temp_x;
                if (rand()%2 == 1) temp_y *= -1;
                enemies[i].next_y = enemies[i].curr_y + temp_y;

                
            } else if (enemies[i].figure == 3) {
                //biskup
                int temp = rand() % 8;
                if (rand()%2 == 1) temp *= -1;
                enemies[i].next_x = enemies[i].curr_x + temp;
                if (rand()%2 == 1) temp *= -1;
                enemies[i].next_y = enemies[i].curr_y + temp;
            } else if (enemies[i].figure == 4) {
                //hetman
                if (rand()%2 == 1) {
                    int temp = rand() % 8;
                    if (rand()%2 == 1) temp *= -1;
                    enemies[i].next_x = enemies[i].curr_x + temp;
                    if (rand()%2 == 1) temp *= -1;
                    enemies[i].next_y = enemies[i].curr_y + temp;
                } else {
                    if (rand()%2 == 0) enemies[i].next_x = enemies[i].curr_x + (rand()%15) - 8;
                    else enemies[i].next_y = enemies[i].curr_y + (rand()%15) - 8;
                }
            }
        }
    }
}

/* poniżej test i proof of concept, że działa
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
    */