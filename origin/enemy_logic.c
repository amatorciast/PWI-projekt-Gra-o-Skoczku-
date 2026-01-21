#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void enemy_death(int indx) {
    game.enemies[indx].alive = 0;
}

void enemy_init() {
    srand(time(NULL));
    for (int i = 0; i < 64; i++) {
        enemy_death(i);
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

void enemy_deside_if_to_bother_living(int score) {
    score=score;
    game.since_last_enemy++;
    game.difficulty += 1;
    
    if (rand()%100 < game.difficulty || game.since_last_enemy >= 5) enemy_spawn();
    if (game.difficulty >= 200) enemy_spawn();
    if (game.difficulty >= 300) enemy_spawn();
}

int check_for_death() {
    for (int i = 0; i < 64; i ++) {
        if (game.enemies[i].alive == 1) {
            if (game.enemies[i].curr_x == game.x && game.enemies[i].curr_y == game.y) {
                return zgon();
            }
            for (int j = 0; j < 64; j ++) {
                if (game.enemies[j].alive && j != i) {
                    if (game.enemies[j].curr_x == game.enemies[i].curr_x && game.enemies[j].curr_y == game.enemies[i].curr_y) {
                        enemy_death(j);
                    }
                }
            }
        }
        
    }
    return 0;
}

void check_for_death_realization(){
    if(check_for_death() == 0) start_game();
    else if(check_for_death() == 1) menu_check();
    else if(check_for_death() == 2) end_game();
    //Jeżeli check_for_death == 0 to:
    //-gracz nie umarł i gra toczy się dalej
    //-gracz umarł, ale wybrał "zagraj_ponownie", wtedy muszę ustawić game.is_started na prawdę
    //Jeżeli check_for_death == 1 to:
    //-gracz umarł i w ekranie śmierci wybrał "menu"
    //Jeżeli check_for_death == 2 to:
    //-gracz umarł i w ekranie śmierci wybrał "koniec gry"
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
                    if(game.difficulty <= 50){//losowe ruchy
                        if (rand()%2 == 0) game.enemies[i].next_x = game.enemies[i].curr_x + (rand()%15) - 8;
                        else game.enemies[i].next_y = game.enemies[i].curr_y + (rand()%15) - 8;
                    } else if(game.difficulty <= 100){//wieża wchodzi na wspólną linię z naszym skoczkiem. Jeżeli już na niej jest to jest 50% szans, że zbije skoczka
                        if (rand()%2 == 0) game.enemies[i].next_x = game.x;
                        else game.enemies[i].next_y = game.y;                          
                    } else if(game.difficulty <= 150){//jeżeli wieża nie jest na wspólnej lini ze skoczkiem to na nią wchodzi. Jeżeli jest na wspólnej lini to na 75% zbije skoczka
                        if (rand()%2 == 0){
                            if (rand()%2 == 0) game.enemies[i].next_x = game.x;
                            else game.enemies[i].next_y = game.y;                              
                        } else{
                            if(game.enemies[i].next_x == game.x) game.enemies[i].next_y = game.y;
                            else if(game.enemies[i].next_y == game.y) game.enemies[i].next_x = game.x;
                            else{
                                if (rand()%2 == 0) game.enemies[i].next_x = game.x;
                                else game.enemies[i].next_y = game.y;                                   
                            }
                        }     
                    } else{//wieża zawsze dąży do zbicia skoczka
                        if(game.enemies[i].next_x == game.x) game.enemies[i].next_y = game.y;
                        else if(game.enemies[i].next_y == game.y) game.enemies[i].next_x = game.x;
                        else{
                            if (rand()%2 == 0) game.enemies[i].next_x = game.x;
                            else game.enemies[i].next_y = game.y;                              
                        }                   
                    }

                    
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
                int temp = rand() % 4; //zamieniłem 8 na 4, bo jak jest 8 to szansa na to, że goniec zostanie na planszy i zrobi pożytek dla przeciwników jest bardzo mała
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
