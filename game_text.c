#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
void game_help_print() {
  printf("- press 'w <i> <j>' to put a zero/white at square (i,j)\n");
  printf("- press 'b <i> <j>' to put a one/black at square (i,j)\n");
  printf("- press 'e <i> <j>' to empty square (i,j)\n");
  printf("- press 'r' to restart\n");
  printf("- press 'q' to quit\n");
}
void game_errors_print(game g) {
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++)
      if (game_has_error(g, i, j)) {
        printf("Error at square (%d,%d)\n", i, j);
      }
  }
}

int main() {
  char c;
  int i, j;
  game g = game_default();
  while (!game_is_over(g)) {
    game_print(g);
    game_errors_print(g);
    printf("> ?[h for help]\n");
    scanf("%c", &c);
    switch (c) {
      case 'h':
        printf("> action: help\n");
        game_help_print();
        break;
      case 'r':
        printf("> action: restart\n");
        game_restart(g);
        break;
      case 'q':
        printf("> action: quit\n");
        game_delete(g);
        printf("shame\n");
        return EXIT_SUCCESS;
        break;
    }
    scanf("%d %d", &i, &j);
    if (c == 'w') {
      printf("> action: play move 'w' into square (%d,%d)\n", i, j);
      if (game_check_move(g, i, j, S_ZERO)) {
        game_play_move(g, i, j, S_ZERO);
      }
    } else if (c == 'b') {
      printf("> action: play move 'b' into square (%d,%d)\n", i, j);
      if (game_check_move(g, i, j, S_ONE)) {
        game_play_move(g, i, j, S_ONE);
      }
    } else if (c == 'e') {
      printf("> action: play move 'e' into square (%d,%d)\n", i, j);
      if (game_check_move(g, i, j, S_EMPTY)) {
        game_play_move(g, i, j, S_EMPTY);
      }
    }
  }
  game_print(g);
  printf("congratulation\n");
  game_delete(g);
  return EXIT_SUCCESS;
}