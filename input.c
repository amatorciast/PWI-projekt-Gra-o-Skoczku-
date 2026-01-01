#include "lib.h"
#include <stdio.h>

int get_input(){
    int ch = getchar();
    if (ch >= '0' && ch <= '7'){
        return ch - '0';
    }
    else if (ch == 'p' || ch == 'P'){
        return 8; //pause
    }
    return -1; //nieprawidłowy input
}