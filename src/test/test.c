#include "test.h"

START_TEST(init_1) {
  first_init_state();
  State_t *state = get_current_state();
  ck_assert_int_eq(state->score, 0);
  finish_game();
  //   free_matrix(state->figure, state->figure_size);
  //   free_matrix(state->next_figure, state->next_figure_size);
  //   free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(init_2) {
  first_init_state();
  State_t *state = get_current_state();
  ck_assert_int_eq(state->level, 1);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(init_3) {
  first_init_state();
  State_t *state = get_current_state();
  ck_assert_int_eq(state->pause, 0);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(init_4) {
  first_init_state();
  State_t *state = get_current_state();
  ck_assert_int_eq(state->coord_x, 0);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(init_5) {
  first_init_state();
  State_t *state = get_current_state();
  ck_assert_int_eq(state->coord_y, 0);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(shift) {
  first_init_state();
  shifting();
  State_t *state = get_current_state();
  ck_assert_int_eq(state->coord_x, 1);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(spawn) {
  first_init_state();
  State_t *state = get_current_state();
  int block_size = state->next_figure_size;
  spawn_figures();
  ck_assert_int_eq(state->figure_size, block_size);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(right_1) {
  first_init_state();
  State_t *state = get_current_state();
  int coord_y = state->coord_y;
  right_move();
  ck_assert_int_eq(state->coord_y, coord_y + 1);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(left_1) {
  first_init_state();
  State_t *state = get_current_state();
  int coord_y = state->coord_y;
  left_move();
  ck_assert_int_eq(state->coord_y, coord_y - 1);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(input_start) {
  first_init_state();
  State_t *state = get_current_state();
  userInput(Start);
  ck_assert_int_eq(state->status, Spawn);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(consume_1) {
  first_init_state();
  State_t *state = get_current_state();
  int score = state->score;
  check_are_rows_full();
  ck_assert_int_eq(state->score, score);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(pause_1) {
  first_init_state();
  State_t *state = get_current_state();
  pause_game();
  ck_assert_int_eq(state->pause, 1);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(input_left) {
  first_init_state();
  State_t *state = get_current_state();
  state->status = Moving;
  userInput(Left);
  ck_assert_int_eq(state->status, Moving);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(input_right) {
  first_init_state();
  State_t *state = get_current_state();
  state->status = Moving;
  userInput(Right);
  ck_assert_int_eq(state->status, Moving);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST
// otsuda
START_TEST(consume_2) {
  first_init_state();
  State_t *state = get_current_state();
  state->score = 10000;
  check_are_rows_full();
  ck_assert_int_eq(state->score, 10000);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(input_down) {
  first_init_state();
  State_t *state = get_current_state();
  state->status = Moving;
  userInput(Down);
  ck_assert_int_eq(state->status, Moving);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(can_rotate_1) {
  first_init_state();
  State_t *state = get_current_state();
  rotate(1);
  ck_assert_int_eq(state->status, 0);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(rotate_1) {
  first_init_state();
  int block_size;
  int **new_block = generate_figure(&block_size);
  int can_rotate = can_it_rotate(new_block);
  ck_assert_int_eq(can_rotate, 1);
  State_t *state = get_current_state();
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
  free_matrix(new_block, block_size);
}
END_TEST

START_TEST(input_action) {
  first_init_state();
  State_t *state = get_current_state();
  state->status = Moving;
  userInput(Action);
  ck_assert_int_eq(state->status, Moving);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(update_state) {
  first_init_state();
  State_t *state = get_current_state();
  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(state->score, info.score);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
  for (int i = 0; i < HEIGHT; i++) {
    free(info.field[i]);
  }
  free(info.field);
  for (int i = 0; i < state->next_figure_size; i++) {
    free(info.next[i]);
  }
  free(info.next);
}
END_TEST

START_TEST(consume_3) {
  first_init_state();
  State_t *state = get_current_state();
  for (int j = 0; j < WIDTH; j++) {
    state->field[HEIGHT - 1][j] = 1;
  }
  check_are_rows_full();
  ck_assert_int_eq(state->score, 100);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(consume_4) {
  first_init_state();
  State_t *state = get_current_state();
  for (int i = HEIGHT - 1; i > HEIGHT - 3; i--) {
    for (int j = 0; j < WIDTH; j++) {
      state->field[i][j] = 1;
    }
  }
  check_are_rows_full();
  ck_assert_int_eq(state->score, 300);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(consume_5) {
  first_init_state();
  State_t *state = get_current_state();
  for (int i = HEIGHT - 1; i > HEIGHT - 4; i--) {
    for (int j = 0; j < WIDTH; j++) {
      state->field[i][j] = 1;
    }
  }
  check_are_rows_full();
  ck_assert_int_eq(state->score, 700);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(consume_6) {
  first_init_state();
  State_t *state = get_current_state();
  for (int i = HEIGHT - 1; i > HEIGHT - 5; i--) {
    for (int j = 0; j < WIDTH; j++) {
      state->field[i][j] = 1;
    }
  }
  check_are_rows_full();
  ck_assert_int_eq(state->score, 1500);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(input_terminate) {
  first_init_state();
  State_t *state = get_current_state();
  userInput(Terminate);
  ck_assert_int_eq(state->status, Initial);
}
END_TEST

START_TEST(right_2) {
  first_init_state();
  State_t *state = get_current_state();
  int coord_y = state->coord_y;
  state->coord_y += 2;
  state->coord_x += 4;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      state->field[i][j] = 1;
    }
  }
  right_move();
  ck_assert_int_eq(state->coord_y, coord_y + 3);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(attaching_1) {
  first_init_state();
  spawn_figures();
  State_t *state = get_current_state();
  state->coord_x = 0;
  state->coord_y = 2;
  attaching();
  ck_assert_int_eq(state->status, GameOver);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(attaching_2) {
  first_init_state();
  spawn_figures();
  State_t *state = get_current_state();
  state->coord_x = 7;
  state->coord_y = 8;
  attaching();
  ck_assert_int_eq(state->status, Spawn);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

START_TEST(attaching_3) {
  first_init_state();
  spawn_figures();
  State_t *state = get_current_state();
  int is_att = is_Attached();
  ck_assert_int_eq(is_att, 0);
  free_matrix(state->figure, state->figure_size);
  free_matrix(state->next_figure, state->next_figure_size);
  free_matrix(state->field, HEIGHT);
}
END_TEST

// Функция создания набора тестов.
Suite *tetris_suite(void) {
  Suite *suite;
  suite = suite_create("Check");

  TCase *tc_tetris;

  tc_tetris = tcase_create("OK");
  suite_add_tcase(suite, tc_tetris);
  tcase_add_test(tc_tetris, init_1);
  tcase_add_test(tc_tetris, init_2);
  tcase_add_test(tc_tetris, init_3);
  tcase_add_test(tc_tetris, init_4);
  tcase_add_test(tc_tetris, init_5);
  tcase_add_test(tc_tetris, shift);
  tcase_add_test(tc_tetris, spawn);
  tcase_add_test(tc_tetris, right_1);
  tcase_add_test(tc_tetris, left_1);
  tcase_add_test(tc_tetris, input_start);
  tcase_add_test(tc_tetris, consume_1);
  tcase_add_test(tc_tetris, pause_1);
  tcase_add_test(tc_tetris, input_left);
  tcase_add_test(tc_tetris, input_right);
  tcase_add_test(tc_tetris, consume_2);
  tcase_add_test(tc_tetris, input_down);
  tcase_add_test(tc_tetris, can_rotate_1);
  tcase_add_test(tc_tetris, rotate_1);
  tcase_add_test(tc_tetris, input_action);
  tcase_add_test(tc_tetris, update_state);
  tcase_add_test(tc_tetris, consume_3);
  tcase_add_test(tc_tetris, consume_4);
  tcase_add_test(tc_tetris, consume_5);
  tcase_add_test(tc_tetris, consume_6);
  tcase_add_test(tc_tetris, input_terminate);
  tcase_add_test(tc_tetris, right_2);
  tcase_add_test(tc_tetris, attaching_1);
  tcase_add_test(tc_tetris, attaching_2);
  tcase_add_test(tc_tetris, attaching_3);
  return suite;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  int nf = 0;

  s = tetris_suite();
  sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}