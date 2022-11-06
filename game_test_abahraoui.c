#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"






void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}



bool test_game_is_empty(){
  game g = game_new_empty();
  for (uint i = 0; i < DEFAULT_SIZE; i++)
  {
    for(uint j = 0; j< DEFAULT_SIZE; j++){
      if (game_get_square(g,i,j)!=S_EMPTY)
      {
       game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}


bool test_game_play_move(){
  game g = game_new_empty();
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      game_set_square(g,i,j,S_ONE);
    }
  }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      if(  game_get_square(g,i,j)!=S_ONE)
       return false;
    }
    }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      game_set_square(g,i,j,S_EMPTY);
    }
  }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      if(  game_get_square(g,i,j)!=S_EMPTY)
       return false;
    }
    }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      game_set_square(g,i,j,S_ZERO);
    }
  }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      if(game_get_square(g,i,j)!=S_ZERO)
       return false;
    }
  }

game_delete(g);
  return true;
}


bool test_game_has_error(){
  game g = game_new_empty();
  game_set_square(g, 0, 0, S_ONE);
  game_set_square(g, 0, 1, S_ONE);
  game_set_square(g, 0, 2, S_ONE);
  if(!game_has_error(g,0,0) && !game_has_error(g,0,1)&& !game_has_error(g,0,2) ){
    return 0;
  }
  else{
    return 1;
  }
}

bool test_game_restart(){
  return true;
}

bool test_game_is_over(){
  game over = game_default_solution();
  game unmodified = game_default();
  game error = game_default_solution();
  game_play_move(error, 3, 4, S_ONE);
  bool test = (!(game_is_over(unmodified)) && (game_is_over(over)) && !(game_is_over(error)));

  game_delete(over);
  game_delete(unmodified);
  game_delete(error);
  return test;
}

bool test_game_check_move() {
  game g = game_new_empty();

  

  game_set_square(g, 0, 3, S_EMPTY);
  bool empty = (!(game_check_move(g, 0, 3, S_EMPTY)) || (game_check_move(g, 0, 3, S_ONE)) || (game_check_move(g, 0, 3, S_ZERO)));

  game_set_square(g, 0, 4, S_ZERO);
  bool zero = (!(game_check_move(g, 0, 4, S_ONE)) || (game_check_move(g, 0, 4, S_ZERO)) || !(game_check_move(g, 0, 4, S_EMPTY)));

  game_set_square(g, 0, 5, S_ONE);
  bool one = ((game_check_move(g, 0, 5, S_ONE)) || !(game_check_move(g, 0, 5, S_ZERO)) || !(game_check_move(g, 0, 5, S_EMPTY)));

  
  bool outside_the_grid = (game_check_move(g, 0, 7, S_EMPTY));

  game_delete(g);
  return (empty || zero || one || outside_the_grid);
}



int main(int argc, char *argv[])
{
  if (argc == 1)
    usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_is_empty", argv[1]) == 0)
    ok = test_game_is_empty();
  else if(strcmp("game_play_move", argv[1]) == 0)
    ok = test_game_play_move();
  else if(strcmp("game_has_error", argv[1]) == 0)
    ok = test_game_has_error();
  else if(strcmp("game_restart", argv[1]) == 0)
    ok = test_game_restart();
     else if(strcmp("game_check_move", argv[1]) == 0)
    ok = test_game_check_move();
    else if(strcmp("game_is_over", argv[1]) == 0)
    ok = test_game_is_over();

    else{
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);

  }

  if(ok)
  {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  }
  else
  {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}

