void print_menu(int selection){
    system("clear"); // Nie jestem pewien jak wyczyszczacie screen w reszcie projektu,
    printf("  ____                     ____  _                  _          \n");
    printf(" / ___|_ __ __ _    ___   / ___|| | _____   ___ ___| | ___   _  \n ");
    printf("| |  _| '__/ _` |  / _ |  |___ || |/ / _ | / __|_  / |/ / | |  |\n");
    printf("| |_| | | | (_| | | (_) |  ___) |   < (_) | (__ / /|   <| |_|  |\n");
    printf(" |____|_|  |__,_|  |___/  |____/|_||_|___/ |___/___|_||_||__,_|\n");
    printf("\n");
    printf("| Start || Save  || Load  || Scores|| Exit  || Inst  |\n");
    for( int i = 0; i < selection; i++){
        printf("         ");
    }
    printf("^\n");
}