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
    return game_equal(g,copy);
    
    
}
bool test_game_equal(){
    game g = game_default();
    game copy = game_copy(g);
    game empty = game_new_empty();
    game solution = game_default_solution();
    if(game_equal(g,copy) == true && game_equal(g,empty) == false && 
    game_equal(copy,solution) == false && game_equal(copy,g) == true &&
     game_equal(solution,copy) == false){
        return true;
     }
     return false;
    
}
bool test_game_delete(){
    game g = game_default();
    game_delete(g);
    return true;
    
}
bool test_game_default(){
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
