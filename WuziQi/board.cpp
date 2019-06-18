#include "board.h"

Board::Board()
{

}

bool Board::StatuCheck(int x,int y){
    std::string NowStatu;
    for(int i = 0;i < DirSum;i++){
        NowStatu = GetStatu(x,y,i);
        if(NowStatu.find("22222") != std::string::npos || NowStatu.find("11111") != std::string::npos) return true;
    }
    return false;
}

void Board::Put(int x,int y,int type){
    board[x][y] = type;
}

int Board::Get(int x,int y){
    return board[x][y];
}

void Board::Clear(){
    memset(board,0,sizeof(board));
}

bool Board::CheckPos(int x,int y){
    bool flag = false;
    for(int i = -1;i <= 1;i++){
        for(int j = -1;j <= 1;j++){
            if(i == 0 && j == 0) {
                continue;
            }
            else if(x + i == 0 || x + i == 14 || y + j == 0 || y + j == 14) {
                continue;
            }
            if(board[x + i][y + j] == 0){
                continue;
            }
            else {
                flag = true;
            }
        }
    }
    return flag;
}

std::string Board::GetStatu(int x,int y,int dir){
    std::string res;
    int posx,posy;
    int dirX[4] = {0,1,1,1};
    int dirY[4] = {1,0,1,-1};
    for(int i = x,j = y;;i -= dirX[dir],j -= dirY[dir]){
        if(i == 0 || j == 0 || i == 14 || j == 14){
            posx = i;
            posy = j;
            break;
        }
    }
    for(int i = posx,j = posy;i >= 0 && j >= 0 && i <= 14 && j <= 14;i += dirX[dir],j += dirY[dir]){
        res.push_back((char)(board[i][j] + '0'));
    }
    return res;
}

int Board::GradeGet(std::string Statu){
    std::string AI_WIN[] = {"22222"};
    std::string People_WIN[] = {"11111"};
    std::string AI_Huo4[] = {"022220"};
    std::string People_Huo4[] = {"011110"};
    std::string AI_Chong4[] = {"022221", "122220", "20222", "22022", "22202"};
    std::string People_Chong4[] = {"011112", "211110", "10111", "11011", "11101"};
    std::string AI_Huo3[] = {"002220", "022200", "020220", "022020"};
    std::string People_Huo3[] = {"001110", "011100", "010110", "011010"};
    std::string AI_Mian3[] = {"002221", "020221", "022021", "022201", "122200", "122020", "120220", "102220", "00222", "20022", "20202", "20220", "02022", "20022", "22002", "22020", "02202", "20202", "22002", "22200"};
    std::string People_Mian3[] = {"001112", "010112", "011012", "011102", "211100", "211010", "210110", "201110", "00111", "10011", "10101", "10110", "01011", "10011", "11001", "11010", "01101", "10101", "11001", "11100"};
    std::string AI_Huo2[] = {"000220", "002020", "002200", "002200", "020200", "022000", "000220", "020020", "020200", "002020", "020020", "022000"};
    std::string People_Huo2[] = {"000110", "001010", "001100", "001100", "010100", "011000", "000110", "010010", "010100", "001010", "010010", "011000"};
    std::string AI_Mian2[] = {"000221", "002021", "020021", "20002", "1020201", "1022001", "122000", "120200", "120020", "1002201"};
    std::string People_Mian2[] = {"000112", "001012", "010012", "10001", "2010102", "2011002", "211000", "210100", "210010", "2001102"};
    std::string AI_One[] = {"2"};
    std::string People_One[] = {"1"};
    std::string NONE[] = {"0"};

    for(int i = 0;i < Win;i++){
        if(Statu.find(AI_WIN[i]) != std::string::npos) return 100000000;
        else if(Statu.find(People_WIN[i]) != std::string::npos) return -100000000;
    }

    for(int i = 0;i < Huo4;i++){
        if(Statu.find(AI_Huo4[i]) != std::string::npos) return 10000000;
        else if(Statu.find(People_Huo4[i]) != std::string::npos) return -10000000;
    }

    for(int i = 0;i < Chong4;i++){
        if(Statu.find(AI_Chong4[i]) != std::string::npos) return 1000000;
        else if(Statu.find(People_Chong4[i]) != std::string::npos) return -1000000;
    }

    for(int i = 0;i < Huo3;i++){
        if(Statu.find(AI_Huo3[i]) != std::string::npos) return 100000;
        else if(Statu.find(People_Huo3[i]) != std::string::npos) return -100000;
    }

    for(int i = 0;i < Mian3;i++){
        if(Statu.find(AI_Mian3[i]) != std::string::npos) return 10000;
        else if(Statu.find(People_Mian3[i]) != std::string::npos) return -10000;
    }

    for(int i = 0;i < Huo2;i++){
        if(Statu.find(AI_Huo2[i]) != std::string::npos) return 1000;
        else if(Statu.find(People_Huo2[i]) != std::string::npos) return -1000;
    }

    for(int i = 0;i < Mian2;i++){
        if(Statu.find(AI_Mian2[i]) != std::string::npos) return 100;
        else if(Statu.find(People_Mian2[i]) != std::string::npos) return -100;
    }

    for(int i = 0;i < One;i++){
        if(Statu.find(AI_One[i]) != std::string::npos) return 10;
        else if(Statu.find(People_One[i]) != std::string::npos) return -10;
    }

    for(int i = 0;i < None;i++){
        if(Statu.find(NONE[i]) != std::string::npos) return 1;
    }
    return 0;
}

int Board::GradeCaculate(int x,int y){
    std::string NowStatu;
    int res = 0;
    for(int i = 0;i < DirSum;i++){
        NowStatu = GetStatu(x,y,i);
        res += GradeGet(NowStatu);
    }
    return res;
}

int Board::GradeSumCaculate(){
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
