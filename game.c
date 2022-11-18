#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_aux.h"

struct game_s {
  square* square_array;
  int size;
};

void *memory_alloc(uint size)
{
    void *tmp = malloc(size);
    if (tmp == NULL)
    {
        fprintf(stderr, "Memory allocation failed \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return tmp;
    }
}

game game_new(square* squares) { return NULL; }

game game_new_empty(void) { return NULL; }

game game_copy(cgame g) { return NULL; }

bool game_equal(cgame g1, cgame g2) { return NULL; }

void game_delete(game g) {}

void game_set_square(game g, uint i, uint j, square s) {
  uint index = (i*g->size) +j;
  g->square_array[index] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  uint index = (i*g->size) +j;
  return g->square_array[index];
}

int game_get_number(cgame g, uint i, uint j) { 
  uint index = (i*g->size) +j;
  square sq = g->square_array[index];
  if(sq == S_ZERO || sq == S_IMMUTABLE_ZERO){
    return 0;
  }
  else if(sq == S_ONE || sq == S_IMMUTABLE_ONE){
    return 1;
  }
  else
    return -1; 
}

int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist) {
  return -1;
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
  return -1;
}

bool game_is_empty(cgame g, uint i, uint j) { return NULL; }

bool game_is_immutable(cgame g, uint i, uint j) { return NULL; }

int game_has_error(cgame g, uint i, uint j) { return -1; }

bool game_check_move(cgame g, uint i, uint j, square s) { return NULL; }

void game_play_move(game g, uint i, uint j, square s) {}

bool game_is_over(cgame g) { return NULL; }

void game_restart(game g) {}
