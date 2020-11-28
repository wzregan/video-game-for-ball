#ifndef BOARD
#define BOARD
#include <stdio.h>
#define DIS_MAXLEN 5
typedef struct Board{
    int len; //板子长度
    int x; //当前x坐标
    int y;  //当前y坐标
    int speed; //当前速度
    int dir; //当前方向
    char dis[DIS_MAXLEN]; //板子显示字符
}Board;
Board* MakeBoard(int len,int x,int y,int speed,int dir,char * dis);
Board* GetBoard();
#endif
