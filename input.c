#include "lib.h"
#include "set_input.h"
#include <stdio.h>

int get_input(){
    char ch = getchar();

    switch(ch){
        case input_0:
        return 0;
        case input_1:
        return 1;
        case input_2:
        return 2;
        case input_3:
        return 3;
        case input_4:
        return 4;
        case input_5:
        return 5;
        case input_6:
        return 6;
        case input_7:
        return 7;
        case input_8:
        return 8;
        case input_9:
        return 9;
    }
    return -1; //nieprawidłowy input
}