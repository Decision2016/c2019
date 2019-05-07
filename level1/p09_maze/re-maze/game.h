//
// Created by Decision on 2019/4/24.
//

#ifndef GAME_H_

#define GAME_H_
#include<string>

struct game
{
    int start_w,start_h,pos;

    game();
    void preInit();
    void Gotoxy(int posx,int posy);
    void PlayerMove(int posx,int posy,int dir);
    void PrintInformation(std::string* ss,int num);
    int GetDir();
    void Game(int w,int h);
    void menu();
};

#endif