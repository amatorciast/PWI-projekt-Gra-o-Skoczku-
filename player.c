#include "lib.h"
#include <stdio.h>

//Game_info game;

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
}


//WAŻNE! dla testów odkomentuj Game_info game; w 4 linijce
/*
int main() {
    game.x = 3;
    game.y = 3;
    int tab[8][8];
    int d;
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
    }

    while (1) {
        scanf(" %d", &d);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j ++) {
                tab[i][j] = '.';
            }
        }
        player_move(d);
        tab[game.y][game.x] = 'P';

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j ++) {
                printf("%c ", tab[i][j]);
            }
            printf("\n");
        }

    }
    
*/
}