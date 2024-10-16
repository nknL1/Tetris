#ifndef GAME_H
#define GAME_H
#define WIN_INIT(time)                                                         \
  {                                                                            \
    initscr();                                                                 \
    cbreak();                                                                  \
    timeout(time);                                                             \
    noecho();                                                                  \
    curs_set(0);                                                               \
    keypad(stdscr, TRUE);                                                      \
  }

#include <unistd.h>

#include "brick_game/tetris/backend.h"
#include "common.h"
#include "gui/cli/frontend.h"

void updateUserAction();
void Input_User_Action();
void check_input_for_moving();

#endif