//
// Created by Decision on 2019/4/24.
//

#include "maze.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>

maze::maze(){

}

int maze::tfind(int x){
    return x == fa[x]?x:fa[x] = tfind(fa[x]);
}

void maze::vector_swap(int x){
    pos--;
    std::swap(edges[x],edges[pos]);
}

int maze::get_rand(){
    int now = pos,rand_num;
    std::srand(int(time(0)));
    rand_num = rand()%now;
    return rand_num;
}

std::vector<point> maze::refresh(int w,int h){
    edges.clear();
    point_set.clear();
    w = 2*w + 2,h = 2*h+2;
    int tmp_map[h+1][w+1];
    std::vector<point> res;

    for(int i = 0;i<=h;i++){
        for(int j = 0;j<=w;j++){
            Map[i][j] = 1;
        }
    }

    for(int i = 1;i<h;i+=2){
        for(int j = 1;j<w;j+=2)
        {
            Map[i][j] = 0;
            tmp_map[i][j] = point_set.size();
            point_set.push_back(point(i,j));
        }
    }

    set_len = point_set.size();
    for(int i = 0;i<set_len;i++) fa[i] = i,rank[i] = 1;
    for(int i = 1;i<=h;i+=2){
        for(int j = 1;j<=w;j+=2){
            if(i+2<=h) edges.push_back(edge(tmp_map[i][j],tmp_map[i+2][j],i+1,j));
            if(j+2<=w) edges.push_back(edge(tmp_map[i][j],tmp_map[i][j+2],i,j+1));
        }
    }

    set_len = edges.size();
    pos = edges.size();

    while(set_len){
        int now = get_rand(),from,to;
        edge t = edges[now];
        from = tfind(t.from),to = tfind(t.to);
        if(from != to){
            if(rank[from] > rank[to]) fa[to] = from;
            else fa[from] = to;
            Map[t.posx][t.posy] = 0;
        }
        set_len--;
        vector_swap(now);
    }
    bool flag = 0;
    for(int i = 1;i<w;i++){
        if(flag) break;
        for(int j = w-1;j>=1;j--){
            if(Map[1][i] == 0&&Map[h-1][j] == 0 && tfind(tmp_map[1][i]) == tfind(tmp_map[h-1][j]))
            {
                flag = 1;
                res.push_back(point(0,i));
                res.push_back(point(h,j));
                Map[0][i] = Map[h][j] = 0;
                break;
            }
        }
    }
    return res;
}


void maze::Show(int posx,int posy,int w,int h){
    for(int i = 0;i<=h;i++){
        for(int j = 0;j<=w;j++){
            if(i == posx&&j == posy) std::cout<<"\033[31m"<<"@";
            else if(Map[i][j] == 1) std::cout<<"\033[32m" <<"#";
            else std::cout<<" ";
        }
        std::cout<<std::endl;
    }
}

int maze::Get(int posx,int posy){
    return Map[posx][posy];
}
