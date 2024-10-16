#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../common.h"

#define SPEED 500
#define CANT_MOVE_LEFT 1
#define CANT_MOVE_RIGHT 2

#define CURRENT_FIGURE 1
#define NEXT_FIGURE 2

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;
typedef enum { ALPHA, BETA, GAMMA, DELTA, OMEGA, PSI, ZETA } Figure;

int **create_matrix(int height, int width);
void free_matrix(int **m, int height);
void copy_matrix(int **source, int **dest, int height, int width);

void first_init_state();
GameInfo_t updateCurrentState();

void userInput(UserAction_t action);

// void generate_rectangle();

void spawn_figures();
int **generate_figure(int *size_f);
void rand_rotate_figure();

// void check_input_for_moving();
void shifting();
void rotate(int flag_r);
// void rotate();
int can_it_move(int flag_m);
int can_it_rotate(int **temp);
int is_Attached(); // чекает вниз
void attaching();
void check_are_rows_full();
void change_score(int amount);
void field_down(int number);

void right_move();
void left_move();
void down_move();

void pause_game();
void finish_game();
void level_mechanic();

#endif