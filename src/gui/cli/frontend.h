#ifndef FRONT_H
#define FRONT_H

#define MAP_PADDING 2

#include <stdlib.h>

#include "../../common.h"

void render(GameInfo_t info);
void print_rectangle(WINDOW *win, int top_y, int bottom_y, int left_x,
                     int right_x);
void terminate_game();
// void terminate_game();

#endif