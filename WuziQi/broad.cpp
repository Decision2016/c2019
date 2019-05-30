#include "broad.h"

Broad::Broad()
{

}

bool Broad::StatuCheck(int x,int y){
    int NowStatu;
    for(int i = 0;i < 8;i++){
        NowStatu = GetStatu(x,y,i);
        if(NowStatu == 242 || NowStatu == 121) return true;
    }
    return false;
}

void Broad::Put(int x,int y,int type){
    broad[x][y] = type;
}

int Broad::Get(int x,int y){
    return broad[x][y];
}

void Broad::Clear(){
    memset(broad,0,sizeof(broad));
}

bool Broad::CheckPos(int x,int y){
    bool flag = 0;
    for(int i = -1;i <= 1;i++){
        for(int j = -1;j <= 1;j++){
            if(i == 0 && j == 0) {
                continue;
            }
            else if(x + i == 0 || x + i == 14 || y + j == 0 || y + j == 14) {
                continue;
            }
            if(broad[x + i][y + j] == 0){
                continue;
            }
            else {
                flag = true;
            }
        }
    }
    return flag;
}

int Broad::GetStatu(int x,int y,int dir){
    int res = 0,posx = x,posy = y;
    int dirX[8] = {0,1,1,1,0,-1,-1,-1};
    int dirY[8] = {-1,-1,0,1,1,1,0,-1};
    for(int i = 0;i <= 5;i++){
        if(posx == 0 || posx == 14 || posy == 0||posy == 14){
            break;
        }
        res = res*3 + this ->Get(posx,posy);
        posx += dirX[dir];
        posy += dirY[dir];
    }
    return res;
}

int Broad::GradeGet(int Statu){
    int AI_WIN[] = {242};
    int People_WIN[] = {121};
    int AI_Huo4[] = {240};
    int People_Huo4[] = {120};
    int AI_Chong4[] = {241,483,188,224,236};
    int People_Chong4[] = {122,606,94,112,118};
    int AI_Huo3[] = {78,234,186,222};
    int People_Huo3[] = {39,117,93,111};
    int AI_Mian3[] = {79,187,223,235,477,465,429,321,26,170,182,186,62,170,218,222,74,182,218,234};
    int People_Mian3[] = {41,95,113,119,603,597,579,525,13,85,91,93,31,85,109,111,37,91,109,117};
    int AI_Huo2[] = {24,60,72,72,180,216,24,168,180,60,168,216};
    int People_Huo2[] = {12,30,36,36,90,108,12,84,90,30,84,108};
    int AI_Mian2[] = {25,61,169,164,910,946,459,423,411,802};
    int People_Mian2[] = {14,32,86,82,1550,1568,594,576,570,1496};
    int AI_One[] = {2};
    int People_One[] = {1};
    int NONE[] = {0};

    for(int i = 0;i < Win;i++){
        if(AI_WIN[i] == Statu) return 100000000;
        else if(People_WIN[i] == Statu) return -100000000;
    }

    for(int i = 0;i < Huo4;i++){
        if(AI_Huo4[i] == Statu) return 10000000;
        else if(People_Huo4[i] == Statu) return -10000000;
    }

    for(int i = 0;i < Chong4;i++){
        if(AI_Chong4[i] == Statu) return 1000000;
        else if(People_Chong4[i] == Statu) return -1000000;
    }

    for(int i = 0;i < Huo3;i++){
        if(AI_Huo3[i] == Statu) return 100000;
        else if(People_Huo3[i] == Statu) return -100000;
    }

    for(int i = 0;i < Mian3;i++){
        if(AI_Mian3[i] == Statu) return 10000;
        else if(People_Mian3[i] == Statu) return -10000;
    }

    for(int i = 0;i < Huo2;i++){
        if(AI_Huo2[i] == Statu) return 1000;
        else if(People_Huo2[i] == Statu) return -1000;
    }

    for(int i = 0;i < Mian2;i++){
        if(AI_Mian2[i] == Statu) return 100;
        else if(People_Mian2[i] == Statu) return -100;
    }

    for(int i = 0;i < One;i++){
        if(AI_One[i] == Statu) return 10;
        else if(People_One[i] == Statu) return -10;
    }

    for(int i = 0;i < None;i++){
        if(NONE[i] == Statu) return 1;
    }
    return 0;
}

int Broad::GradeCaculate(int x,int y){
    int NowStatu;
    int res = 0;
    for(int i = 0;i < DirSum;i++){
        NowStatu = GetStatu(x,y,i);
        res += GradeGet(NowStatu);
    }
    return res;
}

int Broad::GradeSumCaculate(){
    int res = 0;
    for(int i = 1;i < 14;i++){
        for(int j = 1;j < 14;j++){
            if(Get(i,j) != 0){
                res += GradeCaculate(i,j);
            }
        }
    }
    return res;
}
