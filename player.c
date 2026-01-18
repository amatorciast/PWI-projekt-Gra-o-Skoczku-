#include "lib.h"
#include <stdio.h>

bool player_move(int direction) {
    bool is_move_possible = 1;
    switch (direction) {
        case 1:
        if (game.x >= 2 && game.y <= 6) {
            game.x -= 2;
            game.y ++;
        }
        else is_move_possible = 0;
        break;

        case 2:
        if (game.x >= 1 && game.y <= 6) {
            game.x --;
            game.y += 2;
        }
        else is_move_possible = 0;
        break;

        case 3:
        if (game.x <= 6 && game.y <= 5) {
            game.x ++;
            game.y += 2;
        }  
        else is_move_possible = 0;
        break;

        case 4:
        if (game.x <= 5 && game.y <= 6) {
            game.x += 2;
            game.y ++;
        }  
        else is_move_possible = 0;
        break;

        case 5:
        if (game.x <= 5 && game.y >= 1) {
            game.x += 2;
            game.y --;
        }  
        else is_move_possible = 0;
        break;

        case 6:
        if (game.x <= 6 && game.y >= 2) {
            game.x ++;
            game.y -= 2;
        }
        else is_move_possible = 0;
        break;

        case 7:
        if (game.x >= 1 && game.y >= 2) {
            game.x --;
            game.y -= 2;
        }
        else is_move_possible = 0;
        break;

        case 8:
        if (game.x >= 2 && game.y >= 1) {
            game.x -= 2;
            game.y --;
        }
        else is_move_possible = 0;
        break;
    }

    if(is_move_possible == 1){
        for (int i=0; i < 64; i++){
            if (game.enemies[i].alive == 1  &&  game.enemies[i].curr_x == game.x  &&  game.enemies[i].curr_y == game.y) {
                enemy_death_score(i);
                enemy_death(i);
            }
        }
        return 1;
    }
    else return 0;
}


