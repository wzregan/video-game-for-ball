#ifndef BALL
#define BALL
typedef struct Ball{
    int x;
    int y;
    int v_x;
    int v_y;
}Ball;
Ball* getBall();
#endif