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
bool test_game_new();
bool test_game_new_empty();
bool test_game_copy();
bool test_game_equal();
bool test_game_delete();
bool test_game_default();


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
