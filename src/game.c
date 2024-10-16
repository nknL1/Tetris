#include "game.h"

int main() {
  WIN_INIT(500);
  srand(time(NULL));
  first_init_state();
  render(updateCurrentState());

  while (1) {
    State_t *state = get_current_state();
    timeout(500 - 50 * state->level);
    if (state->status == Initial) {
      Input_User_Action();
    } else if (state->status == Spawn) {
      spawn_figures();
    } else if (state->status == Moving) {
      check_input_for_moving();
    } else if (state->status == Shifting && state->pause != Yes_P) {
      shifting();
    } else if (state->status == Shifting && state->pause == Yes_P) {
      check_input_for_moving();
    } else if (state->status == Attaching) {
      attaching();
    } else if (state->status == GameOver) {
      finish_game();
      first_init_state();
    }
    render(updateCurrentState());
  }
  getch();
  endwin();
  return 0;
}

void Input_User_Action() {
  int ch = getch();
  if (ch == START_BUTTON) {
    userInput(Start);
  } else if (ch == KEY_DOWN) {
    userInput(Down);
  } else if (ch == KEY_RIGHT) {
    userInput(Right);
  } else if (ch == KEY_LEFT) {
    userInput(Left);
  } else if (ch == ACTION_BUTTON) {
    userInput(Action);
  } else if (ch == PAUSE_BUTTON) {
    userInput(Pause);
  } else if (ch == TERMINATE_BUTTON) {
    userInput(Terminate);
    terminate_game();
  }
}

void check_input_for_moving() {
  State_t *state = get_current_state();
  Input_User_Action();
  state->status = Shifting;
}
