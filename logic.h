#ifndef LOGIC_H
#define LOGIC_H

    #include "common.h"
    #include "graphics.h" // for proper_shutdown()

    void game_init(board *b);
    void addCheckOutOfBounds(int x, int y, board *board);
    void reveal(int x, int y, board *board);
    void checkOutOfBounds(int x, int y, board *board);
    void generateBoard(board *board);
    void process_input(mouse *mouse, board *board);
    void proper_shutdown(void);

#endif // !LOGIC_H