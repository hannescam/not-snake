#include <iostream>
#include <string>

int cnt;
int place;
std::string array = "__________________________________\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|                                |\n|________________________________|\n";

char* draw_dot(int posx, int posy, std::string symbol){
    place=34;
    while(posy > cnt){
        place=place+34;
        cnt++;
    }
    place=place+cnt+2;
    place=place+posx;
    cnt = 0;
    array.replace(place, 1, symbol);
    char* c  = array.data();
    return c;
}

char* erase_dot(int posx, int posy){
    place=34;
    while(posy > cnt){
        place=place+34;
        cnt++;
    }
    place=place+cnt+2;
    place=place+posx;
    cnt = 0;
    array.replace(place, 1, " ");
    char* c  = array.data();
    return c;
}
