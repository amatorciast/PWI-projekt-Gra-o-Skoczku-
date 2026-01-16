#include "lib.h"
#include <stdio.h>

void player_move(int direction) {
    switch (direction) {
        case 1:
        if (game.x >= 1 && game.y <= 6) {
            game.x --;
            game.y += 2;
        }
        break;
        case 2:
        if (game.x >= 2 && game.y <= 6) {
            game.x -= 2;
            game.y ++;
        }
        break;
        case 3:
        if (game.x >= 2 && game.y >= 1) {
            game.x -= 2;
            game.y --;
        }
        break;
        case 4:
        if (game.x >= 1 && game.y >= 2) {
            game.x --;
            game.y -= 2;
        }
        break;
        case 5:
        if (game.x <= 6 && game.y >= 2) {
            game.x ++;
            game.y -= 2;
        }
        break;
        case 6:
        if (game.x <= 5 && game.y >= 1) {
            game.x += 2;
            game.y --;
        }
        break;
        case 7:
        if (game.x <= 5 && game.y <= 6) {
            game.x += 2;
            game.y ++;
        }
        break;
        case 8:
        if (game.x <= 6 && game.y <= 5) {
            game.x ++;
            game.y += 2;
        }
        break;
    }

    for (int i=0; i < 64; i++){
        if (game.enemies[i].alive == 1  &&  game.enemies[i].curr_x == game.x  &&  game.enemies[i].curr_y == game.y)
            enemy_death(i);
    }
}
