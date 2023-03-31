#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "game_tools.h"

void game_help_print() {
  printf("- press 'w <i> <j>' to put a zero/white at square (i,j)\n");
  printf("- press 'b <i> <j>' to put a one/black at square (i,j)\n");
  printf("- press 'e <i> <j>' to empty square (i,j)\n");
  printf("- press 'r' to restart\n");
  printf("- press 'z' to undo\n");
  printf("- press 'y' to redo\n");
  printf("- press 's' <filename> to save\n");
  printf("- press 'c' to solve\n");
  printf("- press 'q' to quit\n");
}
void game_errors_print(game g) {
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++)
      if (game_has_error(g, i, j)) {
        printf("Error at square (%d,%d)\n", i, j);
      }
  }
}

int main(int argc, char const *argv[]) {
  int scan, b = 0;
  char c;
  game g;
  if (argc == 2) {
    char *filename = (char *)argv[1];
    g = game_load(filename);
  } else {
    g = game_default();
  }
  while (!game_is_over(g)) {
    game_print(g);
    game_errors_print(g);
    printf("> ?[h for help]\n");
    scan = scanf(" %c", &c);
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
      case 'z':
        printf("> action: undo\n");
        game_undo(g);
        break;
      case 'y':
        printf("> action: redo\n");
        game_redo(g);
        break;
      case 'c':
        game_solve(g);
        break;
    }
    if ((c == 'w') || (c == 'b') || (c == 'e')) {
      int i, j;
      scan = scanf(" %d %d", &i, &j);
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
    if (c == 's') {
      char name[4095];
      scan = scanf(" %s", name);
      printf("> action: game save 's' into %s\n", name);
      game_save(g, name);
    }

  }
  game_print(g);
  printf("congratulation\n");
  game_delete(g);
  b += scan;
  return EXIT_SUCCESS;
}