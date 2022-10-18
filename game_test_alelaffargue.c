#define __USE_GNU
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*****TEST*****/
bool test_dummy(int argc, char *name)
{
    if(argc != 3){
        return false;
    }
    printf("entréefonction\n");
    if (strcmp("dummy", name) == 0)
    {
        printf("entrée\n");
        return true;
    }
    return false;
}

/****USAGE****/
void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/****MAIN****/
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argc, argv);
    }

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;

    if (strcmp("dummy", argv[1]) == 0){
      ok = test_dummy(argc, argv[2]);
    }

    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // print test result
    if (ok){
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}