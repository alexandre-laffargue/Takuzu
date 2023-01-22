#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_struct.h"

void* memory_alloc1(uint size) {
  void* tmp = malloc(size);
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation failed \n");
    exit(EXIT_FAILURE);
  } else {
    return tmp;
  }
}

bool game_is_unique(cgame g) {
  game_is_null(g, "game_is_unique");
  return g->unique;
}

bool game_is_wrapping(cgame g) {
  game_is_null(g, "game_is_wrapping");
  return g->wrapping;
}

uint game_nb_cols(cgame g) {
  game_is_null(g, "game_nb_cols");
  return g->nb_cols;
}

uint game_nb_rows(cgame g) {
  game_is_null(g, "game_nb_rows");
  return g->nb_rows;
}

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping,
                  bool unique) {
  if (squares == NULL) {
    exit(EXIT_FAILURE);
  }
  if (nb_rows % 2 != 0 || nb_cols % 2 != 0) {
    exit(EXIT_FAILURE);
  }
  game new = memory_alloc1(sizeof(struct game_s));
  new->nb_rows = nb_rows;
  new->nb_cols = nb_cols;
  new->wrapping = wrapping;
  new->unique = unique;
  new->history = queue_new();
  new->cancelation = queue_new();

  square* array = memory_alloc1((new->nb_rows* new->nb_cols) * sizeof(square));

  for (int i = 0; i < (new->nb_rows* new->nb_cols); i++) {
    square tmp = squares[i];
    array[i] = tmp;
  }
  new->square_array = array;
  return new;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping,
                        bool unique) {
  square* array = memory_alloc1((nb_rows * nb_cols) * sizeof(square));

  for (int i = 0; i < (nb_rows * nb_cols); i++) {
    array[i] = S_EMPTY;
  }

  game g = game_new_ext(nb_rows, nb_cols, array, wrapping, unique);
  free(array);
  return g;
}

void game_undo(game g) {
  game_is_null(g, "game_undo");
  if (queue_is_empty(g->history)) {
    printf("Pas d'undo possible \n");
    return;
  }

  int* tab = queue_pop_head(g->history);
  queue_push_head(g->cancelation, tab);
  int* tab_coup_joue[queue_length(g->history)];

  int compteur = -1;
  bool changed = false;
  while (!queue_is_empty(g->history)) {
    compteur++;
    tab_coup_joue[compteur] = queue_pop_head(g->history);
    if ((tab[0] == tab_coup_joue[compteur][0]) &&
        (tab[1] == tab_coup_joue[compteur][1])) {
      game_set_square(g, tab[0], tab[1], tab_coup_joue[compteur][2]);
      changed = true;
      break;
    }
  }
  while (compteur >= 0) {
    queue_push_head(g->history, tab_coup_joue[compteur]);
    compteur--;
  }
  if (!changed) {
    game_set_square(g, tab[0], tab[1], S_EMPTY);
  }
}

void game_redo(game g) {
  game_is_null(g, "game_redo");
  if (queue_is_empty(g->cancelation)) {
    printf("Pas d'annulation possible \n");
    return;
  }
  if (!queue_is_empty(g->cancelation)) {
    int* tab = queue_pop_head(g->cancelation);
    game_set_square(g, tab[0], tab[1], tab[2]);
    queue_push_head(g->history, tab);
  }
}
