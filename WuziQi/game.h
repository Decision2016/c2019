#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <QTime>
#include "point.h"
#include "broad.h"
#include "alphabeta.h"
#include "mcts.h"

#define SizeOfBroad 15
#define AI 2
#define People 1

struct Game{
    Broad ChessBroad;
    int PeopleMaxPosX,PeoplerMaxPosY;
    bool NowPlayer;
    Game();
    void GameWithPeople();
    void GameInit();
    void SetNowPlayer(bool x);
    void RobotPutChess(int Type);
    bool PutChessOn(int posx,int posy);
    bool canPutChess(int posx,int posy);
    bool CheckWin(int posx,int posy);
    bool GetNowPlayer();
    int GetChessOnBroad(int posx,int posy);
    //int GetPosType(int posx,int posy,int dir,int flag)
};

#endif // GAME_H
