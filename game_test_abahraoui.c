#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_game_is_empty() {
  game g = game_new_empty();
  game_set_square(g, 0, 0, S_EMPTY);
  game_set_square(g, 1, 1, S_ZERO);
  game_set_square(g, 3, 4, S_ONE);
  game_set_square(g, 2, 1, S_IMMUTABLE_ONE);
  game_set_square(g, 2, 2, S_IMMUTABLE_ZERO);
  if (game_is_empty(g, 1, 1) == false && game_is_empty(g, 3, 4) == false &&
      game_is_empty(g, 2, 1) == false && game_is_empty(g, 2, 2) == false &&
      game_is_empty(g, 0, 0) == true) {
    game_delete(g);
    return true;
  } else {
    game_delete(g);
    return false;
  }
}

bool test_game_play_move() {
  game g = game_new_empty();
  game g2 = game_default();

  game_set_square(g, 0, 0, S_EMPTY);
  game_set_square(g, 1, 1, S_ZERO);
  game_set_square(g, 3, 3, S_ONE);
  game_set_square(g, 1, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 1, 3, S_IMMUTABLE_ZERO);

  game_play_move(g, 0, 0, S_ONE);
  game_play_move(g, 1, 1, S_ONE);
  game_play_move(g, 3, 3, S_EMPTY);
  game_play_move(g2, 0, 0, S_ONE);
  // game_play_move(g,1,2,S_EMPTY);
  // game_play_move(g,1,3,S_EMPTY);

  if (game_get_square(g, 0, 0) != S_ONE) {
    game_delete(g2);
    game_delete(g);
    return false;
  } else if (game_get_square(g, 1, 1) != S_ONE) {
    game_delete(g2);
    game_delete(g);
    return false;
  } else if (game_get_square(g, 3, 3) != S_EMPTY) {
    game_delete(g2);
    game_delete(g);
    return false;
  } else if (game_get_square(g2, 0, 0) != S_ONE) {
    game_delete(g2);
    game_delete(g);
    return false;
  }
  // else if(game_get_square(g,1,2)!=S_IMMUTABLE_ONE){game_delete(g);return
  // false;} else
  // if(game_get_square(g,1,3)!=S_IMMUTABLE_ZERO){game_delete(g);return false;}
  game_delete(g);
  game_delete(g2);
  return true;
}

bool test_game_has_error() {
  game g = game_new_empty();
  game_set_square(g, 0, 0, S_ONE);
  game_set_square(g, 0, 1, S_ONE);
  game_set_square(g, 0, 2, S_ONE);
  game c = game_new_empty();
  game_set_square(c, 2, 0, S_ONE);
  game_set_square(c, 1, 0, S_ONE);
  game_set_square(c, 0, 0, S_ONE);
  game d = game_new_empty();
  game_set_square(d, 0, 0, S_ZERO);
  game_set_square(d, 0, 1, S_ZERO);
  game_set_square(d, 0, 2, S_ZERO);
  game e = game_new_empty();
  game_set_square(e, 2, 0, S_ZERO);
  game_set_square(e, 1, 0, S_ZERO);
  game_set_square(e, 0, 0, S_ZERO);
  if (!game_has_error(g, 0, 0) && !game_has_error(g, 0, 1) &&
      !game_has_error(g, 0, 2) && !game_has_error(c, 0, 0) &&
      !game_has_error(c, 2, 0) && !game_has_error(c, 1, 0) &&
      !game_has_error(d, 0, 0) && !game_has_error(d, 0, 1) &&
      !game_has_error(d, 0, 2) && !game_has_error(e, 2, 0) &&
      !game_has_error(e, 1, 0) && !game_has_error(e, 0, 0)) {
    game_delete(g);
    game_delete(c);
    game_delete(d);
    game_delete(e);
    return 0;
  } else {
    game_delete(g);
    game_delete(c);
    game_delete(d);
    game_delete(e);
    return 1;
  }
}

bool test_game_restart() {
  game g = game_new_empty();
  game_set_square(g, 0, 0, S_ZERO);
  game_set_square(g, 0, 1, S_ONE);
  game_set_square(g, 2, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 3, 3, S_IMMUTABLE_ZERO);
  game_restart(g);
  if (game_get_square(g, 0, 0) == S_EMPTY &&
      game_get_square(g, 0, 1) == S_EMPTY &&
      game_get_square(g, 2, 2) == S_IMMUTABLE_ONE &&
      game_get_square(g, 3, 3) == S_IMMUTABLE_ZERO &&
      game_get_square(g, 1, 2) == S_EMPTY &&
      queue_is_empty(g->historique) == true &&
      queue_is_empty(g->annulation) == true) {
    game_delete(g);
    return true;
  } else {
    game_delete(g);
    return false;
  }
}

