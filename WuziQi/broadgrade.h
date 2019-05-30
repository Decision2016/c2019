#ifndef BROADGRADE_H
#define BROADGRADE_H

#define SizeOfBroad 15

#include "broad.h"

struct BroadGrade{
    BroadGrade();
    int Grade[SizeOfBroad][SizeOfBroad];
    Broad nowBroad;
    void Set(int x,int y,int grade);
    int Get(int x,int y);
};

#endif // BROADGRADE_H
