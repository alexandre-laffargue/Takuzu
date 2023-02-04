#include "game_tools.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_ext.h"
#include "game_struct.h"

game game_load(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printf("Error: cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  int rows, cols, wrapping, unique;

  fscanf(f, " %d %d %d %d", &rows, &cols, &wrapping, &unique);
  game g = game_new_empty_ext(rows, cols, wrapping, unique);

  fgetc(f);
  int i = 0;
  while (!feof(f) && i < rows) {
    for (int j = 0; j < cols; j++) {
      int c = fgetc(f);
      if (c == 119) {  // 119 = w en ASCII
        game_set_square(g, i, j, S_ZERO);
      } else if (c == 98) {  // 98 = b en ASCII
        game_set_square(g, i, j, S_ONE);
      } else if (c == 87) {  // 87 = W en ASCII
        game_set_square(g, i, j, S_IMMUTABLE_ZERO);
      } else if (c == 66) {  // 66 = B en ASCII
        game_set_square(g, i, j, S_IMMUTABLE_ONE);
      }
    }
    fgetc(f);
    i++;
  }
  return g;
}

void game_save(cgame g, char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    printf("Error: cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  char *c;
  fprintf(f, "%d %d %d %d\n", game_nb_rows(g), game_nb_cols(g),
          game_is_wrapping(g), game_is_unique(g));
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++) {
      square sq = game_get_square(g, i, j);
      if (sq == S_EMPTY) {
        c = "e";
      }
      if (sq == S_IMMUTABLE_ONE) {
        c = "B";
      }
      if (sq == S_IMMUTABLE_ZERO) {
        c = "W";
      }
      if (sq == S_ONE) {
        c = "b";
      }
      if (sq == S_ZERO) {
        c = "w";
      }

      fprintf(f, "%s", c);
    }
    fprintf(f, "\n");
  }
  fclose(f);
}
