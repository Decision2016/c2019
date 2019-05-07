//
// Created by Decision on 2019/4/24.
//

#ifndef MAZE_H_

#define MAZE_H_

#include<vector>

struct edge{
    int from,to,posx,posy;
    edge(int u,int v,int a,int b):from(u),to(v),posx(a),posy(b){}
};
struct point{
    int x,y;
    point(int h,int w):x(h),y(w){}
};
struct maze{
    int pos,set_len;
    int Map[500][500];
    int fa[100000],rank[100000];
    std::vector<edge> edges;
    std::vector<point> point_set;

    maze();
    int tfind(int x);
    void vector_swap(int x);
    int get_rand();
    std::vector<point> refresh(int w,int h);
    void Show(int posx,int posy,int w,int h);
    int Get(int posx,int posy);
};

#endif