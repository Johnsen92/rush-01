#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "map.h"

#define SHUFFLES 100

static void shuffle(int ** map, int width)
{
    int col1 = rand() % width;
    int col2 = rand() % width;
    while (col1 == col2)
    {
        col2 = rand() % width;
    }
    int row1 = rand() % width;
    int row2 = rand() % width;
    while (row1 == row2)
    {
        row2 = rand() % width;
    }
    swapRows(map, width, row1, row2);
    swapCols(map, width, col1, col2);
}

static void deriveConstraints(int ** map, int width, int * constraints)
{
    for(int pos = 0; pos < width; pos++)
    {
        constraints[VIEW_UP(pos)] = viewUp(map, width, pos);
        constraints[VIEW_DOWN(pos)] = viewDown(map, width, pos);
        constraints[VIEW_LEFT(pos)] = viewLeft(map, width, pos);
        constraints[VIEW_RIGHT(pos)] = viewRight(map, width, pos);
    }
}

int main(int argc, char ** argv)
{
    srand(time(NULL));
    assert(argc == 2);
    int width = strtol(argv[1], NULL, 10);
    int ** map = (int **) malloc(width * sizeof(int*));
    for (int i = 0; i < width; i++)
    {
        map[i] = (int *) malloc(width * sizeof(int));
    }
    int * constraints = (int *) malloc(width * 4 * sizeof(int));

    initMap(map, width);

    for (int i = 0; i < SHUFFLES; i++)
    {
        shuffle(map, width);
    }
    assert(isValid(map, width));

    deriveConstraints(map, width, constraints);
    printConstraints(constraints, width);
}