#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void usage(int argc, char *argv[]){
    fprintf(stderr,"Usage: %s <testname> [<...>]\n", argv[0]);
}

bool test_dummy(){
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