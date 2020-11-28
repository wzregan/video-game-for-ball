#ifndef VIDEO
#define VIDEO
#define MS 1000
#include "ball.h"
#include "board.h"
typedef struct GameMap
{
    int Left;
    int Right;
    int Top;
    int Bottom;
    char * margin;
}GameMap;
GameMap* MakeMap(int l,int r, int t, int b);//制作地图
void DrawMap(GameMap*); //绘制地图
void SetAutoTask(); //开启自动刷新地图
void showBall(Ball * ball,GameMap *map);
void EraseBall(Ball * ball,GameMap *map);
void ShowBoard(Board *board,GameMap * map);
void EraseBoard(Board *board,GameMap * map);
void setIntervalTask();
void OpenAutoRefres();
void OpenAutoBoardTask();
#endif