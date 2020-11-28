#include <curses.h>
#include <stdlib.h>
#include "video.h"
#include "board.h"
#include <sys/time.h>
#include <signal.h>
#include "ball.h"
GameMap* MakeMap(int l,int r, int t, int b){
    GameMap *map = (GameMap*)malloc(sizeof(GameMap));
    map->Bottom = b;
    map->Top = t;
    map->Left = l;
    map->Right = r;
    return map;
} //制作地图
void DrawMap(GameMap *map){
    for(int i = map->Left;i<map->Right;i++){
        move(map->Top,i);
        addch('_');
        move(map->Bottom,i);
        addch('_');
    }
    for(int i = map->Top+1;i<=map->Bottom;i++){
        move(i,map->Left);
        addch('|');
        move(i,map->Right);
        addch('|');
    }
}//绘制地图

void ShowBoard(Board *board,GameMap * map){
    int x = map->Left + board->x;
    int y = map->Top + board->y;
    for(int i =x;i<x+board->len;i++){
        move(y,i);
        standout();
        addstr(board->dis);
        standend();
    }
}

void EraseBoard(Board *board,GameMap * map){
    int x = map->Left + board->x;
    int y = map->Top + board->y;
    for(int i =x;i<x+board->len;i++){
        if(i<=map->Left || i>=map->Right-1){
            continue;
        }
        move(y,i);
        addstr(board->dis);
    }
}
int timers[4][2]={{10,-1},{100,-1},{500,-1},{1000,-1}};
void * tasks[];

void timer_manager(int sig){
    for(int i=0;i<4;i++){
        if(timers[i][1]==-1){
            break;
        }else if(timers[i][1]==0){
            void (*task)()=tasks[i];
            task();
            timers[i][1] = timers[i][0];
        }else{
            timers[i][1]--;
        }
    }
}
void auto_refresh_task(){
    move(0,0);
    char buf[20];
    sprintf(buf,"current speed:%d",GetBoard()->speed);
    addstr(buf);
    refresh();
}
void OpenAutoRefres(){
    tasks[0] = auto_refresh_task;
    timers[0][0]=10;
    timers[0][1]=0;
}

extern GameMap * map;
void auto_move_board_task(){
    Board* board = GetBoard();

    EraseBoard(board,map);
    board->x += board->dir;
    if(board->x==0 || board->x+board->len==map->Right-map->Left){
        board->dir=-board->dir;
        return;
    }
    ShowBoard(board,map);
}
void OpenAutoBoardTask(){
    tasks[1] = auto_move_board_task;
    timers[1][0]=GetBoard()->speed;
    timers[1][1]=GetBoard()->speed;
}
//定时刷新屏幕
void SetAutoTask(){
    signal(SIGALRM,timer_manager);
    struct itimerval timer;
    timer.it_value.tv_sec=0;
    timer.it_value.tv_usec=1000;
    timer.it_interval.tv_sec=0;
    timer.it_interval.tv_usec=1000;
    int c = setitimer(ITIMER_REAL,&timer,NULL);
}

void showBall(Ball * ball,GameMap *map){
    int x = map->Left + ball->x;
    int y = map->Top + ball->y;
    move(y,x);
    addstr("O");
}

void EraseBall(Ball * ball,GameMap *map){
    int x = map->Left + ball->x;
    int y = map->Top + ball->y;
    move(y,x);
    addstr(" ");
}

//设置任务
void setIntervalTask(){
    static unsigned i = 0;
}