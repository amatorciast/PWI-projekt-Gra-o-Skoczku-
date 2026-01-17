#include "lib.h"
#include <stdio.h>


void player_move(int direction) {
    switch (direction) {
        case 1:
        if (game.x >= 2 && game.y <= 6) {
            game.x -= 2;
            game.y ++;
        }        
        break;

        case 2:
        if (game.x >= 1 && game.y <= 6) {
            game.x --;
            game.y += 2;
        }
        break;

        case 3:
        if (game.x <= 6 && game.y <= 5) {
            game.x ++;
            game.y += 2;
        }
        break;

        case 4:
        if (game.x <= 5 && game.y <= 6) {
            game.x += 2;
            game.y ++;
        }
        break;

        case 5:
        if (game.x <= 5 && game.y >= 1) {
            game.x += 2;
            game.y --;
        }
        break;

        case 6:
        if (game.x <= 6 && game.y >= 2) {
            game.x ++;
            game.y -= 2;
        }        
        break;

        case 7:
        if (game.x >= 1 && game.y >= 2) {
            game.x --;
            game.y -= 2;
        } 
        break;

        case 8:
        if (game.x >= 2 && game.y >= 1) {
            game.x -= 2;
            game.y --;
        } 
        break;
    }

    for (int i=0; i < 64; i++){
        if (game.enemies[i].alive == 1  &&  game.enemies[i].curr_x == game.x  &&  game.enemies[i].curr_y == game.y)
            enemy_death(i);
            // i moznaby doliczyc punkty do score w tym miejscu moze?
    }
}


//WAŻNE! dla testów odkomentuj Game_info game; w 4 linijce
/*
int main() {
    game.x = 3;
    game.y = 3;
    int d;
    int tab[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j ++) {
            tab[i][j] = '.';
        }
    }
    tab[game.y][game.x] = 'P';
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j ++) {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }*/
    /*
    set_output();

    while (1) {
        scanf(" %d", &d);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j ++) {
                tab[i][j] = '.';
            }
        }
        //player_move(d);
        tab[game.y][game.x] = 'P';

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j ++) {
                printf("%c ", tab[i][j]);
            }
            printf("\n");
        }*/
        //set_output();

    //}
    

//}
