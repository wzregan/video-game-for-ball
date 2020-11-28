#include <curses.h>
#include <stdlib.h>
#include "video.h"
#include "board.h"
#include <sys/time.h>
#include <signal.h>
#include "ball.h"
extern GameMap * map;
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
    if(x==map->Left||x==map->Right||y==map->Top){
        return;
    }
    if(y==map->Bottom){
        addstr("_");
        return;
    }
    addstr(" ");
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
//板子移动的任务
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
//开启Board移动
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
//小球移动任务
void auto_move_ball_task(){
    static int step = 1;
    Ball * ball = getBall();
    EraseBall(ball,map);
    if(step%1==0){
        ball->y=ball->y+ball->v_y;
    }
    ball->x=ball->x+ball->v_x;

    showBall(ball,map);
    Collisiondetect(ball,map,GetBoard());
    step++;
}

void openAutoMoveBallTask(){
    timers[2][0]=100;
    timers[2][1]=0;
    tasks[2] = auto_move_ball_task;
}
//关闭闹钟
void closeTimer(){
    struct itimerval old_timeral;
    getitimer(ITIMER_REAL,&old_timeral);
    struct itimerval new_timeral;
    new_timeral.it_interval.tv_sec=0;
    new_timeral.it_interval.tv_usec=0;
    new_timeral.it_value.tv_sec=0;
    new_timeral.it_value.tv_usec=0;
    setitimer(ITIMER_REAL,&new_timeral,&old_timeral);   
}
//碰撞检测
void Collisiondetect(Ball *ball,GameMap* map,Board *board){
    if(ball->y==board->y&&ball->x>=board->x&&ball->x<=board->x+board+board->len){
        ball->v_y=-ball->v_y;
    }
    if(ball->x<=1){
        ball->v_x=-ball->v_x;
    }
    if(ball->x+map->Left>map->Right){
        ball->v_x=-ball->v_x;
    }
    if(ball->y+map->Top>=map->Bottom+1){
        ball->v_y=0;
        ball->v_x=0;
        closeTimer();
    }
    if(ball->y<=1){
        ball->v_y=-ball->v_y;
    }

}