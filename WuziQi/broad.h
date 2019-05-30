#ifndef BROAD_H
#define BROAD_H

#include<cstring>
#include<QtDebug>

#define SizeOfBroad 15
#define DirSum 8
#define Win 1
#define Huo4 1
#define Chong4 5
#define Huo3 4
#define Mian3 20
#define Huo2 12
#define Mian2 10
#define One 1
#define None 1


struct Broad{
    int broad[SizeOfBroad][SizeOfBroad];
    void Clear();
    void Put(int x,int y,int type);
    int Get(int x,int y);
    int GetStatu(int x,int y,int dir);
    int GradeCaculate(int x,int y);
    int GradeSumCaculate();
    int GradeGet(int Statu);
    bool CheckPos(int x,int y);
    bool StatuCheck(int x,int y);
    Broad();
};

#endif // BROAD_H
