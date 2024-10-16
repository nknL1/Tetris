#include "backend.h"

int **create_matrix(int height, int width) {
  int **matrix = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    int *row = (int *)malloc(width * sizeof(int));
    matrix[i] = row;
    for (int j = 0; j < width; j++) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

void free_matrix(int **m, int height) {
  for (int i = 0; i < height; i++) {
    free(m[i]);
  }
  free(m);
}

void copy_matrix(int **source, int **dest, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      dest[i][j] = source[i][j];
    }
  }
}

State_t *get_current_state() {
  static State_t State;
  return &State;
}

void first_init_state() {
  State_t *State = get_current_state();

  State->field = create_matrix(HEIGHT, WIDTH);
  State->status = Initial;
  State->level = 1;
  State->pause = Begin;
  State->score = 0;
  State->speed = SPEED;
  State->coord_x = 0;
  State->coord_y = 0;
  int next_figure_size;

  int **next_figure = generate_figure(&next_figure_size);
  int **figure = create_matrix(next_figure_size, next_figure_size);
  State->next_figure_size = next_figure_size;
  State->next_figure = next_figure;

  State->figure = figure;
  State->figure_size = next_figure_size;
  rand_rotate_figure();
}

GameInfo_t updateCurrentState() {
  State_t *state = get_current_state();
  GameInfo_t info;
  info.field = create_matrix(HEIGHT, WIDTH);
  copy_matrix(state->field, info.field, HEIGHT, WIDTH);
  info.next = create_matrix(state->next_figure_size, state->next_figure_size);
  copy_matrix(state->next_figure, info.next, state->next_figure_size,
              state->next_figure_size);
  if (state->status != Initial) {
    for (int i = 0; i < state->figure_size; i++) {
      for (int j = 0; j < state->figure_size; j++) {
        int new_x = state->coord_x - i;
        int new_y = state->coord_y + j;
        if ((state->figure[i][j] == 1) && (new_x >= 0) && (new_y < WIDTH)) {
          info.field[new_x][new_y] = 1;
        }
      }
    }
  }

  int high_score;
  FILE *file = fopen("./max_score.txt", "r");
  fscanf(file, "%d", &high_score);
  fclose(file);
  info.high_score = high_score;

  info.score = state->score;
  info.level = state->level;
  info.speed = state->speed;
  info.pause = state->pause;
  return info;
}

void spawn_figures() {
  State_t *state = get_current_state();
  free_matrix(state->figure, state->figure_size);
  state->figure_size = state->next_figure_size;
  state->figure = state->next_figure;

  state->coord_x = 0;
  state->coord_y = 4;

  int next_figure_size;
  int **next_figure = generate_figure(&next_figure_size);
  state->next_figure_size = next_figure_size;

  state->next_figure = next_figure;
  rand_rotate_figure(NEXT_FIGURE);
  state->status = Moving;
}

void shifting() {
  State_t *state = get_current_state();
  if (!is_Attached()) {
    (state->coord_x)++;
    state->status = Moving;
  } else {
    state->status = Attaching;
  }
}

int can_it_move(int flag_m) {
  int flag = 0;
  State_t *state = get_current_state();
  int x = state->coord_x;
  int y = state->coord_y;
  for (int i = 0; i < state->figure_size; i++) {
    for (int j = 0; j < state->figure_size; j++) {
      int new_x = state->coord_x - i;
      int new_y = state->coord_y + j;
      if (flag_m == CANT_MOVE_LEFT) {
        new_y--;
        if ((state->figure[i][j] == 1) && (new_y < 0)) {
          flag = CANT_MOVE_LEFT;
        } else if ((new_y >= 0) && (new_x >= 0)) {
          if ((state->figure[i][j] == 1) && (state->field[new_x][new_y] == 1))
            flag = CANT_MOVE_LEFT;
        }
      } else if (flag_m == CANT_MOVE_RIGHT) {
        new_y++;
        if ((state->figure[i][j] == 1) && (new_y >= WIDTH)) {
          flag = CANT_MOVE_RIGHT;
        } else if ((new_y >= 0) && (new_x >= 0)) {
          if ((state->figure[i][j] == 1) && (state->field[new_x][new_y] == 1))
            flag = CANT_MOVE_RIGHT;
        }
      }
    }
  }
  return flag;
}

