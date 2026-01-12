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
        if(input <= 8 && input>=0){
            player_move(input);
            set_output();
            enemy_move();
            set_output();
        }else if(input==9){
            game.is_started = false;
            if(pause()){
                menu_check();
            } else game.is_started = true;
        }
    }

    end_game();
    return 0;
}
    
/*
int main(){
    int input;
    
    enemy_init(); //nowe i ważne
    while(true){
        input = get_input();
        if(input <= 8 && input>=0){
            player_move(input);
            set_output();
            enemy_move();
            enemy_spawn();
            set_output();
        }
    }

    end_game();
    return 0;
}
    */


