#ifndef COMMON_H
#define COMMON_H
#include <ncurses.h>
#include <time.h>
#define HEIGHT 20
#define WIDTH 10
#define ACTION_BUTTON 32
#define TERMINATE_BUTTON 27
#define PAUSE_BUTTON 112 // мб добавит большие буквы
#define START_BUTTON 115
typedef enum { Begin, Yes_P, No_P } PauseState;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int status;
  int **field;
  int **figure;
  int figure_size;
  int **next_figure;
  int next_figure_size;
  int coord_x;
  int coord_y;
  int score;
  int level;
  int speed;
  int pause;
} State_t;

State_t *get_current_state();
typedef enum { Initial, Spawn, Moving, Shifting, Attaching, GameOver } Status;
#endif