int is_Attached() {
  unsigned int flag = 0;
  State_t *state = get_current_state();

  for (int i = 0; i < state->figure_size; i++) {
    for (int j = 0; j < state->figure_size; j++) {
      int new_x = state->coord_x + 1 - i;
      int new_y = state->coord_y + j;

      if (state->figure[i][j] == 1) {
        if (new_x >= HEIGHT) {
          flag = 1;
        } else if ((new_x >= 0) && (state->field[new_x][new_y] == 1)) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

void attaching() {
  State_t *state = get_current_state();

  for (int i = 0; i < state->figure_size; i++) {
    for (int j = 0; j < state->figure_size; j++) {
      int new_x = state->coord_x - i;
      int new_y = state->coord_y + j;

      if ((state->figure[i][j] == 1) && (new_x >= 0) && (new_y >= 0) &&
          (new_y < WIDTH) && (new_x < HEIGHT)) {
        state->field[new_x][new_y] = 1;
      } else if ((state->figure[i][j] == 1) && (new_x <= 0)) {
        state->status = GameOver;
      }
    }
  }
  if (state->status != GameOver) {
    check_are_rows_full();
    level_mechanic();
    state->status = Spawn;
  }
}

void check_are_rows_full() {
  State_t *state = get_current_state();
  int count = 0;
  int amount = 0;
  // unsigned int flag = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (state->field[i][j] == 1)
        count++;
    }
    if (count == 10) {
      field_down(i);
      amount++;
    }
    count = 0;
  }
  change_score(amount);
  // return flag;
}

void change_score(int amount) {
  State_t *state = get_current_state();
  if (amount == 1) {
    state->score += 100;
  } else if (amount == 2) {
    state->score += 300;
  } else if (amount == 3) {
    state->score += 700;
  } else if (amount == 4) {
    state->score += 1500;
  }
}
void field_down(int number) {
  State_t *state = get_current_state();
  int **temp = create_matrix(HEIGHT, WIDTH);

  for (int i = 1; i < number + 1; i++) {
    for (int j = 0; j < WIDTH; j++) {
      temp[i][j] = state->field[i - 1][j];
    }
  }
  for (int i = number + 1; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      temp[i][j] = state->field[i][j];
    }
  }
  free_matrix(state->field, HEIGHT);
  state->field = create_matrix(HEIGHT, WIDTH);
  copy_matrix(temp, state->field, HEIGHT, WIDTH);
  free_matrix(temp, HEIGHT);
}

void userInput(UserAction_t action) {
  State_t *state = get_current_state();
  if ((action == Start)) {
    state->pause = No_P;
    state->status = Spawn;
  } else if (action == Down && state->pause != Yes_P) {
    down_move();
  } else if (action == Right && state->pause != Yes_P) {
    right_move();
  } else if (action == Left && state->pause != Yes_P) {
    left_move();
  } else if (action == Action && state->pause != Yes_P) {
    rotate(CURRENT_FIGURE);
  } else if ((action == Pause) && (state->status != Initial) &&
             state->pause != Yes_P) {
    pause_game();
  } else if (action == Pause && state->pause == Yes_P) {
    state->pause = No_P;
    // state->status = Shifting;
  } else if (action == Terminate) {
    finish_game();
  }
}

void left_move() {
  State_t *state = get_current_state();
  if (can_it_move(CANT_MOVE_LEFT) != CANT_MOVE_LEFT) {
    (state->coord_y)--;
  }
}

void right_move() {
  State_t *state = get_current_state();
  if (can_it_move(CANT_MOVE_RIGHT) != CANT_MOVE_RIGHT) {
    (state->coord_y)++;
  }
}

void down_move() {
  State_t *state = get_current_state();
  if (is_Attached() == 0) {
    (state->coord_x)++;
  } else {
    state->status = Attaching;
  }
}

int **generate_figure(int *size_f) {
  int type_f = rand() % 7;

  if (type_f == ALPHA) {
    *size_f = 4;
  } else if (type_f == DELTA) {
    *size_f = 2;
  } else {
    *size_f = 3;
  }

  int **figure = create_matrix(*size_f, *size_f);

  if (type_f == ALPHA) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[0][3] = 1;
  } else if (type_f == BETA) {
    figure[1][0] = 1;
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
  } else if (type_f == GAMMA) {
    figure[1][2] = 1;
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
  } else if (type_f == DELTA) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
  } else if (type_f == OMEGA) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (type_f == PSI) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][1] = 1;
  } else {
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
  }
  return figure;
}

