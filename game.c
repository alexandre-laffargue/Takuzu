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

game game_new(square* squares) {
  if (squares == NULL) {
    printf("Error: squares is NULL \n");
    exit(EXIT_FAILURE);
  }
  game new = memory_alloc(sizeof(struct game_s));
  new->nb_rows = DEFAULT_SIZE;
  new->nb_cols = DEFAULT_SIZE;
  new->unique = false;
  new->wrapping = false;
  square* array = memory_alloc((new->nb_rows* new->nb_cols) * sizeof(square));

  for (int i = 0; i < (new->nb_rows* new->nb_cols); i++) {
    square tmp = squares[i];
    array[i] = tmp;
  }
  new->square_array = array;
  new->historique = queue_new();
  new->annulation = queue_new();
  return new;
}

game game_new_empty(void) {
  game g = memory_alloc(sizeof(struct game_s));
  g->nb_rows = DEFAULT_SIZE;
  g->nb_cols = DEFAULT_SIZE;
  g->unique = false;
  g->wrapping = false;
  square* array = memory_alloc((g->nb_rows * g->nb_cols) * sizeof(square));

  for (int i = 0; i < g->nb_rows * g->nb_cols; i++) {
    array[i] = S_EMPTY;
  }
  g->square_array = array;
  g->historique = queue_new();
  g->annulation = queue_new();
  return g;
}

game game_copy(cgame g) {
  if (g == NULL) {
    printf("game_copy: g is NULL\n");
    exit(EXIT_FAILURE);
  }
  game copy = memory_alloc(sizeof(struct game_s));
  copy->nb_rows = g->nb_rows;
  copy->nb_cols = g->nb_cols;
  copy->unique = g->unique;
  copy->wrapping = g->wrapping;
  copy->square_array =
      memory_alloc((copy->nb_rows * copy->nb_cols) * sizeof(square));
  for (int i = 0; i < copy->nb_rows; i++) {
    for (int j = 0; j < copy->nb_cols; j++) {
      game_set_square(copy, i, j, game_get_square(g, i, j));
    }
  }
  copy->historique = queue_new();
  copy->annulation = queue_new();
  return copy;
}

bool game_equal(cgame g1, cgame g2) {
  if (g1 == NULL || g2 == NULL) {
    printf("game_equal: g1 or g2 is NULL\n");
    exit(EXIT_FAILURE);
  }
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
    if (g->historique != NULL) {
      queue_free_full(g->historique, free);
    }
    if (g->annulation != NULL) {
      queue_free_full(g->annulation, free);
    }
    free(g);
  }
}

void game_set_square(game g, uint i, uint j, square s) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols ||
      (s != S_EMPTY && s != S_IMMUTABLE_ONE && s != S_IMMUTABLE_ZERO &&
       s != S_ONE && s != S_ZERO)) {
    printf(
        "game_set_square: g is NULL or i or j is out of range or s is not a "
        "square, params : %d %d %d %d %d\n",
        i, j, g->nb_rows, g->nb_cols, s);
    exit(EXIT_FAILURE);
  }
  uint index = (i * g->nb_cols) + j;
  g->square_array[index] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    printf(
        "game_get_square: g is NULL or i or j is out of range, params : %d %d "
        "%d %d\n",
        i, j, g->nb_rows, g->nb_cols);
    exit(EXIT_FAILURE);
  }
  uint index = (i * g->nb_cols) + j;
  return g->square_array[index];
}

int game_get_number(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    printf(
        "game_get_number: g is NULL or i or j is out of range, params : %d %d "
        "%d %d\n",
        i, j, g->nb_rows, g->nb_cols);
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

int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols || dist > 2) {
    printf(
        "game_get_next_square: g is NULL or i or j is out of range or dist is "
        "greater than 2, params : %d %d %d %d %d\n",
        i, j, g->nb_rows, g->nb_cols, dist);
    exit(EXIT_FAILURE);
  }
  if (!g->wrapping) {
    if (dir == UP) {
      int ni = i - dist;
      if (ni >= 0 && ni < g->nb_rows) {
        square sq = game_get_square(g, ni, j);
        return sq;
      } else {
        return -1;
      }
    } else if (dir == DOWN) {
      int ni = i + dist;
      if (ni >= 0 && ni < g->nb_rows) {
        square sq = game_get_square(g, ni, j);
        return sq;
      } else {
        return -1;
      }
    } else if (dir == LEFT) {
      int nj = j - dist;
      if (nj >= 0 && nj < g->nb_cols) {
        square sq = game_get_square(g, i, nj);
        return sq;
      } else {
        return -1;
      }
    } else if (dir == RIGHT) {
      int nj = j + dist;
      if (nj >= 0 && nj < g->nb_cols) {
        square sq = game_get_square(g, i, nj);
        return sq;
      } else {
        return -1;
      }
    }
  } else {
    if (dir == UP) {
      int ni = (i - dist);
      if (ni < 0) {
        ni += g->nb_rows;
      }
      square sq = game_get_square(g, ni, j);
      return sq;
    } else if (dir == DOWN) {
      int ni = (i + dist);
      if (ni >= g->nb_rows) {
        ni -= g->nb_rows;
      }
      square sq = game_get_square(g, ni, j);
      return sq;
    } else if (dir == LEFT) {
      int nj = (j - dist);
      if (nj < 0) {
        nj += g->nb_cols;
      }
      square sq = game_get_square(g, i, nj);
      return sq;
    } else if (dir == RIGHT) {
      int nj = (j + dist);
      if (nj >= g->nb_cols) {
        nj -= g->nb_cols;
      }
      square sq = game_get_square(g, i, nj);
      return sq;
    }
  }
  exit(EXIT_FAILURE);
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols || dist > 2) {
    printf(
        "game_get_next_number: g is NULL or i or j is out of range or dist is "
        "greater than 2, params : %d %d %d %d %d\n",
        i, j, g->nb_rows, g->nb_cols, dist);
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
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    printf(
        "game_is_empty: g is NULL or i or j is out of range, params : %d %d %d "
        "%d\n",
        i, j, g->nb_rows, g->nb_cols);
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) != S_EMPTY) {
    return false;
  }
  return true;
}

