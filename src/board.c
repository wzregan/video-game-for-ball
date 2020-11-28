#include "board.h"
#include <stdlib.h>
Board *board=NULL;
Board * MakeBoard(int len,int x,int y,int speed,int dir,char * dis){
    Board *board = (Board*)malloc(sizeof(board));
    board->len = len;
    board->x = x;
    board->y = y;
    board->dir = dir;
    board->speed = speed;
    for(int i =0;i<DIS_MAXLEN;i++){
        board->dis[i] = dis[i];
    }
    *(board->dis) = *dis;
    return board;
}
Board* GetBoard(){
    if(board==NULL){
        board = MakeBoard(8,1,18,50,1,"  ");
    }
    return board;
}
