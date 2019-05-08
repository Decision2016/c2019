#include "game.h"

Game::Game()
{

}

bool Game::CanPutChess(int posx,int posy){
    //if(NowPlayer != 0) return false;
    if(posx == 0 || posx == 14 || posy == 0 ||posy == 14) return false;
    if(ChessBroad[posx][posy] == 1 || ChessBroad[posx][posy] == 2) return false;
    return true;
}

bool Game::PutChessOn(int posx,int posy){
    if(!CanPutChess(posx,posy)) return false;
    if(!NowPlayer) ChessBroad[posx][posy] = 1;
    else ChessBroad[posx][posy] = 2;
    NowPlayer = !NowPlayer;
    return true;
}

int Game::GetChessOnBroad(int posx,int posy){
    if(posx < 1 || posy >=14) return -1;
    return ChessBroad[posx][posy];
}

bool Game::CheckWin(int posx,int posy){
    int CheckX[8] = {0,1,1,1,0,-1,-1,-1};
    int checkY[8] = {-1,-1,0,1,1,1,0,-1};
    int nowchess;
    if(NowPlayer) nowchess = 2;
    else nowchess = 1;
    for(int i = 0;i<8;i++){
        int cnt = 1;
        int tposx = posx;
        int tposy = posy;
        while(ChessBroad[tposx][tposy] != 0){
            if(tposx == 0 || tposx == 14 || tposy == 0|| tposy == 14) break;
            if(cnt == 5) break;
            tposx += CheckX[i];
            tposy += checkY[i];
            if(ChessBroad[tposx][tposy] == nowchess) cnt++;
            else break;
        }
        if(cnt == 5) return true;
        else continue;
    }
    return false;
}

void Game::GameInit(){
    NowPlayer = 0;
    memset(ChessBroad,0,sizeof(ChessBroad));
}

bool Game::GetNowPlayer(){
    return NowPlayer;
}

void Game::RobotPutChess(){
    GradeInit();
    RobotGetPos();
    ChessBroad[RobotPutPosX][RobotPutPosY] = 2;
}

void Game::RobotGetPos(){
    int PeopleGrade,RobotGrade;
    for(int i = 1;i < 14;i++){
        for(int j = 1;j < 14;j++){
            if(ChessBroad[i][j] != 0) continue;
            PeopleGrade = GetPosGrade(i,j,0);
            RobotGrade = GetPosGrade(i,j,1);
            if(PeopleGrade > PeopleMaxGrade){
                PeopleMaxPosX = i;
                PeopleMaxPosY = j;
                PeopleMaxGrade = PeopleGrade;
            }
            if(RobotGrade > RobotMaxGrade){
                RobotMaxPosX = i;
                RobotMaxPosY = j;
                RobotMaxGrade = RobotGrade;
            }
        }
    }
    if(RobotMaxGrade > PeopleMaxGrade){
        RobotPutPosX = RobotMaxPosX;
        RobotPutPosY = RobotMaxPosY;
    }
    else{
        RobotPutPosX = PeopleMaxPosX;
        RobotPutPosY = PeopleMaxPosY;
    }
}

void Game::GradeInit(){
    RobotMaxPosX = RobotMaxPosY = 0;
    PeopleMaxPosX = PeopleMaxPosY = 0;
    PeopleMaxGrade = RobotMaxGrade = 0;
}

void Game::SetNowPlayer(bool x){
    NowPlayer = x;
}

int Game::GetChess(int x,int y,int dir,int len){
    int dirx[8] = {0,1,1,1,0,-1,-1,-1};
    int diry[8] = {-1,-1,0,1,1,1,0,-1};
    return GetChessOnBroad(x + len * dirx[dir],y + len * diry[dir]);
}

int Game::GetPosGrade(int posx,int posy,int now){
    int NowPlayerChess = now + 1;
    int OtherPlayerChess = !now + 1;
    int GradeRes = 0;
    for(int i = 0;i < 8;i++){
        //对活4的判断
        if(GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == NowPlayerChess && GetChess(posx,posy,i,5) == 0){
            GradeRes += 1000000;
        }

        //对死4的判断
        if(GetChess(posx,posy,i,-1) == NowPlayerChess && GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == NowPlayerChess){
            GradeRes += 400000;
        }

        if(GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == NowPlayerChess  && (GetChess(posx,posy,i,5) == OtherPlayerChess || GetChess(posx,posy,i,5) == OtherPlayerChess)){
            GradeRes += 400000;
        }
        //对活3的判断
        if(GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == 0){
            GradeRes += 200000;
        }

        if(GetChess(posx,posy,i,-2) == 0 && GetChess(posx,posy,i,-1) == NowPlayerChess && GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == 0){
            GradeRes += 200000;
        }

        //对死3的判断
        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == NowPlayerChess && (GetChess(posx,posy,i,5) == OtherPlayerChess || GetChess(posx,posy,i,5) == -1)){
            GradeRes += 50000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == NowPlayerChess && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 50000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 50000;
        }

        if(GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 50000;
        }

        if(GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == 0 && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 50000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == NowPlayerChess && GetChess(posx,posy,i,5) == 0 && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 50000;
        }

        //对活2的判断
        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == 0 && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == NowPlayerChess && GetChess(posx,posy,i,5) == 0 && GetChess(posx,posy,i,6) == 0){
            GradeRes += 5000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == NowPlayerChess && GetChess(posx,posy,i,5) == 0){
            GradeRes += 5000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess && GetChess(posx,posy,i,6) == 0){
            GradeRes += 5000;
        }

        //对死2的判断
        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == 0 && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == NowPlayerChess && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 2000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == 0 && GetChess(posx,posy,i,3) == NowPlayerChess && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 2000;
        }

        if(GetChess(posx,posy,i,1) == 0 && GetChess(posx,posy,i,2) == NowPlayerChess && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess && (GetChess(posx,posy,i,6) == OtherPlayerChess || GetChess(posx,posy,i,6) == -1)){
            GradeRes += 2000;
        }

        if(GetChess(posx,posy,i,1) == NowPlayerChess && GetChess(posx,posy,i,2) == 0 && GetChess(posx,posy,i,3) == 0 && GetChess(posx,posy,i,4) == 0 && GetChess(posx,posy,i,5) == NowPlayerChess ){
            GradeRes += 2000;
        }

        //只有1个棋子的判断
        if(GetChess(posx,posy,i,1) == NowPlayerChess) GradeRes += 100;
    }
    return GradeRes;
}
