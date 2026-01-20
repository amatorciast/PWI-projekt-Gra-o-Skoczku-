#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// sprawdza czy ma uzywac komendy windowsa czy linuxa
#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

void cease(){
    system(CLEAR_CMD);
} // dodalem zeby czyscic screen dla funkcji do ktorych nie bylem na tyle odwazny zeby zmieniac
void print_menu(int selection){ // zwykle menu
    cease();
    printf("  ____                     ____  _                  _          \n");
    printf(" / ___|_ __ __ _    ___   / ___|| | _____   ___ ___| | ___   _  \n");
    printf("| |  _| '__/ _` |  / _ \\  | |__ | |/ / _ \\ / __|_  / |/ / | | |\n");
    printf("| |_| | | | (_| | | (_) |  ___) |   < (_) | (__ / /|   <| |_| |\n");
    printf(" \\____|_|  \\__,_|  \\___/  |____/|_|\\_\\___/ \\___/___|_|\\_\\\\__,_|\n");
    printf("\n");
    // napisane w paru printf zamiast jednego dla latwiejszej czytelnosci kodu
    printf("| Start || Save  || Load  || Scores|| Exit  || Inst  |\n");
    for( int i = 0; i < selection; i++) printf("         "); // sprawdza na jakim selection jestesmy i przesuwa o tyle
    printf("^\n");
}
void print_pause(int selection){ // menu pause
    cease();
    printf(" ____                          _ \n");
    printf("|  _ \\ __ _ _   _ ___  ___  __| |\n");
    printf("| |_)|/ _` | | | / __|/ _ |/ _` |\n");
    printf("|  __/ (_| | |_| |__ |  __/ (_| |\n");
    printf("|_|   |__,_|__,__|___/|___||__,_|\n");
    printf("\n");
    printf("|Resume||Menu|\n");
    if (selection == 1) printf("        ^\n");
    else printf("^\n");
}
void print_zgon(int selection){ // menu posmiertne
    cease();
    printf(" ____             _   _     \n");
    printf("|  _ \\  ___  __ _| |_| |__  \n");
    printf("| | | |/ _ |/ _` | __| '_ \\ \n");
    printf("| |_| |  __/ (_| | |_| | | |\n");
    printf("|____/ |___||__,_||__|_| |_|\n");
    printf("\n");
    printf("Uzyskano score: %d \n", game.score);
    printf("|Reset||Menu || End |\n");
    for(int i = 0; i < selection;i++) printf("       ");
    printf("^\n"); 
}