#include "lib.h"
#define START_X 4
#define START_Y 4

Game_info game;

int main(){
    int input;
    score_list_init(game.score_list);
    
    game_reset();

    while(!game.is_started){
        menu_check();
    }
    
    while(true){
        input = get_input();
        set_output();
        print_score_quick();
        //Wykonanie ruchu gracza, a następnie przeciwników
        if(input <= 8 && input>=0){
            if(player_move(input) == 1){
                game.score++;
                set_output();
                print_score_quick();
                enemy_move();
                check_for_death_realization();
                enemy_deside_if_to_bother_living(game.score);
                set_output();
                print_score_quick();
            }
            else{
                input_error();
            }
        }else if(input==9){
            pause();
        }
    }

    end_game();
    return 0;
}


