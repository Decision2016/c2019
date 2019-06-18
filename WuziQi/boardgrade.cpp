#include "boardgrade.h"

BoardGrade::BoardGrade()
{

}

void BoardGrade::Set(int x,int y,int grade){
    Grade[x][y] = grade;
}

int BoardGrade::Get(int x,int y){
    return Grade[x][y];
}