bool game_is_immutable(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    printf(
        "game_is_immutable: g is NULL or i or j is out of range, params : %d "
        "%d %d %d\n",
        i, j, g->nb_rows, g->nb_cols);
    exit(EXIT_FAILURE);
  }
  square sq = game_get_square(g, i, j);
  if (sq == S_IMMUTABLE_ONE || sq == S_IMMUTABLE_ZERO) {
    return true;
  } else {
    return false;
  }
}

int game_has_error(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    printf(
        "game_has_error: g is NULL or i or j is out of range, params : %d %d "
        "%d %d\n",
        i, j, g->nb_rows, g->nb_cols);
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) == S_EMPTY) {
    return 0;
  }
  int cpt_ver = 1, cpt_hor = 1;  // début des test du nbr de même case à coté
  /* horizontal*/
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, RIGHT, 1)) {
    cpt_hor++;
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, RIGHT, 2)) {
      return -1;
    }
  }
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, LEFT, 1)) {
    cpt_hor++;
    if (cpt_hor > 2) {
      return -1;
    }
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, LEFT, 2)) {
      return -1;
    }
  }
  /* vertical*/
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, UP, 1)) {
    cpt_ver++;
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, UP, 2)) {
      return -1;
    }
  }
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, DOWN, 1)) {
    cpt_ver++;
    if (cpt_ver > 2) {
      return -1;
    }
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, DOWN, 2)) {
      return -1;
    }
  }
  int cpt_hor1 = 0, cpt_ver1 = 0;  // début du test de la moitié d'une couleur
  for (uint k = 0; k < g->nb_rows; k++) {
    if (game_get_number(g, k, j) == game_get_number(g, i, j)) {
      cpt_hor1++;
    }
  }
  for (uint k = 0; k < g->nb_cols; k++) {
    if (game_get_number(g, i, k) == game_get_number(g, i, j)) {
      cpt_ver1++;
    }
  }
  if (cpt_hor1 > (g->nb_rows / 2) || cpt_ver1 > (g->nb_cols / 2)) {
    return -1;
  }
  if (g->unique) {  // test de la condition unique
    bool testligne = true;
    bool testcolonne = true;
    for (uint k = 0; k < g->nb_cols;
         k++) {  // regarde si il y a une case vide dans la ligne
      if (game_get_square(g, i, k) == S_EMPTY) {
        testligne = false;
        break;
      }
    }
    for (uint k = 0; k < g->nb_rows;
         k++) {  // regarde si il y a une case vide dans la colonne
      if (game_get_square(g, k, j) == S_EMPTY) {
        testcolonne = false;
        break;
      }
    }
    if (testligne) {
      int tab[g->nb_cols];
      for (uint k = 0; k < g->nb_cols;
           k++) {  // parcours la ligne et met les valeurs dans un tableau
        tab[k] = game_get_number(g, i, k);
      }
      int cptlmemenombre;
      for (uint x = 0; x < g->nb_rows; x++) {  // parcours les lignes
        cptlmemenombre = 0;
        for (uint y = 0; y < g->nb_cols; y++) {  // parcours les colonnes
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
        if (cptlmemenombre == g->nb_cols) {
          return -1;
        }
      }
    }
    if (testcolonne) {
      int tab[g->nb_rows];
      for (uint k = 0; k < g->nb_rows;
           k++) {  // parcours la colonne et met les valeurs dans un tableau
        tab[k] = game_get_number(g, k, j);
      }
      int cptcmemenombre;
      for (uint x = 0; x < g->nb_cols; x++) {  // parcours les colonnes
        cptcmemenombre = 0;
        for (uint y = 0; y < g->nb_rows; y++) {  // parcours les lignes
          if (y == j) {  // si sur la meme colonne que la case testé on passe a
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
        if (cptcmemenombre == g->nb_rows) {
          return -1;
        }
      }
    }
  }
  return 0;
}

bool game_check_move(cgame g, uint i, uint j, square s) {
  if (g == NULL) {
    printf("game_check_move: game is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (s == S_IMMUTABLE_ONE || s == S_IMMUTABLE_ZERO || i >= g->nb_rows ||
      j >= g->nb_cols) {
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
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    printf(
        "game_play_move: game is NULL or i or j is out of range, params : "
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
    queue_push_head(g->historique, tab);
    queue_clear_full(g->annulation, free);
  }
}

bool game_is_over(cgame g) {
  if (g == NULL) {
    printf("game_is_over: game is NULL\n");
    exit(EXIT_FAILURE);
  }
  for (uint k = 0; k < g->nb_rows; k++) {
    for (uint l = 0; l < g->nb_cols; l++) {
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
  if (g == NULL) {
    printf("game_restart: game is NULL\n");
    exit(EXIT_FAILURE);
  }
  for (uint i = 0; i < g->nb_rows; i++) {
    for (uint j = 0; j < g->nb_cols; j++) {
      if (game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
          game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
        game_set_square(g, i, j, S_EMPTY);
      }
    }
  }
  queue_clear_full(g->historique, free);
  queue_clear_full(g->annulation, free);
}
