#include <stdio.h>
#include "game.h"
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "board.h"

int main(){
    initscr();
    clear();
    GameInit();  
    GameWait();
    
    endwin();
    return 0;
}
