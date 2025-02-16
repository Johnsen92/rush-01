#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "map.h"

#define MAX_SUM(width) ((width * (width + 1)) / 2)

int main(int argc, char **argv)
{
    /* Assert that only one argument was provided (filename excluded) */
    assert(argc == 2);

    /* Assert that the number of constraints is a square number */
    int argCount = (strlen(argv[1]) + 1)/2;
    assert(argCount % 4 == 0);
    int width = argCount / 4;
    printf("Args: %d\n", argCount);
    printf("Width: %d\n", width);

    int * constraints = (int *) malloc(argCount * sizeof(int));
    int ** map = (int **) malloc(width * sizeof(int*));
    for (int i = 0; i < width; i++)
    {
        map[i] = (int *) malloc(width * sizeof(int));
    }

    /* Parse the constraints */
    char delim = ' ';
    char * token = strtok(argv[1], &delim);
    int i = 0;
    while(token != NULL)
    {
        char * end;
        constraints[i] = strtol(token, &end, 10);
        assert(*end == '\0');
        i++;
        token = strtok(NULL, &delim);
    }
    /* Assert that calculated number of constraints is equal to the number of parsed tokens */
    assert(i == argCount);
    
    initMap(map, width);
    assert(permute(map, width, constraints, 0));
    assert(isValid(map, width));
    printBoard(map, width, constraints);
}