bool test_game_is_over() {
  game g3 = game_new_empty();
  game_set_square(g3, 0, 0, S_ZERO);
  game_set_square(g3, 0, 1, S_ZERO);
  game_set_square(g3, 0, 2, S_ZERO);
  game_set_square(g3, 0, 3, S_ONE);
  game_set_square(g3, 0, 4, S_ONE);
  game_set_square(g3, 0, 5, S_ONE);

  game_set_square(g3, 1, 0, S_ONE);
  game_set_square(g3, 1, 1, S_ZERO);
  game_set_square(g3, 1, 2, S_ZERO);
  game_set_square(g3, 1, 3, S_ZERO);
  game_set_square(g3, 1, 4, S_ONE);
  game_set_square(g3, 1, 5, S_ONE);

  game_set_square(g3, 2, 0, S_ONE);
  game_set_square(g3, 2, 1, S_ONE);
  game_set_square(g3, 2, 2, S_ZERO);
  game_set_square(g3, 2, 3, S_ZERO);
  game_set_square(g3, 2, 4, S_ZERO);
  game_set_square(g3, 2, 5, S_ONE);

  game_set_square(g3, 3, 0, S_ONE);
  game_set_square(g3, 3, 1, S_ONE);
  game_set_square(g3, 3, 2, S_ONE);
  game_set_square(g3, 3, 3, S_ZERO);
  game_set_square(g3, 3, 4, S_ZERO);
  game_set_square(g3, 3, 5, S_ZERO);

  game_set_square(g3, 4, 0, S_ZERO);
  game_set_square(g3, 4, 1, S_ONE);
  game_set_square(g3, 4, 2, S_ONE);
  game_set_square(g3, 4, 3, S_ONE);
  game_set_square(g3, 4, 4, S_ZERO);
  game_set_square(g3, 4, 5, S_ZERO);

  game_set_square(g3, 5, 0, S_ZERO);
  game_set_square(g3, 5, 1, S_ZERO);
  game_set_square(g3, 5, 2, S_ONE);
  game_set_square(g3, 5, 3, S_ONE);
  game_set_square(g3, 5, 4, S_ONE);
  game_set_square(g3, 5, 5, S_ZERO);
  game over = game_default_solution();
  game unmodified = game_default();
  game error = game_default_solution();
  game_play_move(error, 3, 4, S_ONE);
  bool test = (!(game_is_over(unmodified)) && (game_is_over(over)) &&
               !(game_is_over(error)) && !(game_is_over(g3)));

  game_delete(over);
  game_delete(unmodified);
  game_delete(error);
  game_delete(g3);
  return test;
}

bool test_game_check_move() {
  game g = game_new_empty();

  game_set_square(g, 0, 3, S_IMMUTABLE_ONE);
  bool test_immutable = (!(game_check_move(g, 0, 3, S_EMPTY)) &&
                         !(game_check_move(g, 0, 3, S_ONE)) &&
                         !(game_check_move(g, 0, 3, S_ZERO)));

  game_set_square(g, 0, 3, S_IMMUTABLE_ZERO);
  bool test_immutable0 = (!(game_check_move(g, 0, 3, S_EMPTY)) &&
                          !(game_check_move(g, 0, 3, S_ONE)) &&
                          !(game_check_move(g, 0, 3, S_ZERO)));

  game_set_square(g, 0, 3, S_EMPTY);
  bool empty =
      ((game_check_move(g, 0, 3, S_EMPTY)) &&
       (game_check_move(g, 0, 3, S_ONE)) && (game_check_move(g, 0, 3, S_ZERO)));

  game_set_square(g, 0, 4, S_ZERO);
  bool zero = ((game_check_move(g, 0, 4, S_ONE)) &&
               (game_check_move(g, 0, 4, S_ZERO)) &&
               (game_check_move(g, 0, 4, S_EMPTY)));

  game_set_square(g, 0, 5, S_ONE);
  bool one = ((game_check_move(g, 0, 5, S_ONE)) &&
              (game_check_move(g, 0, 5, S_ZERO)) &&
              (game_check_move(g, 0, 5, S_EMPTY)));

  game_delete(g);
  return (test_immutable && test_immutable0 && empty && zero && one);
}

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_is_empty", argv[1]) == 0)
    ok = test_game_is_empty();
  else if (strcmp("game_play_move", argv[1]) == 0)
    ok = test_game_play_move();
  else if (strcmp("game_has_error", argv[1]) == 0)
    ok = test_game_has_error();
  else if (strcmp("game_restart", argv[1]) == 0)
    ok = test_game_restart();
  else if (strcmp("game_check_move", argv[1]) == 0)
    ok = test_game_check_move();
  else if (strcmp("game_is_over", argv[1]) == 0)
    ok = test_game_is_over();

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
