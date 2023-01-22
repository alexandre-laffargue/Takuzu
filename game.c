#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"

void* memory_alloc(uint size) {
  void* tmp = malloc(size);
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation failed \n");
    exit(EXIT_FAILURE);
  } else {
    return tmp;
  }
}

void game_is_null(cgame g, char* s) {
  if (g == NULL) {
    printf("%s: g is NULL\n", s);
    exit(EXIT_FAILURE);
  }
}

game game_new(square* squares) {
  if (squares == NULL) {
    printf("Error: squares is NULL \n");
    exit(EXIT_FAILURE);
  }
  game g = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, squares, false, false);
  return g;
}

game game_new_empty(void) {
  game g = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  return g;
}

game game_copy(cgame g) {
  game_is_null(g, "game_copy");
  game copy = game_new_empty_ext(game_nb_rows(g), game_nb_cols(g),
                                 game_is_wrapping(g), game_is_unique(g));
  for (int i = 0; i < game_nb_rows(copy); i++) {
    for (int j = 0; j < game_nb_cols(copy); j++) {
      game_set_square(copy, i, j, game_get_square(g, i, j));
    }
  }

  return copy;
}

bool game_equal(cgame g1, cgame g2) {
  game_is_null(g1, "game_equal");
  game_is_null(g2, "game_equal");
  if ((game_nb_rows(g1) != game_nb_rows(g2)) ||
      (game_nb_cols(g1) != game_nb_cols(g2)) ||
      (game_is_unique(g1) != game_is_unique(g2)) ||
      (game_is_wrapping(g1) != game_is_wrapping(g2))) {
    return false;
  }
  for (int i = 0; i < game_nb_rows(g1); i++) {
    for (int j = 0; j < game_nb_cols(g1); j++) {
      if (game_get_square(g1, i, j) != game_get_square(g2, i, j)) {
        return false;
      }
    }
  }
  return true;
}

void game_delete(game g) {
  if (g != NULL) {
    if (g->square_array != NULL) {
      free(g->square_array);
    }
    if (g->history != NULL) {
      queue_free_full(g->history, free);
    }
    if (g->cancelation != NULL) {
      queue_free_full(g->cancelation, free);
    }
    free(g);
  }
}

void game_set_square(game g, uint i, uint j, square s) {
  game_is_null(g, "game_set_square");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g) ||
      (s != S_EMPTY && s != S_IMMUTABLE_ONE && s != S_IMMUTABLE_ZERO &&
       s != S_ONE && s != S_ZERO)) {
    printf(
        "game_set_square: i or j is out of range or s is not a "
        "square, params : %d %d %d %d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g), s);
    exit(EXIT_FAILURE);
  }
  uint index = (i * game_nb_cols(g)) + j;
  g->square_array[index] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  game_is_null(g, "game_get_square");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
    printf(
        "game_get_square: i or j is out of range, params : %d %d "
        "%d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g));
    exit(EXIT_FAILURE);
  }
  uint index = (i * game_nb_cols(g)) + j;
  return g->square_array[index];
}

int game_get_number(cgame g, uint i, uint j) {
  game_is_null(g, "game_get_number");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
    printf(
        "game_get_number: i or j is out of range, params : %d %d "
        "%d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g));
    exit(EXIT_FAILURE);
  }
  square sq = game_get_square(g, i, j);
  if (sq == S_ZERO || sq == S_IMMUTABLE_ZERO) {
    return 0;
  } else if (sq == S_ONE || sq == S_IMMUTABLE_ONE) {
    return 1;
  } else
    return -1;
}
int get_next_square_nowrapping(cgame g, uint i, uint j, direction dir,
                               uint dist) {
  if (dir == UP) {
    int ni = i - dist;
    if (ni >= 0 && ni < game_nb_rows(g)) {
      square sq = game_get_square(g, ni, j);
      return sq;
    } else {
      return -1;
    }
  } else if (dir == DOWN) {
    int ni = i + dist;
    if (ni >= 0 && ni < game_nb_rows(g)) {
      square sq = game_get_square(g, ni, j);
      return sq;
    } else {
      return -1;
    }
  } else if (dir == LEFT) {
    int nj = j - dist;
    if (nj >= 0 && nj < game_nb_cols(g)) {
      square sq = game_get_square(g, i, nj);
      return sq;
    } else {
      return -1;
    }
  } else if (dir == RIGHT) {
    int nj = j + dist;
    if (nj >= 0 && nj < game_nb_cols(g)) {
      square sq = game_get_square(g, i, nj);
      return sq;
    } else {
      return -1;
    }
  }
  exit(EXIT_FAILURE);
}

