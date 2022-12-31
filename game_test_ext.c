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

bool test_game_is_wrapping() {
  game g1 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  game g2 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, true, false);
  bool test = !game_is_wrapping(g1) && game_is_wrapping(g2);
  game_delete(g1);
  game_delete(g2);
  return test;
}

bool test_game_is_unique(){
  game g = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, true);

  if(game_is_unique(g) != g->unique){
    game_delete(g);
    return false;
  }
  g->unique = false;

  if(game_is_unique(g) != g->unique){
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_new_empty_ext(){
  game g = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, true, true);
  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j <= 5; j++) {
      square tmp = game_get_square(g, i, j);
      if (tmp != S_EMPTY) {
        game_delete(g);
        return false;
      }
    }
  }
  if(g->unique != game_is_unique(g) || g->wrapping != game_is_wrapping(g)){
    game_delete(g);
    return false;
  }
  if(g->nb_cols != DEFAULT_SIZE || g->nb_rows != DEFAULT_SIZE){
    game_delete(g);
    return false;
  }
  if(g->annulation == NULL || g->historique == NULL){
      game_delete(g);
      return false;
    }
  game_delete(g);
  return true;

}

bool test_game_new_ext(){
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));

  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  game g = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, square_array,true ,true);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; i < 6; i++) {
      if (game_get_square(g, i, j) != S_ZERO &&
          game_get_square(g, i, j) != S_EMPTY &&
          game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
          game_get_square(g, i, j) != S_IMMUTABLE_ZERO &&
          game_get_square(g, i, j) != S_ONE) {
        game_delete(g);
        free(square_array);
        return false;
      }
    }
  }
  if(g->unique != game_is_unique(g) || g->wrapping != game_is_wrapping(g)){
    game_delete(g);
    free(square_array);
    return false;
  }
  if(g->nb_cols != DEFAULT_SIZE || g->nb_rows != DEFAULT_SIZE){
    game_delete(g);
    free(square_array);
    return false;
  }
  if(g->annulation == NULL || g->historique == NULL){
      game_delete(g);
      free(square_array);
      return false;
    }
  
  game_delete(g);
  free(square_array);
  return true;
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
  else if (strcmp("game_is_wrapping", argv[1]) == 0)
    ok = test_game_is_wrapping();
  else if (strcmp("game_new_empty_ext", argv[1]) == 0)
    ok = test_game_new_empty_ext();
  else if (strcmp("game_new_ext", argv[1]) == 0)
    ok = test_game_new_ext();
  else if (strcmp("game_is_unique", argv[1]) == 0)
    ok = test_game_is_unique();

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