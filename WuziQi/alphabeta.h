#ifndef ALAPHBETA_H
#define ALAPHBETA_H

#include "point.h"
#include "board.h"
#include "boardgrade.h"
#include "node.h"
#include <vector>
#include <QtDebug>

#define INF 1000000007
#define MAXDEP 2
#define People 1
#define AI 2

struct AlphaBeta{
    int x,y,cnt;
    Point Res,Temp;
    Board Nowboard;
    BoardGrade Grade;
    Point GetNextPoint();
    int AlphaBetaEngin(const Node& node,int depth,int alaph,int beta);
    Point GetBestStep(std::vector<Node> Statu);
    void Output();
    AlphaBeta();
};

#endif // ALAPHBETA_H
