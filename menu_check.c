#include "lib.h"

void menu_check(){
    switch(menu()){
            case 0:
            start_game();
            break;

            case 1:
            if(game.is_started){
                save(&game);
            }else{
                save_error(0);
            }
            break;

            case 2:
            game = load();
            break;
            
            case 3:
            print_score();
            break;

            case 4:
            end_game();
            break;
        }
}