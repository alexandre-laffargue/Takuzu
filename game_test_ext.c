#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"



void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_game_nb_rows() {
  game g = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  bool test1 = (DEFAULT_SIZE == game_nb_rows(g));
  game_delete(g);

  g = game_new_empty_ext(3, 2, false, false);
  bool test2 = (3 == game_nb_rows(g));
  game_delete(g);

  return (test1 && test2);
}

bool test_game_nb_cols() {
  game g = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  bool test1 = (DEFAULT_SIZE == game_nb_cols(g));
  game_delete(g);

  g = game_new_empty_ext(3, 2, false, false);
  bool test2 = (2 == game_nb_cols(g));
  game_delete(g);

  return (test1 && test2);
}



int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_nb_rows", argv[1]) == 0)
    ok = test_game_nb_rows();
  else if (strcmp("game_nb_cols", argv[1]) == 0)
    ok = test_game_nb_cols();

else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}