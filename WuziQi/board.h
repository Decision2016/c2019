#ifndef Board_H
#define Board_H

#include<cstring>
#include<QtDebug>
#include<string>
#include<QString>
#include<iostream>

#define SizeOfBoard 15
#define DirSum 4
#define Win 1
#define Huo4 1
#define Chong4 5
#define Huo3 4
#define Mian3 20
#define Huo2 12
#define Mian2 10
#define One 1
#define None 1


struct Board{
    int board[SizeOfBoard][SizeOfBoard];
    void Clear();
    void Put(int x,int y,int type);
    int Get(int x,int y);
    std::string GetStatu(int x,int y,int dir);
    int GradeCaculate(int x,int y);
    int GradeSumCaculate();
    int GradeGet(std::string Statu);
    bool CheckPos(int x,int y);
    bool StatuCheck(int x,int y);
    Board();
};

#endif // Board_H
