#include "alphabeta.h"

AlphaBeta::AlphaBeta(){

}

Point AlphaBeta::GetNextPoint(){
    Node root = Node(2,0,0);
    std::vector<Node> Status;
    memset(Grade.Grade,-1,sizeof(Grade.Grade));
    int Score = AlphaBetaEngin(root,MAXDEP,-INF,INF);
    for(int i = 1;i < 14;i++){
        for(int j = 1;j < 14;j++){
            if(Grade.Get(i,j) == Score) Status.push_back(Node(AI,i,j));
        }
    }
    Res = GetBestStep(Status);
    return Res;
}

int AlphaBeta::AlphaBetaEngin(Node node,int depth,int alpha,int beta){
    if(Nowbroad.StatuCheck(node.x,node.y)){
        if(node.NowPlayer == AI) {
            return INF;
        }
        else {
            return -INF;
        }
    }
    if(depth == 0) {
        int res = Nowbroad.GradeSumCaculate();
        return res;
    }
    if(node.NowPlayer == AI) {
        for(int i = 1;i < 14;i++) {
            for(int j = 1;j < 14;j++) {
                if(Nowbroad.CheckPos(i,j)) {
                    Nowbroad.Put(i,j,AI);
                    Node child = Node(People,i,j);
                    int value = AlphaBetaEngin(child,depth - 1,alpha,beta);
                    Nowbroad.Put(i,j,0);
                    if(value > alpha) {
                        alpha = value;
                        Grade.Set(i,j,alpha);
                    }
                    if(alpha >= beta) {
                        break;
                    }
                }
            }
            if(alpha >= beta) {
                break;
            }
        }
        return alpha;
    }
    else {
        for(int i = 1;i < 14;i++) {
            for(int j = 1;j < 14;j++) {
                if(Nowbroad.CheckPos(i,j)) {
                    Nowbroad.Put(i,j,People);
                    Node child = Node(AI,i,j);
                    int value = AlphaBetaEngin(child,depth - 1,alpha,beta);
                    Nowbroad.Put(i,j,0);
                    if(value < beta) {
                        beta = value;
                        Grade.Set(i,j,beta);
                    }
                    if(alpha >= beta) {
                        break;
                    }
                }
            }
            if(alpha >= beta) {
                break;
            }
        }
        return beta;
    }
}

Point AlphaBeta::GetBestStep(std::vector<Node> Statu){
    unsigned int len = Statu.size();
    Node node = Statu[0];
    Nowbroad.Put(node.x,node.y,node.NowPlayer);
    int value = Nowbroad.GradeSumCaculate();
    Nowbroad.Put(node.x,node.y,0);
    unsigned int res = 0;
    for(unsigned int i = 0;i < len;i++) {
        Node n = Statu[i];
        Nowbroad.Put(n.x,n.y,n.NowPlayer);
        int value1 = Nowbroad.GradeSumCaculate();
        if(value1 > value){
            res = i;
        }
        Nowbroad.Put(n.x,n.y,0);
    }
    return Point(Statu[res].x,Statu[res].y);
}
