#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include"game.h" 
#include "game_aux.h"

void usage(int argc, char *argv[]){
    fprintf(stderr,"Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

bool test_dummy(){
    return true;
}


bool test_game_print(){
    game g = game_default();
    game_print(g);
    return true;
}
bool test_game_new(){
     square *square_array = malloc(sizeof(square)*(DEFAULT_SIZE*DEFAULT_SIZE));
    
    for(int i = 0; i < 36; i++){
        square_array[i] = S_EMPTY;
    }
    game g = game_new(square_array);
    for(int i = 0; i < 6; i++){
        for(int j = 0; i < 6; i++){
            if(game_get_square(g, i, j) != S_ZERO && game_get_square(g, i, j) != S_EMPTY && game_get_square(g, i, j) != S_IMMUTABLE_ONE && game_get_square(g, i, j) != S_IMMUTABLE_ZERO && game_get_square(g, i, j) != S_ONE ){return false;}
        }
    }
    return true;
}
bool test_game_new_empty(){
    game g = game_new_empty();
    for(int i = 0; i <= 5; i++){
        for(int j = 0; j <= 5; j++){
            square tmp = game_get_square(g,i,j);
            if(tmp != S_EMPTY){
                return false;
            }
        }
    }
    return true;
}
bool test_game_copy(){
    game g = game_default();
    game copy = game_copy(g);
    if(&g != &copy){
    return game_equal(g,copy);
    }
    return false;
    
    
}
bool test_game_equal(){
    game g = game_default();
    game copy = game_new_empty();
    bool test = game_equal(g,copy);
    if(test == true){
        for(int i = 0; i <= DEFAULT_SIZE; i++){
            for(int j = 0; j <= DEFAULT_SIZE; j++){
                if(game_get_square(g,i,j) != game_get_square(copy,i,j) ||
                 game_get_number(g,i,j) != game_get_number(copy,i,j) ||
                 game_is_immutable(g,i,j) != game_is_immutable(copy,i,j)){
                    return false;
                }
            }
        }
    }else{
        for(int i = 0; i <= DEFAULT_SIZE; i++){
            for(int j = 0; j <= DEFAULT_SIZE; j++){
                if(game_get_square(g,i,j) != game_get_square(copy,i,j)||
                 game_get_number(g,i,j) != game_get_number(copy,i,j)||
                 game_is_immutable(g,i,j) != game_is_immutable(copy,i,j)){
                    return true;
                }
            }
        }
        
    }
    return true;
}
bool test_game_delete(){
    game g = game_default();
    game_delete(g);
    return true;
    
}
bool test_game_default(){
    game g = game_default();
    for(int i = 0; i <= 5; i++){
        for(int j = 0; j <= 5; j++){
           if((i == 0 && j == 1) || (i == 3 && j == 2) || (i == 4 && j == 2))
                {
                    if(game_get_square(g,i,j) != S_IMMUTABLE_ONE){
                        return false;
                    }
                }
           else if ((i == 0 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 4) || (i == 3 && j == 1)
            || (i == 4 && j == 5) || (i == 5 && j == 5))
                {
                    if(game_get_square(g,i,j) != S_IMMUTABLE_ZERO){
                        return false;
                    }
                }
            else{
                if(game_get_square(g,i,j) != S_EMPTY){
                    return false;
                }
            }
           
           
        }
    }

    return true;
}


int main(int argc, char *argv[]){
    if(argc == 1){
        usage(argc, argv);
    }
    fprintf(stderr, "-> Start test \"%s\"\n", argv[1]);
    bool tmp = false;

    if(strcmp("dummy", argv[1]) == 0){
        tmp = test_dummy();
    }
    
    else if(strcmp("game_print", argv[1]) == 0){
            tmp = test_game_print();




   }
   
   else if(strcmp("game_delete", argv[1]) == 0){
            tmp = test_game_delete();




   }
   else if(strcmp("game_new", argv[1]) == 0){
            tmp = test_game_new();




   }
   else if(strcmp("game_new_empty", argv[1]) == 0){
            tmp = test_game_new_empty();




   }
   else if(strcmp("game_copy", argv[1]) == 0){
            tmp = test_game_copy();




   }else if(strcmp("game_equal", argv[1]) == 0){
            tmp = test_game_equal();




   }else if(strcmp("game_default", argv[1]) == 0){
            tmp = test_game_default();




   }else{
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    

    if(tmp == true){
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }else{
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}
