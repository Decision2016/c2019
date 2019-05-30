#ifndef NODE_H
#define NODE_H


struct Node{
    int NowPlayer;
    int x;
    int y;
    Node();
    Node(int p,int xx,int yy):NowPlayer(p),x(xx),y(yy){}
};

#endif // NODE_H
