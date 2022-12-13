#include "game_aux.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_ext.h"
#include "game_struct.h"

void game_print(cgame g) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  printf("   ");
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    printf("%d", i);
  }
  printf("\n   ");
  for (int j = 0; j < DEFAULT_SIZE; j++) {
    printf("-");
  }
  printf("\n");
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    printf("%d |", i);
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g, i, j) == S_EMPTY) {
        printf(" ");
      }
      if (game_get_square(g, i, j) == S_ZERO) {
        printf("w");
      }
      if (game_get_square(g, i, j) == S_ONE) {
        printf("b");
      }
      if (game_get_square(g, i, j) == S_IMMUTABLE_ZERO) {
        printf("W");
      }
      if (game_get_square(g, i, j) == S_IMMUTABLE_ONE) {
        printf("B");
      }
    }
    printf("|\n");
  }
  printf("   ");
  for (int j = 0; j < DEFAULT_SIZE; j++) {
    printf("-");
  }
  printf("\n");
}

game game_default(void) {
  square* sq = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));
  ;

  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    sq[i] = S_EMPTY;
  }
  sq[1] = S_IMMUTABLE_ONE;
  sq[2] = S_IMMUTABLE_ZERO;
  sq[13] = S_IMMUTABLE_ZERO;
  sq[16] = S_IMMUTABLE_ZERO;
  sq[19] = S_IMMUTABLE_ZERO;
  sq[20] = S_IMMUTABLE_ONE;
  sq[26] = S_IMMUTABLE_ONE;
  sq[29] = S_IMMUTABLE_ZERO;
  sq[35] = S_IMMUTABLE_ZERO;
  game def = game_new(sq);
  free(sq);
  return def;
}

game game_default_solution(void) {
  game g = game_default();
  game_set_square(g, 0, 0, S_ZERO);
  game_set_square(g, 0, 3, S_ONE);
  game_set_square(g, 0, 4, S_ZERO);
  game_set_square(g, 0, 5, S_ONE);

  game_set_square(g, 1, 0, S_ZERO);
  game_set_square(g, 1, 1, S_ONE);
  game_set_square(g, 1, 2, S_ONE);
  game_set_square(g, 1, 3, S_ZERO);
  game_set_square(g, 1, 4, S_ONE);
  game_set_square(g, 1, 5, S_ZERO);

  game_set_square(g, 2, 0, S_ONE);
  game_set_square(g, 2, 2, S_ZERO);
  game_set_square(g, 2, 3, S_ONE);
  game_set_square(g, 2, 5, S_ONE);

  game_set_square(g, 3, 0, S_ONE);
  game_set_square(g, 3, 3, S_ZERO);
  game_set_square(g, 3, 4, S_ZERO);
  game_set_square(g, 3, 5, S_ONE);

  game_set_square(g, 4, 0, S_ZERO);
  game_set_square(g, 4, 1, S_ONE);
  game_set_square(g, 4, 3, S_ZERO);
  game_set_square(g, 4, 4, S_ONE);

  game_set_square(g, 5, 0, S_ONE);
  game_set_square(g, 5, 1, S_ZERO);
  game_set_square(g, 5, 2, S_ZERO);
  game_set_square(g, 5, 3, S_ONE);
  game_set_square(g, 5, 4, S_ONE);

  return g;
}