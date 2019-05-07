//
// Created by Decision on 2019/4/24.
//

#include "game.h"
#include "maze.h"
#include <windows.h>
#include <conio.h>
#include <iostream>

#define W 160
#define H 40
int dirx[4] = {-1,0,1,0};
int diry[4] = {0,-1,0,1};
std::string con_information[3] = {"CONGRATULATIONS!","You are out of the maze!","Press 1 to menu."};
std::string s[7] = {"Welcome to Decision's maze!","You can use WASD to move.","Press 1 to chose Simple Mode(Smallest map).","Press 2 to chose Ordinary Mode(Small map).",
               "Press 3 to chose Middle Mode(Large map).","Press 4 to chose Hard Mode(The largest map).",
               "Press 5 to exit."};

game::game(){

}

void game::preInit(){
    system("mode con cols=160 lines=40");
}

void game::Gotoxy(int posx,int posy){
    COORD CUR;
    HANDLE hout;
    CUR.X = posy;
    CUR.Y = posx;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,CUR);
}

void game::PlayerMove(int posx,int posy,int dir){
    Gotoxy(posx,posy);
    std::cout<<" ";
    Gotoxy(posx + dirx[dir],posy + diry[dir]);
    std::cout<<"\033[1m\033[31m"<<"@";
}

void game::PrintInformation(std::string* ss,int num){
    system("cls");
    int maxx = 0,len;
    for(int i = 0;i<num;i++){
        len = ss[i].length();
        maxx = std::max(len,maxx);
    }
    start_w = (W - maxx) / 2;
    start_h = (H - num*2) / 2;
    for(int i = 1;i<=H;i++){
        if(i == start_h){
            for(int k = 0;k<num;k++){
                int tmp = start_w + maxx+1;
                for(int l = 1;l<=W;l++){
                    if(l==start_w - 2||l==tmp + 2) std::cout<<"\033[1m\033[31m"<<"#";
                    else if(l==start_w+1) std::cout<<"\033[1m\033[31m"<<ss[k],l+=ss[k].length() - 1;
                    else std::cout<<" ";
                }
                std::cout<<std::endl;
                for(int l = 1;l<=W;l++){
                    if(l==start_w - 2||l==tmp + 2) std::cout<<"\033[1m\033[31m"<<"#";
                    else std::cout<<" ";
                }
                std::cout<<std::endl;
            }
            i+=2*num;
        }
        else if(i == start_h + 2*num + 1 || i == start_h-1){
            for(int j = 1;j<=W;j++){
                if(j>=start_w - 2&&j<=start_w + maxx + 3) std::cout<<"\033[1m\033[31m"<<"#";
                else std::cout<<" ";
            }
            std::cout<<std::endl;
        }
        else std::cout<<std::endl;

    }
}

int game::GetDir(){
    char c = getch();
    if(c == 'w') return 0;
    else if(c == 'a') return 1;
    else if(c == 's') return 2;
    else if(c == 'd') return 3;
}

void game::Game(int w,int h){
    system("cls");
    maze Maze;
    std::vector<point> p = Maze.refresh(w,h);
    w = 2*w + 2,h = 2*h+2;
    point player = point(p[0].x,p[0].y);
    Maze.Show(player.x,player.y,w,h);
    while(player.x != p[1].x || player.y != p[1].y){
        int dir = GetDir();
        int nowx = player.x + dirx[dir],nowy = player.y + diry[dir];
        if(Maze.Get(nowx,nowy) == 0 && nowx>=0 && nowy>=0){
            PlayerMove(player.x,player.y,dir);
            Gotoxy(h+1,0);
            player.x = nowx;
            player.y = nowy;
        }
        Sleep(125);
    }

    PrintInformation(con_information,3);
    char t;
    t = getch();
    Sleep(125);
    if(t == '1'){
        PrintInformation(s,7);
        return ;
    }
}

void game::menu(){
    int t;
    while(1){
        t = getch();
        switch(t){
            case(49):
                Game(10,5);
                break;
            case(50):
                Game(20,10);
                break;
            case(51):
                Game(30,15);
                break;
            case(52):
                Game(50,15);
                break;
            case(53):
                return ;
        }
    }
}