void pause_game() {
  State_t *state = get_current_state();
  state->pause = Yes_P;
}

void rotate(int flag_r) // flag_r - определяет менять нынешний или следующий
{
  State_t *state = get_current_state();
  int size_m;
  int **temp;
  int **source;
  if (flag_r == CURRENT_FIGURE) {
    size_m = state->figure_size;
    temp = create_matrix(size_m, size_m);
    source = create_matrix(size_m, size_m);
    copy_matrix(state->figure, source, size_m, size_m);
  } else if (flag_r == NEXT_FIGURE) {
    size_m = state->next_figure_size;
    temp = create_matrix(size_m, size_m);
    source = create_matrix(size_m, size_m);
    copy_matrix(state->next_figure, source, size_m, size_m);
  }

  for (int i = 0; i < size_m; i++) {
    for (int j = 0; j < size_m; j++) {
      temp[i][j] = 0;
    }
  }

  if (size_m == 4) {
    if (source[0][0] == 1) {
      temp[0][1] = 1;
      temp[1][1] = 1;
      temp[2][1] = 1;
      temp[3][1] = 1;
    } else {
      temp[0][0] = 1;
      temp[0][1] = 1;
      temp[0][2] = 1;
      temp[0][3] = 1;
    }
  } else {
    for (int i = 0; i < size_m; i++) {
      for (int j = 0; j < size_m; j++) {
        temp[j][size_m - 1 - i] = source[i][j];
      }
    }
  }
  if (flag_r == CURRENT_FIGURE) {
    if (can_it_rotate(temp) == 1) {
      copy_matrix(temp, state->figure, size_m, size_m);
    }
  } else if (flag_r == NEXT_FIGURE) {
    copy_matrix(temp, state->next_figure, size_m, size_m);
  }

  free_matrix(temp, size_m);
  free_matrix(source, size_m);
}

void rand_rotate_figure() {
  int rotations = rand() % 4;
  for (int i = 0; i < rotations; i++) {
    rotate(NEXT_FIGURE);
  }
}

int can_it_rotate(int **temp) {
  int flag = 1;
  State_t *state = get_current_state();
  for (int i = 0; i < state->figure_size; i++) {
    for (int j = 0; j < state->figure_size; j++) {
      int new_x = state->coord_x - i;
      int new_y = state->coord_y + j;
      if ((temp[i][j] == 1) && ((new_y < 0) || (new_y >= WIDTH))) {
        flag = 0;
      } else if ((new_y >= 0) && (new_x >= 0) && (new_y < WIDTH)) {
        if ((temp[i][j] == 1 && state->field[new_x][new_y]) == 1) {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

void finish_game() {
  State_t *state = get_current_state();
  free_matrix(state->field, HEIGHT);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
}

void save_max_score() {
  State_t *state = get_current_state();
  FILE *file;

  int high_score;
  file = fopen("max_score.txt", "r");
  fscanf(file, "%d", &high_score);
  fclose(file);

  if (state->score > high_score) {
    file = fopen("max_score.txt", "w");
    fprintf(file, "%d", state->score);
    fclose(file);
  }
}

void level_mechanic() {
  State_t *state = get_current_state();
  if (state->score >= 600 && state->level != 10) {
    state->level = 0;
    state->speed = 500;
    for (int i = 0; i <= state->score / 600; i++) {
      state->level++;
      state->speed += 50;
    }
  }
  save_max_score();
}