int get_next_square_wrapping(cgame g, uint i, uint j, direction dir,
                             uint dist) {
  if (dir == UP) {
    int ni = (i - dist);
    if (ni < 0) {
      ni += game_nb_rows(g);
    }
    square sq = game_get_square(g, ni, j);
    return sq;
  } else if (dir == DOWN) {
    int ni = (i + dist);
    if (ni >= game_nb_rows(g)) {
      ni -= game_nb_rows(g);
    }
    square sq = game_get_square(g, ni, j);
    return sq;
  } else if (dir == LEFT) {
    int nj = (j - dist);
    if (nj < 0) {
      nj += game_nb_cols(g);
    }
    square sq = game_get_square(g, i, nj);
    return sq;
  } else if (dir == RIGHT) {
    int nj = (j + dist);
    if (nj >= game_nb_cols(g)) {
      nj -= game_nb_cols(g);
    }
    square sq = game_get_square(g, i, nj);
    return sq;
  }
  exit(EXIT_FAILURE);
}

int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist) {
  game_is_null(g, "game_get_next_square");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g) || dist > 2) {
    printf(
        "game_get_next_square: i or j is out of range or dist is "
        "greater than 2, params : %d %d %d %d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g), dist);
    exit(EXIT_FAILURE);
  }
  if (!game_is_wrapping(g)) {
    return get_next_square_nowrapping(g, i, j, dir, dist);
  } else {
    return get_next_square_wrapping(g, i, j, dir, dist);
  }
  exit(EXIT_FAILURE);
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
  game_is_null(g, "game_get_next_number");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g) || dist > 2) {
    printf(
        "game_get_next_number: i or j is out of range or dist is "
        "greater than 2, params : %d %d %d %d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g), dist);
    exit(EXIT_FAILURE);
  }
  int sq = game_get_next_square(g, i, j, dir, dist);
  if (sq == -1) {
    return -1;
  }
  if (sq == S_ZERO || sq == S_IMMUTABLE_ZERO) {
    return 0;
  } else if (sq == S_ONE || sq == S_IMMUTABLE_ONE) {
    return 1;
  } else
    return -1;
}

bool game_is_empty(cgame g, uint i, uint j) {
  game_is_null(g, "game_is_empty");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
    printf(
        "game_is_empty: i or j is out of range, params : %d %d %d "
        "%d\n",
        i, j, game_nb_rows(g), game_nb_cols(g));
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) != S_EMPTY) {
    return false;
  }
  return true;
}

bool game_is_immutable(cgame g, uint i, uint j) {
  game_is_null(g, "game_is_immutable");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
    printf(
        "game_is_immutable: i or j is out of range, params : %d "
        "%d %d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g));
    exit(EXIT_FAILURE);
  }
  square sq = game_get_square(g, i, j);
  if (sq == S_IMMUTABLE_ONE || sq == S_IMMUTABLE_ZERO) {
    return true;
  } else {
    return false;
  }
}

bool error_unique_rows(cgame g, uint i, uint j) {
  int tab[game_nb_cols(g)];
  for (uint k = 0; k < game_nb_cols(g);
       k++) {  // parcours la ligne et met les valeurs dans un tableau
    tab[k] = game_get_number(g, i, k);
  }
  int cptlmemenombre;
  for (uint x = 0; x < game_nb_rows(g); x++) {  // parcours les lignes
    cptlmemenombre = 0;
    for (uint y = 0; y < game_nb_cols(g); y++) {  // parcours les colonnes
      if (x == i) {  // si sur la meme ligne que la case testé on passe a la
                     // suivante
        break;
      }
      if (game_get_number(g, x, y) !=
          tab[y]) {  // si la valeur de la case testé est differente de
                     // celle du tableau
        break;       // on passe a la ligne suivante
      }
      cptlmemenombre++;
    }
    if (cptlmemenombre == game_nb_cols(g)) {
      return false;
    }
  }
  return true;
}

bool error_unique_cols(cgame g, uint i, uint j) {
  int tab[game_nb_rows(g)];
  for (uint k = 0; k < game_nb_rows(g);
       k++) {  // parcours la colonne et met les valeurs dans un tableau
    tab[k] = game_get_number(g, k, j);
  }
  int cptcmemenombre;
  for (uint x = 0; x < game_nb_cols(g); x++) {  // parcours les colonnes
    cptcmemenombre = 0;
    for (uint y = 0; y < game_nb_rows(g); y++) {  // parcours les lignes
      if (x == j) {  // si sur la meme colonne que la case testé on passe a
                     // la suivante
        break;
      }
      if (game_get_number(g, y, x) !=
          tab[y]) {  // si la valeur de la case testé est differente de
                     // celle du tableau
        break;       // on passe a la colonne suivante
      }
      cptcmemenombre++;
    }
    if (cptcmemenombre == game_nb_rows(g)) {
      return false;
    }
  }
  return true;
}

