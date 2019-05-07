#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include "maze.h"

using namespace std;

#define W 160
#define H 40

int dirx[4] = {-1,0,1,0};
int diry[4] = {0,-1,0,1};
string s[7] = {"Welcome to Decision's maze!","You can use WASD to move.","Press 1 to chose Simple Mode(Smallest map).","Press 2 to chose Ordinary Mode(Small map).",
               "Press 3 to chose Middle Mode(Large map).","Press 4 to chose Hard Mode(The largest map).",
               "Press 5 to exit."};
string con_information[3] = {"CONGRATULATIONS!","You are out of the maze!","Press 1 to menu."};


struct game
{
    int start_w,start_h,pos; 
    
    game();
    void preInit();
    void Gotoxy(int posx,int posy);
    void PlayerMove(int posx,int posy,int dir);
    void PrintInformation(string* ss,int num);
    int GetDir();
    void Game(int w,int h);
    void menu();
};

#endif