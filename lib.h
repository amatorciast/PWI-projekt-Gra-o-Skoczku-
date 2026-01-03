#include <stdbool.h>

#define and &&
#define or ||
#define true 1
#define false 0


typedef struct{
    char map[8][8];//plansza gry
    int x, y;//miejsce gracza w map
    int is_started;//flaga dla sprawdzania czy gra sie zaczola
    //0: nie zaczola sie
    //1: zaczola sie
    //2: pause
}Game_info;

extern Game_info game;




//------------------------------------Jakub Sroka---------------------------------------
void set_terminal();//ustawienie terminalu
int get_input();//zwraca to co wpisał gracz
//0-8: osiem standardowych ruchów skoczka + zostanie w miejscu
//9: pauza
//======================================================================================



//--------------------------------------------------------------------------------------
void player_move(int);//logika ruszania gracza
//======================================================================================



//----------------------------------Gabriel Mis-----------------------------------------
typedef struct {
    bool alive;
    int curr_x;
    int curr_y;
    int next_x;
    int next_y;
    int figure; // 0 pionek
    // 1 wieza
    // 2 skoczek
    // 3 biskup
    // 4 hetman
}enemy;
extern enemy enemies[64];
void enemy_init();//zapełnienie powyższej tablicy
void enemy_spawn();//dodawanie przeciwników
void enemy_death(int indx);//usuwanie przeciwnika
void enemy_move();//logika ruszania przeczewnikow
//======================================================================================



//----------------------------------Alan Drab-------------------------------------------
void set_output();//wypisywanie
//prośba - typ enemy ma dwa koordynaty - obecne i następne
//zrób proszę, że te następne się podświetlają jakoś
//jasne :like:
//======================================================================================



//----------------------------Kacper Niebrzydowski--------------------------------------
int pause();//podaje dostep do przejscia do:
//0: zwrot do gry
//1: menu

int menu();//podaje dostep dla uzytkowmika do funkcyj:
//0: rozpoczac nowa gre
//1: save
//2: load
//3: wypisuje score
//4: wyjscie

void save(Game_info);//zapisuje gre
void save_error();//obsluga bledu gdy chcemy zapisc gre ktorej nie ma
Game_info load();//zwraca informacje o gre
//======================================================================================



//--------------------------------------------------------------------------------------
void print_score();//zwraca liste int ze scorami z ostatnich podejsc
void add_score(int);//dodaje nowy score
//======================================================================================




void menu_check();
void end_game();//jezeli bedziecie robili malloc/calloc to ta funkcja powinna zawierac free
void start_game();//jezeli potrzebujecie cos zaimplikowac na poczatku - tu jest miejsce dla tego