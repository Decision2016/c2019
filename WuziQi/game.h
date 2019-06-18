#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <QTime>
#include "point.h"
#include "board.h"
#include "alphabeta.h"
#include "mcts.h"

#define SizeOfBoard 15
#define AI 2
#define People 1

struct Game{
    Board ChessBoard;
    int PeopleMaxPosX,PeoplerMaxPosY;
    bool NowPlayer;
    Game();
    void GameWithPeople();
    void GameInit();
    void SetNowPlayer(bool x);
    Point RobotPutChess(int Type,int x,int y);
    bool PutChessOn(int posx,int posy);
    bool canPutChess(int posx,int posy);
    bool CheckWin(int posx,int posy);
    bool GetNowPlayer();
    int GetChessOnBoard(int posx,int posy);
    //int GetPosType(int posx,int posy,int dir,int flag)
};

#endif // GAME_H
