#include "lib.h"
#define START_X 0
#define START_Y 0

Game_info game;

int main(){
    int input;
    
    game.is_started = false;
    game.score = 0;
    game.since_last_enemy = 0;
    game.difficulty = 0;

    while(!game.is_started){
        menu_check();
    }
    
    enemy_init(); //nowe i ważne
    while(true){
        input = get_input();
        set_output();
        print_score_quick();
        //gracz i przeciwnicy najwyraźniej poruszają się jednocześnie
        if(input <= 8 && input>=0){
            game.score++;
            player_move(input);
            set_output();
            print_score_quick();
            enemy_move();
            enemy_deside_if_to_bother_living(game.score);
            set_output();
            print_score_quick();
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


