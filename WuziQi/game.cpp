#include "game.h"

Game::Game()
{

}

bool Game::canPutChess(int posx,int posy){
    //if(NowPlayer != 0) return false;
    if(posx == 0 || posx == 14 || posy == 0 ||posy == 14) return false;
    if(ChessBroad[posx][posy] == 1 || ChessBroad[posx][posy] == 2) return false;
    return true;
}

bool Game::PutChessOn(int posx,int posy){
    if(!canPutChess(posx,posy)) return false;
    if(!NowPlayer) ChessBroad[posx][posy] = 1;
    else ChessBroad[posx][posy] = 2;
    NowPlayer = !NowPlayer;
    return true;
}

int Game::GetChessOnBroad(int posx,int posy){
    return ChessBroad[posx][posy];
}

bool Game::CheckWin(int posx,int posy){
    int CheckX[8] = {0,1,1,1,0,-1,-1,-1};
    int checkY[8] = {-1,-1,0,1,1,1,0,-1};
    int nowchess;
    if(NowPlayer) nowchess = 1;
    else nowchess = 2;
    for(int i = 0;i<8;i++){
        int cnt = 1;
        int tposx = posx;
        int tposy = posy;
        while(ChessBroad[tposx][tposy] != 0){
            if(tposx == 0 || tposx == 14 || tposy == 0|| tposy == 14) break;
            if(cnt == 5) break;
            tposx += CheckX[i];
            tposy += checkY[i];
            if(ChessBroad[tposx][tposy] == nowchess) cnt++;
            else break;
        }
        if(cnt == 5) return true;
        else continue;
    }
    return false;
}



void Game::GameInit(){
    NowPlayer = 0;
    memset(ChessBroad,0,sizeof(ChessBroad));
}

bool Game::GetNowPlayer(){
    return NowPlayer;
}

void Game::RobotPutChess(){
    int posx = qrand() % 13 + 1;
    int posy = qrand() % 13 + 1;
    while(ChessBroad[posx][posy] != 0){
        posx = qrand() % 13 + 1;
        posy = qrand() % 13 + 1;
    }
    ChessBroad[posx][posy] = 2;
}

void Game::GradeInit(){
    RobotMaxPosX = RobotMaxPosY = 0;
    PeopleMaxPosX = PeoplerMaxPosY = 0;
    PeopleMaxGrade = RobotMaxGrade = 0;
}

void Game::SetNowPlayer(bool x){
    NowPlayer = x;
}
