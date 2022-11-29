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
  if(squares == NULL ){
    exit(EXIT_FAILURE);
  }
  game new;
  new = memory_alloc(sizeof(game));
  new->square_array = memory_alloc((DEFAULT_SIZE*DEFAULT_SIZE) * sizeof(square));

  for(int i = 0; i<(DEFAULT_SIZE*DEFAULT_SIZE); i++){
    square tmp = squares[i];
    new->square_array[i] = tmp;
  }
  
  new->size = DEFAULT_SIZE;

  return new;


}

game game_new_empty(void) {
  game g;
  g = memory_alloc(sizeof(game));
  g->square_array = memory_alloc((DEFAULT_SIZE*DEFAULT_SIZE) * sizeof(square));




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
  copy->square_array = memory_alloc((DEFAULT_SIZE*DEFAULT_SIZE) * sizeof(square));
  if(copy == NULL){
    exit(EXIT_FAILURE);
  }
  copy->size = g->size;
  for(int i = 0; i<DEFAULT_SIZE; i++){
    for(int j = 0; j<DEFAULT_SIZE; j++){
    game_set_square(copy,i,j,game_get_square(g,i,j)) ;
    }

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
    if(g->square_array != NULL){
      
        free(g->square_array);
      
    }
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

bool game_is_empty(cgame g, uint i, uint j) { 
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE){
    exit(EXIT_FAILURE);
  }
  if(game_get_square(g,i,j)!=S_EMPTY){
    return false;
  }
  return true;
}

bool game_is_immutable(cgame g, uint i, uint j) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE) {
    exit(EXIT_FAILURE);
  }
  square sq = game_get_square(g, i, j);
  if(sq == S_IMMUTABLE_ONE || sq == S_IMMUTABLE_ZERO) {
    return true;
  } else { return false; }
}

int game_has_error(cgame g, uint i, uint j) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE){
    exit(EXIT_FAILURE);
   }
   int cpt_ver = 1, cpt_hor = 1;
   if(game_get_number(g,i,j)==game_get_next_number(g,i,j, RIGHT, 1)){
    cpt_hor++;
    if(game_get_number(g,i,j)==game_get_next_number(g,i,j, RIGHT, 2)){
      return -1;
    }
   }
   if(game_get_number(g,i,j)==game_get_next_number(g,i,j, LEFT, 1)){
    cpt_hor++;
    if(cpt_hor>2){
      return -1;
    }
    if(game_get_number(g,i,j)==game_get_next_number(g,i,j, LEFT, 2)){
      return -1;
    }
   }
   /* vertical*/
   if(game_get_number(g,i,j)==game_get_next_number(g,i,j, UP, 1)){
    cpt_ver++;
    if(game_get_number(g,i,j)==game_get_next_number(g,i,j, UP, 2)){
      return -1;
    }
   }
   if(game_get_number(g,i,j)==game_get_next_number(g,i,j, DOWN, 1)){
    cpt_ver++;
    if(cpt_ver>2){
      return -1;
    }
    if(game_get_number(g,i,j)==game_get_next_number(g,i,j, DOWN, 2)){
      return -1;
    }
   }
   int cpt_ver0 = 0, cpt_hor0 = 0, cpt_ver1 = 0, cpt_hor1 = 0;
   for(uint k=0; k<g->size; k++){
    if(game_get_number(g,k,j)==0){
      cpt_hor0++;
    }
    if(game_get_number(g,i,k)==0){
      cpt_ver0++;
    }
    if(game_get_number(g,k,j)==1){
      cpt_hor1++;
    }
    if(game_get_number(g,i,k)==1){
      cpt_ver1++;
    }
   }
   if(cpt_hor0 > (g->size/2) || cpt_ver0 > (g->size/2) || cpt_ver1 > (g->size/2) || cpt_hor1 > (g->size/2)){
    return -1;
   }
   else{
    return 0;
   }
   
}

bool game_check_move(cgame g, uint i, uint j, square s) {
  if(g == NULL){
    exit(EXIT_FAILURE);
  }
  if(game_get_square(g,i,j)!=S_IMMUTABLE_ONE && game_get_square(g,i,j)!=S_IMMUTABLE_ZERO && i<g->size && j<g->size){
    return true;
  }
  else{
    return false;
  }
}

void game_play_move(game g, uint i, uint j, square s) {
  if(g == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE){
    exit(EXIT_FAILURE);
  }
  if(s==S_IMMUTABLE_ONE && s==S_IMMUTABLE_ONE){
    exit(EXIT_FAILURE);
  }
  if(game_get_square(g,i,j)!=S_IMMUTABLE_ONE && game_get_square(g,i,j)!=S_IMMUTABLE_ZERO){
    game_set_square(g,i,j,s);
  }
}

bool game_is_over(cgame g) {
  if(g == NULL){
    exit(EXIT_FAILURE);
  }
  for(uint k = 0 ; k<g->size; k++){
    for(uint l = 0; l<g->size; l++){
      if(game_has_error(g,k,l) != 0){
        return false;
      }
    }
  }
  return true;
}

void game_restart(game g) {
 if(g == NULL){
  exit(EXIT_FAILURE);
 }
 for(uint i = 0; i<DEFAULT_SIZE; i++){
  for(uint j = 0; j<DEFAULT_SIZE; j++){
    if(game_get_square(g,i,j)!=S_IMMUTABLE_ONE && game_get_square(g,i,j)!=S_IMMUTABLE_ZERO){
      game_set_square(g,i,j,S_EMPTY);
    }
  }
 }
}
