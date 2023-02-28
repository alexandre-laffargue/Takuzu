#include "game_tools.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_aux.h"
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
  fclose(f);
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

bool game_build_solution(game g, int i, int j) {
  if (game_is_over(g)) {
    // game_print(g);
    return true;
  }
  bool retour1;
  bool retour2;

  while (game_get_square(g, i, j) == S_IMMUTABLE_ONE ||
         game_get_square(g, i, j) == S_IMMUTABLE_ZERO) {
    if ((uint)(j + 1) < game_nb_cols(g)) {
      j++;
    } else if (((uint)(j + 1) == game_nb_cols(g)) &&
               ((uint)(i + 1) < game_nb_rows(g))) {
      i++;
      j = 0;
    } else {
      return false;
    }
  }

  if ((uint)(j + 1) < game_nb_cols(g)) {
    game_set_square(g, i, j, S_ONE);
    retour1 = game_build_solution(g, i, j + 1);
    if (!retour1) {
      game_set_square(g, i, j, S_ZERO);
      retour2 = game_build_solution(g, i, j + 1);
    }
  } else if (((uint)(j + 1) == game_nb_cols(g)) &&
             ((uint)(i + 1) < game_nb_rows(g))) {
    game_set_square(g, i, j, S_ONE);
    retour1 = game_build_solution(g, i + 1, 0);
    if (!retour1) {
      game_set_square(g, i, j, S_ZERO);
      retour2 = game_build_solution(g, i + 1, 0);
    }
  } else if (((uint)(j + 1) == game_nb_cols(g)) &&
             ((uint)(i + 1) == game_nb_rows(g))) {
    game_set_square(g, i, j, S_ONE);
    if (game_is_over(g)) {
      retour1 = true;
      // game_print(g);
    }
    if (!retour1) {
      game_set_square(g, i, j, S_ZERO);
      if (game_is_over(g)) {
        retour2 = true;
        // game_print(g);
      }
    }
  } else {
    return false;
  }
  return retour1 || retour2;
}

bool game_solve(game g) {
  if (game_is_over(g)) return true;

  int i = 0;
  int j = 0;

  bool ret = game_build_solution(g, i, j);
  if (ret)
    printf("Il y a une ou plusieurs solutions.\n");
  else
    printf("Il n'y a pas de solution.\n");
  return ret;
}

uint game_build_nb(game g, int i, int j) {
  if (game_is_over(g)) {
    //game_print(g);
    return (uint)1;
  }
  uint rt1 = 0;
  uint rt2 = 0;

  while (game_get_square(g, i, j) == S_IMMUTABLE_ONE ||
      game_get_square(g, i, j) == S_IMMUTABLE_ZERO) {
    if ((uint)(j + 1) < game_nb_cols(g)) {
      j++;
    } else if (((uint)(j + 1) == game_nb_cols(g)) &&
               ((uint)(i + 1) < game_nb_rows(g))) {
      i++;
      j = 0;
    } else {
      return false;
    }
  }

  if ((uint)(j + 1) < game_nb_cols(g)) {
    game_set_square(g, i, j, S_ONE);
    rt1 = game_build_nb(g, i, j + 1);
    game_set_square(g, i, j, S_ZERO);
    rt2 = game_build_nb(g, i, j + 1);
  } else if (((uint)(j + 1) == game_nb_cols(g)) &&
             ((i + 1) < game_nb_rows(g))) {
    game_set_square(g, i, j, S_ONE);
    rt1 = game_build_nb(g, i + 1, 0);
    game_set_square(g, i, j, S_ZERO);
    rt2 = game_build_nb(g, i + 1, 0);
  } else if (((uint)(j + 1) == game_nb_cols(g)) &&
             ((i + 1) == game_nb_rows(g))) {
    game_set_square(g, i, j, S_ONE);
    if (game_is_over(g)) {
      rt1 = (uint)1;
      //game_print(g);
    }
    game_set_square(g, i, j, S_ZERO);
    if (game_is_over(g)) {
      rt2 = (uint)1;
      //game_print(g);
    }
  } else {
    return (uint)0;
  }
  return rt1 + rt2;
}

uint game_nb_solutions(cgame g) {
  int i = 0;
  int j = 0;
  game gs = game_copy(g);

  uint ret = game_build_nb(gs, i, j);
  game_delete(gs);
  printf("Il y a %d solution(s).\n", ret);
  return ret;
}