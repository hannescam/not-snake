#include <cstdlib>
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include "draw.h"
#include "intToStr.h"

int x;
int y;
int xold;
int yold;
int x_food;
int y_food;
int x_enemy;
int y_enemy;
int x_enemy_old;
int y_enemy_old;
int xy_des;
bool x_enemywant;
bool y_enemywant;
int input;
int score;
int dead;
int dcnt;
int key;

void enemy(int playerx, int playery){
    x_enemywant=false;
    y_enemywant=false;
    if (x_enemy < playerx | x_enemy > playerx) x_enemywant=true;
    if (y_enemy < playery | y_enemy > playery) y_enemywant=true;
    if (x_enemywant && y_enemywant){
        if (xy_des == 1){
            xy_des=0;
            if (y_enemy < playery) y_enemy++;
            if (y_enemy > playery) y_enemy--;
        } else if (xy_des == 0){
            xy_des=1;
            if (x_enemy < playerx) x_enemy++;
            if (x_enemy > playerx) x_enemy--;
        }
    } else if (x_enemywant | y_enemywant){
        if (x_enemy < playerx) x_enemy++;
        if (x_enemy > playerx) x_enemy--;
        if (y_enemy < playery) y_enemy++;
        if (y_enemy > playery) y_enemy--;
    }
    draw_dot(x_enemy, y_enemy, "K");
    erase_dot(x_enemy_old, y_enemy_old);
    x_enemy_old=x_enemy;
    y_enemy_old=y_enemy;    
}

int game(std::string input){
    move(0, 0);
    if(input == "UP") y--;
    if(input == "DOWN") y++;
    if(input == "LEFT") x--;
    if(input == "RIGHT") x++;
    if(x == 32) {
        if(rand() % 10 + 1 == 5) {
            dead=1;
        }else{
            x=0;
        }
    }
    if(y == 16) {
        if(rand() % 10 + 1 == 3) {
            dead=1;
        }else{
            y=0;
        }
    }
    if(x == -1) {
        if(rand() % 10 + 1 == 1) {
            dead=1;
        }else{
            x=31;
        }
    }
    if(y == -1) {
        if(rand() % 10 + 1 == 9) {
            dead=1;
        }else{
            y=15;
        }
    }
    
    if (dead == 1){
        printw("score: ");
        printw(intToStr(score));
        printw("\n");
        if (dcnt == 0) printw(draw_dot(x_enemy, y_enemy, "K"));
        printw("\n du bist tot zum beenden STRG+C Druecken");
        if(score > 10) printw(" Du warst gut (:");
        dcnt=1;
        return 0;
    }
    if(x == x_food && y == y_food){
        score++;
        x_food = rand() % 31 + 0;
        y_food = rand() % 15 + 0;
        draw_dot(x_food, y_food, "X");
    }
    if(x_enemy == x_food && y_enemy == y_food){
        x_food = rand() % 31 + 0;
        y_food = rand() % 15 + 0;
        draw_dot(x_food, y_food, "X");
    }
    printw("score: ");
    printw(intToStr(score));
    printw("\n");
    erase_dot(xold, yold);
    printw(draw_dot(x, y, "#"));
    xold=x;
    yold=y;
    enemy(x, y);
    if (x_enemy == x && y_enemy == y) dead=1;
    return 0;
}

int main(){
    initscr();
    crmode();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    move(0, 0);
    refresh();
    srand(time(NULL));
    x_food = rand() % 31 + 0;
    y_food = rand() % 15 + 0;
    x = rand() % 31 + 0;
    y = rand() % 15 + 0;
    x_enemy = rand() % 31 + 0;
    y_enemy = rand() % 15 + 0;
    x_enemy_old=x_enemy;
    y_enemy_old=y_enemy;
    draw_dot(x_enemy, y_enemy, "K");
    draw_dot(x_food, y_food, "X");
    printw("score: 0\n");
    printw(draw_dot(x, y, "#"));
    xold=x;
    yold=y;
    while(true) {
        //std::cin >> input;
        refresh();
        key = getch();
        while(key != ERR) {
            usleep(10000);
            refresh();
            if (key == KEY_RIGHT) game("RIGHT");
            if (key == KEY_LEFT) game("LEFT");
            if (key == KEY_UP) game("UP");
            if (key == KEY_DOWN) game("DOWN");
            key = getch();
        }
        //usleep(100);
        //game(input);
    }
}