bool error_unique(cgame g, uint i, uint j) {
  bool testligne = true;
  bool testcolonne = true;
  for (uint k = 0; k < game_nb_cols(g);
       k++) {  // regarde si il y a une case vide dans la ligne
    if (game_get_square(g, i, k) == S_EMPTY) {
      testligne = false;
      break;
    }
  }
  for (uint k = 0; k < game_nb_rows(g);
       k++) {  // regarde si il y a une case vide dans la colonne
    if (game_get_square(g, k, j) == S_EMPTY) {
      testcolonne = false;
      break;
    }
  }
  if (testligne) {
    if (!error_unique_rows(g, i, j)) {
      return false;
    }
  }
  if (testcolonne) {
    if (!error_unique_cols(g, i, j)) {
      return false;
    }
  }
  return true;
}

bool error_3samecolor(cgame g, uint i, uint j) {
  int cpt_ver = 1, cpt_hor = 1;
  /* horizontal*/
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, RIGHT, 1)) {
    cpt_hor++;
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, RIGHT, 2)) {
      return false;
    }
  }
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, LEFT, 1)) {
    cpt_hor++;
    if (cpt_hor > 2) {
      return false;
    }
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, LEFT, 2)) {
      return false;
    }
  }
  /* vertical*/
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, UP, 1)) {
    cpt_ver++;
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, UP, 2)) {
      return false;
    }
  }
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, DOWN, 1)) {
    cpt_ver++;
    if (cpt_ver > 2) {
      return false;
    }
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, DOWN, 2)) {
      return false;
    }
  }
  return true;
}

bool error_more_half_color(cgame g, uint i, uint j) {
  int cpt_memecouleur_surC = 0,
      cpt_memecouleur_surL = 0;  // début du test de la moitié d'une couleur
  for (uint k = 0; k < game_nb_rows(g); k++) {
    if (game_get_number(g, k, j) == game_get_number(g, i, j)) {
      cpt_memecouleur_surL++;
    }
  }
  for (uint k = 0; k < game_nb_cols(g); k++) {
    if (game_get_number(g, i, k) == game_get_number(g, i, j)) {
      cpt_memecouleur_surC++;
    }
  }
  if (cpt_memecouleur_surL > (game_nb_rows(g) / 2) ||
      cpt_memecouleur_surC > (game_nb_cols(g) / 2)) {
    return false;
  }
  return true;
}

int game_has_error(cgame g, uint i, uint j) {
  game_is_null(g, "game_has_error");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
    printf(
        "game_has_error: i or j is out of range, params : %d %d "
        "%d %d\n",
        i, j, game_nb_rows(g), game_nb_cols(g));
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) == S_EMPTY) {
    return 0;
  }
  if (!error_3samecolor(g, i, j)) {
    return -1;
  }
  if (!error_more_half_color(g, i, j)) {
    return -1;
  }
  if (game_is_unique(g)) {
    if (!error_unique(g, i, j)) {
      return -1;
    }
  }
  return 0;
}

bool game_check_move(cgame g, uint i, uint j, square s) {
  game_is_null(g, "game_check_move");
  if (s == S_IMMUTABLE_ONE || s == S_IMMUTABLE_ZERO || i >= game_nb_rows(g) ||
      j >= game_nb_cols(g)) {
    return false;
  }
  square sq = game_get_square(g, i, j);
  if (sq != S_IMMUTABLE_ONE && sq != S_IMMUTABLE_ZERO) {
    return true;
  } else {
    return false;
  }
}

void game_play_move(game g, uint i, uint j, square s) {
  game_is_null(g, "game_play_move");
  if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
    printf(
        "game_play_move: i or j is out of range, params : "
        " %d, %d, %d\n",
        i, j, s);
    exit(EXIT_FAILURE);
  }
  if (s == S_IMMUTABLE_ONE || s == S_IMMUTABLE_ZERO) {
    printf("game_play_move: square is immutable\n");
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
      game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
    game_set_square(g, i, j, s);
    int* tab = memory_alloc(3 * sizeof(int));
    tab[0] = i;
    tab[1] = j;
    tab[2] = s;
    queue_push_head(g->history, tab);
    queue_clear_full(g->cancelation, free);
  }
}

bool game_is_over(cgame g) {
  game_is_null(g, "game_is_over");
  for (uint k = 0; k < game_nb_rows(g); k++) {
    for (uint l = 0; l < game_nb_cols(g); l++) {
      if (game_has_error(g, k, l) != 0) {
        return false;
      }
      if (game_get_square(g, k, l) == S_EMPTY) {
        return false;
      }
    }
  }
  return true;
}

void game_restart(game g) {
  game_is_null(g, "game_restart");
  for (uint i = 0; i < game_nb_rows(g); i++) {
    for (uint j = 0; j < game_nb_cols(g); j++) {
      if (game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
          game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
        game_set_square(g, i, j, S_EMPTY);
      }
    }
  }
  queue_clear_full(g->history, free);
  queue_clear_full(g->cancelation, free);
}
