#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <QTime>

#define SizeOfBroad 15

struct Game
{
    Game();
    int ChessBroad[SizeOfBroad][SizeOfBroad];
    int RobotMaxPosX,RobotMaxPosY;
    int PeopleMaxPosX,PeoplerMaxPosY;
    int RobotMaxGrade,PeopleMaxGrade;
    bool NowPlayer;
    void GameWithPeople();
    void GameInit();
    void GetPosGrade(int posx,int posy);
    void GetGradeOnBroad();
    void RobotPutChess();
    void GradeInit();
    void SetNowPlayer(bool x);
    bool PutChessOn(int posx,int posy);
    bool canPutChess(int posx,int posy);
    bool CheckWin(int posx,int posy);
    bool GetNowPlayer();
    int GetChessOnBroad(int posx,int posy);
    //int GetPosType(int posx,int posy,int dir,int flag)
};

#endif // GAME_H
