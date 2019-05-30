#include "broadgrade.h"

BroadGrade::BroadGrade()
{

}

void BroadGrade::Set(int x,int y,int grade){
    Grade[x][y] = grade;
}

int BroadGrade::Get(int x,int y){
    return Grade[x][y];
}
