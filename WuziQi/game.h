#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <QTime>
#include <QDebug>
#define SizeOfBroad 15

struct Game
{
    Game();
    int ChessBroad[SizeOfBroad][SizeOfBroad];
    int RobotMaxPosX,RobotMaxPosY;
    int PeopleMaxPosX,PeopleMaxPosY;
    int RobotMaxGrade,PeopleMaxGrade;
    int RobotPutPosX,RobotPutPosY;   //机器下子位置
    bool NowPlayer;
    void GameWithPeople();
    void GameInit();
    void GetGradeOnBroad();
    void RobotPutChess();
    void GradeInit();
    void SetNowPlayer(bool x);
    void RobotGetPos();
    bool GetNowPlayer();
    bool PutChessOn(int posx,int posy);
    bool CanPutChess(int posx,int posy);
    bool CheckWin(int posx,int posy);
    int GetPosGrade(int posx,int posy,int now);
    int GetChess(int x,int y,int dir,int len);
    int GetChessOnBroad(int posx,int posy);
    //int GetPosType(int posx,int posy,int dir,int flag)
};

#endif // GAME_H
