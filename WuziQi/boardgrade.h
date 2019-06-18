#ifndef BoardGRADE_H
#define BoardGRADE_H

#define SizeOfBoard 15

#include "board.h"

struct BoardGrade{
    BoardGrade();
    int Grade[SizeOfBoard][SizeOfBoard];
    Board nowBoard;
    void Set(int x,int y,int grade);
    int Get(int x,int y);
};

#endif // BoardGRADE_H
