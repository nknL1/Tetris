#include "frontend.h"

void render(GameInfo_t info) {
  WINDOW *game_window =
      newwin(HEIGHT + MAP_PADDING, 3 * WIDTH + MAP_PADDING, 0, 0);
  refresh();
  box(game_window, 0, 0);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (info.field[i][j] == 1) {
        mvwprintw(game_window, i + 1, 3 * j + 1, "[ ]");
      } else {
        mvwprintw(game_window, i + 1, 3 * j + 1, "   ");
      }
    }
  }

  State_t *state = get_current_state();
  if (info.pause == Begin) {
    mvwprintw(game_window, HEIGHT / 2, WIDTH - 3, "Press S to start");
  }
  wrefresh(game_window);

  if (info.pause == Yes_P) {
    WINDOW *text_window = newwin(3, 7, 9, 13);
    refresh();
    box(text_window, 0, 0);
    mvwprintw(text_window, 1, 1, "PAUSE");
    wrefresh(text_window);
    delwin(text_window);
  }

  WINDOW *params_window = newwin(HEIGHT + MAP_PADDING, 3 * WIDTH + MAP_PADDING,
                                 0, 3 * WIDTH + MAP_PADDING);
  refresh();
  box(params_window, 0, 0);

  print_rectangle(params_window, 1, 3, 3, 18);
  char score[10];
  sprintf(score, "%d", info.score);
  mvwprintw(params_window, 2, 5, "SCORE: ");
  mvwprintw(params_window, 2, 12, score);

  print_rectangle(params_window, 4, 6, 3, 18);
  char level[10];
  sprintf(level, "%d", info.level);
  mvwprintw(params_window, 5, 5, "LEVEL: ");
  mvwprintw(params_window, 5, 12, level);

  print_rectangle(params_window, 7, 9, 3, 18);
  char speed[10];
  sprintf(speed, "%d", info.speed);
  mvwprintw(params_window, 8, 5, "SPEED: ");
  mvwprintw(params_window, 8, 12, speed);

  // print_rectangle(params_window, 10, 9, 3, 18);
  char high_score[10];
  sprintf(high_score, "%d", info.high_score);
  mvwprintw(params_window, 11, 5, "MAX SCORE: ");
  mvwprintw(params_window, 11, 16, high_score);

  mvwprintw(params_window, 14, 5, "NEXT:");
  for (int i = 0; i < state->next_figure_size; i++) {
    for (int j = 0; j < state->next_figure_size; j++) {
      if (info.next[i][j] == 1) {
        mvwprintw(params_window, WIDTH + 1 + 3 + MAP_PADDING - i, 5 + 7 + 3 * j,
                  "[ ]");
      }
    }
  }

  wrefresh(params_window);

  for (int i = 0; i < HEIGHT; i++) {
    free(info.field[i]);
  }
  free(info.field);

  for (int i = 0; i < state->next_figure_size; i++) {
    free(info.next[i]);
  }
  free(info.next);

  delwin(game_window);
  delwin(params_window);
}

void print_rectangle(WINDOW *win, int top_y, int bottom_y, int left_x,
                     int right_x) {
  mvwaddch(win, top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++)
    mvwaddch(win, top_y, i, ACS_HLINE);
  mvwaddch(win, top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvwaddch(win, i, left_x, ACS_VLINE);
    mvwaddch(win, i, right_x, ACS_VLINE);
  }

  mvwaddch(win, bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++)
    mvwaddch(win, bottom_y, i, ACS_HLINE);
  mvwaddch(win, bottom_y, i, ACS_LRCORNER);
}

void terminate_game() {
  endwin();
  exit(0);
}
