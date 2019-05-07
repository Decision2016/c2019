#include "game.h"
#include "maze.h"

game Game;

static std::string s[7] = {"Welcome to Decision's maze!","You can use WASD to move.","Press 1 to chose Simple Mode(Smallest map).","Press 2 to chose Ordinary Mode(Small map).",
               "Press 3 to chose Middle Mode(Large map).","Press 4 to chose Hard Mode(The largest map).",
               "Press 5 to exit."};

int main(){
    Game.preInit();
    Game.PrintInformation(s,7);
    Game.menu();
    return 0;
}