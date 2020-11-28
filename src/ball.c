#include "ball.h"
#include <stdio.h>
#include <stdlib.h>
Ball *ball=NULL;
Ball* getBall(){
    if(ball==NULL){
        ball = (Ball*)malloc(sizeof(Ball));
        ball->v_x=1;
        ball->v_y=1;
        ball->x=1;
        ball->y=1;
    }
    return ball;
}
