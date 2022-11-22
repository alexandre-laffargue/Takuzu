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

game game_new(square* squares) {
  game new;
  new = memory_alloc(sizeof(game));
  new->square_array = memory_alloc((DEFAULT_SIZE*DEFAULT_SIZE) * sizeof(square));

  
  new->square_array = squares;
  new->size = DEFAULT_SIZE;

  return new;


}

game game_new_empty(void) {
  game g;
  g = memory_alloc(sizeof(game));
  g->square_array = memory_alloc((DEFAULT_SIZE*DEFAULT_SIZE) * sizeof(square));


  square sq[DEFAULT_SIZE*DEFAULT_SIZE];

  for(int i = 0; i< DEFAULT_SIZE*DEFAULT_SIZE ; i++){
    g->square_array[i] = S_EMPTY;
  }
 
  g->size = DEFAULT_SIZE;

  return g;


}

game game_copy(cgame g) {
  if( g == NULL){
    exit(EXIT_FAILURE);
  }
  game copy;
  copy = memory_alloc(sizeof(game));
  copy->square_array = memory_alloc((DEFAULT_SIZE*DEFAULT_SIZE-1) * sizeof(square));
  if(copy == NULL){
    exit(EXIT_FAILURE);
  }
  copy->size = g->size;
  for(int i = 0; i<(DEFAULT_SIZE*DEFAULT_SIZE); i++){
    copy->square_array[i] = g->square_array[i];

  }
  

  return copy;


}

bool game_equal(cgame g1, cgame g2) {
   if(g1 == NULL || g2 == NULL ){
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < DEFAULT_SIZE*DEFAULT_SIZE; i++){
    if(g1->square_array[i] != g2->square_array[i]){
      return false;
    }
    
  }
  return true;
}

void game_delete(game g) {
  if(g != NULL){
    
  free(g);
  }

}

void game_set_square(game g, uint i, uint j, square s) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE || (s != S_EMPTY && s!= S_IMMUTABLE_ONE && s!= S_IMMUTABLE_ZERO && s != S_ONE && s != S_ZERO)){
    exit(EXIT_FAILURE);
  }
  uint index = (i*g->size) +j;
  g->square_array[index] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE){
    exit(EXIT_FAILURE);
  }
  uint index = (i*g->size) +j;
  return g->square_array[index];
}

int game_get_number(cgame g, uint i, uint j) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE){
    exit(EXIT_FAILURE);
  }
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
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE || dist > 2){
    exit(EXIT_FAILURE);
  }
  uint index = (i*g->size) +j;
  if(dir == UP){
    int coord = i - dist;
    if(coord >= 0 && coord < g->size){
      uint indexf = index - (dist*g->size);
      square sq = g->square_array[indexf];
      return sq;
    }else{return -1;}
  }
  else if (dir == DOWN){
    int coord = i + dist;
    if(coord >= 0 && coord < g->size){
      uint indexf = index + (dist*g->size);
      square sq = g->square_array[indexf];
      return sq;
    }else{return -1;}
  }
  else if (dir == LEFT){
    int coord = j - dist;
    if(coord >= 0 && coord < g->size){
      uint indexf = index - dist;
      square sq = g->square_array[indexf];
      return sq;
    }else{return -1;}
  }
  else if (dir == RIGHT){
    int coord = j + dist;
    if(coord >= 0 && coord < g->size){
      uint indexf = index + dist;
      square sq = g->square_array[indexf];
      return sq;
    }else{return -1;}
  }
  exit(EXIT_FAILURE);
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE || dist > 2){
    exit(EXIT_FAILURE);
  }
  int sq = game_get_next_square(g, i, j, dir, dist);
  if(sq == -1){
    return -1;
  }
  if(sq == S_ZERO || sq == S_IMMUTABLE_ZERO){
    return 0;
  }
  else if(sq == S_ONE || sq == S_IMMUTABLE_ONE){
    return 1;
  }
  else
    return -1; 
}

bool game_is_empty(cgame g, uint i, uint j) { return NULL; }

bool game_is_immutable(cgame g, uint i, uint j) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE) {
    exit(EXIT_FAILURE);
  }
  square sq = game_get_square(g, i, j);
  if(sq == S_IMMUTABLE_ONE || sq == S_IMMUTABLE_ZERO) {
    return true;
  } else { return false; }
}

int game_has_error(cgame g, uint i, uint j) { return 0; }

bool game_check_move(cgame g, uint i, uint j, square s) { return NULL; }

void game_play_move(game g, uint i, uint j, square s) {}

bool game_is_over(cgame g) { return NULL; }

void game_restart(game g) {}
