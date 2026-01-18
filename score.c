#include <stdio.h>
#include "lib.h"

#define PIONEK 1
#define SKOCZEK 2
#define BISKUP 3
#define WIEZA 4
#define HETMAN 5

void enemy_death_score(int index)
{
    int pom=game.enemies[index].figure;

    switch (pom) {
        case 0:
            game.score+=PIONEK;
            break;
        case 1:
            game.score+=WIEZA;
            break;
        case 2:
            game.score+=SKOCZEK;
            break;
        case 3:
            game.score+=BISKUP;
            break;
        case 4:
            game.score+=HETMAN;
            break;
    }
}

void score_list_init(int score_list[10])
{
    for(int i=0; i<10; i++) {
        score_list[i]=-1;
    }
}

void add_score(int new_score, int *score_list)//dodaje nowy score
{
    if(score_list[9]==-1) { //jesli istnieje puste miejsce w tablicy ostatnich wynikow
        int i=9;
        while(score_list[i-1]==-1) {
            i--;
        }
        
        score_list[i]=new_score;
    }
    else {
        for(int i=0; i<9; i++) {
            score_list[i]=score_list[i+1];
        }
        score_list[9]=new_score;
    }
}

void print_score()
{
    printf("\e[1;1H\e[2J\e[3J");
    printf("Ostanie wyniki:\n");
    for(int i=0; i<10; i++) {
        if(game.score_list[i]==-1) {
            printf("brak zapisanego wyniku\n");
        }
        else {
            printf("%d\n", game.score_list[i]);
        }
    }
    printf("Wprowadz dowolny znak aby kontynuować\n");
    char leave;
    while(scanf(" %c", &leave)) {
        return;
    }
}