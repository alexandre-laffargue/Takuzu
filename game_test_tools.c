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

int main(int argc, char *argv[]) {
  if (argc == 1) {
    usage(argc, argv);
  }
  fprintf(stderr, "-> Start test \"%s\"\n", argv[1]);
  bool tmp = false;

  if (strcmp("game_load", argv[1]) == 0) {
    tmp = test_game_load();

  } else {
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