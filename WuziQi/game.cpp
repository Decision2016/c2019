#include "game.h"

Game::Game(){

}

bool Game::canPutChess(int posx,int posy){
    //if(NowPlayer != 0) return false;
    if(posx == 0 || posx == 14 || posy == 0 ||posy == 14) return false;
    if(ChessBroad.Get(posx,posy) == 1 || ChessBroad.Get(posx,posy) == 2) return false;
    return true;
}

bool Game::PutChessOn(int posx,int posy){
    if(!canPutChess(posx,posy)) return false;
    if(!NowPlayer) ChessBroad.Put(posx,posy,1);
    else ChessBroad.Put(posx,posy,2);
    NowPlayer = !NowPlayer;
    return true;
}

int Game::GetChessOnBroad(int posx,int posy){
    return ChessBroad.Get(posx,posy);
}

bool Game::CheckWin(int posx,int posy){
    bool res = ChessBroad.StatuCheck(posx,posy);
    return res;
}



void Game::GameInit(){
    NowPlayer = 0;
    ChessBroad.Clear();
}

bool Game::GetNowPlayer(){
    return NowPlayer;
}

void Game::SetNowPlayer(bool x){
    NowPlayer = x;
}

//根据选项调用不同的AI接口
Point Game::RobotPutChess(int Type,int x,int y){
    AlphaBeta a;
    a.Nowbroad = ChessBroad;
    a.x = x;
    a.y = y;
    Point Nxt = a.GetNextPoint();
    ChessBroad.Put(Nxt.x,Nxt.y,AI);
    return Nxt;
}
