#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "map.h"

static bool solve(int ** map, int width, int * constraints, int start)
{
    if (isSolved(map, width, constraints))
        return true;
    if (start < width) {
        int i, j;
        for (i = width-2; i >= start; i--) {
            for (j = i + 1; j < width; j++) {
                swapCols(map, width, i, j);
                solve(map, width, constraints, i+1);
            }
            rotateRowsLeft(map, width, i);
            if (isSolved(map, width, constraints))
                return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    /* Assert that only one argument was provided (filename excluded) */
    assert(argc == 2);

    /* Assert that the number of constraints is a square number */
    int argCount = (strlen(argv[1]) + 1)/2;
    int width = sqrt(argCount);
    printf("Args: %d\n", argCount);
    printf("Width: %d\n", width);
    assert(width * width == argCount);

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
    
    initMap(map, width);

    printf("Here!\n");

    /* Assert that calculated number of constraints is equal to the number of parsed tokens */
    assert(i == argCount);
    assert(solve(map, width, constraints, 0));
    assert(isValid(map, width));
    printMap(map, width);
}