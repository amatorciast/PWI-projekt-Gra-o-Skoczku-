#include "lib.h"
#define START_X 0
#define START_Y 0

Game_info game;

int main(){
    int input;
    game.is_started = false;

    while(!game.is_started){
        menu_check();
    }

    enemy_init(); //nowe i ważne
    while(true){
        input = get_input();
        //gracz i przeciwnicy najwyraźniej poruszają się jednocześnie
        if(input <= 7){
            player_move(input);
            enemy_move();
            set_output();
        }else{
            if(pause()){
                while(!game.is_started){
                    menu_check();
                }
            }
        }
    }

    end_game();
    return 0;
}