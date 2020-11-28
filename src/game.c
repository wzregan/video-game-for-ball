#include "video.h"
#include <curses.h>
#include <signal.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "game.h"
#include "board.h"
#include "ball.h"
#include "keymap.h"
GameMap * map;
void GameInit(){
    map = MakeMap(15,57,1,20); //制作地图
    DrawMap(map); // 画出地图
    //初始化木板
    Board* board = GetBoard();
    ShowBoard(board,map);
    showBall(getBall(),map);
    OpenAutoRefres();
    OpenAutoBoardTask();

    SetAutoTask();

    //绑定IO处理函数
    fcntl(0,F_SETOWN,getpid()); //设置一个用来接收SIGIO信号的进程
    int s = fcntl(0,F_GETFL); //得到文件描述符
    fcntl(0,F_SETFL,(s|O_ASYNC)); //为文件描述符设置O_ASYNC
    signal(SIGIO,KeyHanlde); 
}

void KeyHanlde(){
    Key key = getchar();
    if(key==UP){
        if(GetBoard()->speed>20){
            GetBoard()->speed-=5;
            OpenAutoBoardTask();
        }
    }else if(key=DOWN){
        if(GetBoard()->speed<80){
            GetBoard()->speed+=5;
            OpenAutoBoardTask();
        }
    }
}

void GameWait(){
    while (1)
    {
        pause();
    }
}