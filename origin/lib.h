#include <stdbool.h>

//deklaracja struktury enemy
typedef struct {
    bool alive;
    int curr_x;
    int curr_y;
    int next_x;
    int next_y;
    int figure;
    // 0 pionek
    // 1 wieza
    // 2 skoczek
    // 3 biskup
    // 4 hetman
}enemy;

//deklaracja struktury Game_info
typedef struct{
    enemy enemies[64]; //tablica z danymi o przeciwnikach
    int x, y; //pozycja gracza na planszy
    int is_started; //flaga mówiąca czy gra sie zaczęła czy nie
    //0: nie zaczęła się
    //1: zaczęła się
    int score; //wynik gracza
    int since_last_enemy; //licznik rund od ostatniego pojawienia się nowego przeciwnika
    int difficulty; // poziom trudności rosnący wraz z liczbą przeżytych rund
    int score_list[10];
}Game_info;

extern Game_info game;


//------------------------------------Jakub Sroka---------------------------------------
int get_input();//zwraca to co wpisał gracz
//0-8: osiem standardowych ruchów skoczka + zostanie w miejscu
//9: pauza
void input_error();//obsługuje sytuację, w której gracz próbuje wyjść poza planszę
void show_instructions();
//======================================================================================



//------------------------------------Jakub Sroka---------------------------------------
void save(Game_info*);//zapisuję gre do pliku tekstowego
void save_error(int);//obsługa bledów podczas zapisywania gry
int load();//wczytuje informacje o grze z pliku teksowego
void load_error(int);//obsluga bledów podczas wczytywania gry

void check_for_death_realization();//poprawnie wykonuje check_for_death, żeby w main było ładnie
//======================================================================================



//----------------------------------Gabriel Mis-----------------------------------------
bool player_move(int);//logika ruszania gracza, w player.c

//poniższe w menu_placeholder.c
void print_score_quick();//szybkie wypisanie score w trakcie działania gry;
int zgon();//zwraca wybór gracza z ekranu śmierci
//0: zagraj ponownie
//1: menu
void game_reset();//resetuje stan game
//======================================================================================



//----------------------------------Gabriel Mis-----------------------------------------
//poniższe w enemy_logic.c
int check_for_death();//jeżeli gracz nie umarł to zwraca 0, a w przeciwnym przypadku wynik zgon()
void enemy_init();//zapełnienie powyższej tablicy
void enemy_deside_if_to_bother_living(int);//decydowanie czy zespawnić przeciwnika
void enemy_spawn();//dodawanie przeciwników
void enemy_death(int indx);//usuwanie przeciwnika
void enemy_move();//logika ruszania przeczewnikow
//======================================================================================



//----------------------------------Alan Drab-------------------------------------------
void set_output();//wypisuje planszę do gry wraz z zawartością
void windows_dzialaj();
void wsadzanie_przeciwnikow_na_plansze(char[8][8]);
void wsadzanie_ruchu_przeciwnikow(char[8][8]);
void obliczanie_mozliwych_ruchow(char[8][8]);
//======================================================================================



//----------------------------Kacper Niebrzydowski--------------------------------------
void pause();//zatrzymuje gre i można
//0: wznowić grę
//1: przejść do menu

int menu();//podaje dostep dla uzytkowmika do funkcyj:
//0: rozpoczac nowa gre
//1: save
//2: load
//3: wypisuje score
//4: wyjscie
//======================================================================================



//--------------------------------------------------------------------------------------
void print_score();//zwraca liste int ze scorami z ostatnich podejsc
void add_score(int, int *);//dodaje nowy score
void enemy_death_score(int); //dodaje punkty za pokonanie przeciwnika
void score_list_init(int score_list[10]); //czysci tablice
//======================================================================================


void menu_check();
void end_game();
void start_game();