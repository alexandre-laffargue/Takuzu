#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "game_tools.h"

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_game_load() {
  game g = game_new_empty_ext(8, 6, false, false);
  game_play_move(g, 0, 1, S_ONE);
  game_play_move(g, 7, 2, S_ONE);
  game_play_move(g, 6, 5, S_ONE);
  game_play_move(g, 2, 0, S_ONE);
  game_play_move(g, 4, 4, S_ONE);
  game_save(g, "save.txt");
  game save = game_load("save.txt");
  if (!game_equal(g, save)) {
    game_delete(g);
    game_delete(save);
    remove("save.txt");
    return false;
  }
  game_delete(g);
  game_delete(save);
  remove("save.txt");
  return true;
}

bool test_game_save() {
  game g = game_default();
  game_set_square(g, 0, 0, S_ZERO);
  game_set_square(g, 5, 4, S_ONE);

  game_save(g, "testdefault.txt");

  FILE *f = fopen("testdefault.txt", "r");
  int rows, cols, wrapping, unique;
  int rFscanf = fscanf(f, " %d %d %d %d", &rows, &cols, &wrapping, &unique);
  rFscanf++;
  if (rows != game_nb_rows(g) || cols != game_nb_cols(g) ||
      wrapping != game_is_wrapping(g) || unique != game_is_unique(g)) {
    game_delete(g);
    fclose(f);
    remove("testdefault.txt");
    return false;
  }
  fgetc(f);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int code = fgetc(f);
      square sq;
      if (code == 119)
        sq = S_ZERO;
      else if (code == 98)
        sq = S_ONE;
      else if (code == 87)
        sq = S_IMMUTABLE_ZERO;
      else if (code == 66)
        sq = S_IMMUTABLE_ONE;
      else if (code == 101)
        sq = S_EMPTY;
      else {
        game_delete(g);
        fclose(f);
        remove("testdefault.txt");
        return false;
      }

      if (game_get_square(g, i, j) != sq) {
        game_delete(g);
        fclose(f);
        remove("testdefault.txt");
        return false;
      }
    }
    fgetc(f);
  }
  game_delete(g);
  fclose(f);
  return true;
}

bool test_game_nb_solutions() {
  game g = game_load("../ressources/4x4_2.txt");
  if (game_nb_solutions(g) != 2) {
    game_delete(g);
    return false;
  }
  game g2 = game_load("../ressources/4x4.txt");
  if (game_nb_solutions(g2) != 90) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  game_delete(g);
  game_delete(g2);
  return true;
}

bool test_game_solve() {
  game over = game_default_solution();
  bool a = game_solve(over);
  if (a != true) {
    game_delete(over);
    return false;
  }
  game g = game_default();
  if (game_solve(g) != true) {
    game_delete(over);
    game_delete(g);
    return false;
  }
  game_delete(over);
  game_delete(g);
  return true;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    usage(argc, argv);
  }
  fprintf(stderr, "-> Start test \"%s\"\n", argv[1]);
  bool tmp = false;

  if (strcmp("game_load", argv[1]) == 0)
    tmp = test_game_load();
  else if (strcmp("game_save", argv[1]) == 0)
    tmp = test_game_save();
  else if (strcmp("game_nb_solutions", argv[1]) == 0)
    tmp = test_game_nb_solutions();
  else if (strcmp("game_solve", argv[1]) == 0)
    tmp = test_game_solve();

  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (tmp == true) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}