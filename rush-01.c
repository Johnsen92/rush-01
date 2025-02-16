#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "map.h"

#define COL(index, width) (index % width)
#define ROW(index, width) (index / width)

void preSolve(int ** map, int width, int * constraints, bool ** fixed)
{
    for (int row = 0; row < width; row++)
    {
        if (constraints[VIEW_LEFT(row)] == 1)
        {
            map[row][0] = width;
            fixed[row][0] = true;
        }
        if (constraints[VIEW_RIGHT(row)] == 1)
        {
            map[row][width-1] = width;
            fixed[row][width-1] = true;
        }

        for (int col = 0; col < width; col++)
        {
            if (constraints[VIEW_LEFT(row)] == width)
            {
                map[row][col] = col + 1;
                fixed[row][col] = true; 
            }
            if (constraints[VIEW_RIGHT(row)] == width)
            {
                map[row][col] = width - col;
                fixed[row][col] = true;
            }
        }
    }

    for (int col = 0; col < width; col++)
    {
        if (constraints[VIEW_UP(col)] == 1)
        {
            map[0][col] = width;
            fixed[0][col] = true;
        }
        if (constraints[VIEW_DOWN(col)] == 1)
        {
            map[width-1][col] = width;
            fixed[width-1][col] = true;
        }

        for (int row = 0; row < width; row++)
        {
            if (constraints[VIEW_UP(col)] == 4)
            {
                map[row][col] = row + 1;
                fixed[row][col] = true;
            }
            if (constraints[VIEW_DOWN(col)] == 4)
            {
                map[row][col] = width - row;
                fixed[row][col] = true;
            }
        }
    }
}

bool solve(int ** map, int width, int * constraints, bool ** fixed, int index)
{
    bool solved = isSolved(map, width, constraints);
    
    /* If the map is solved, DON'T backtrack it and return from the recursion */
    if (solved)
        return true;

    /* If we have reached the end of the map, return */
    if (index == width*width)
        return false;
    
    /* If this is a fixed index, skip to the next index */
    if (fixed[ROW(index, width)][COL(index, width)])
        return solve(map, width, constraints, fixed, index+1);
    for (int i = 1; (i <= width) && !solved; i++)
    {
        int tmp = map[ROW(index, width)][COL(index, width)];
        map[ROW(index, width)][COL(index, width)] = i;
        if (colSum(map, width, COL(index, width)) <= MAX_SUM(width) && rowSum(map, width, ROW(index, width)) <= MAX_SUM(width))
        {
            solved = solve(map, width, constraints, fixed, index+1);
        }
        else
        {
            map[ROW(index, width)][COL(index, width)] = tmp;
            break;
        }

        if (!solved)
            map[ROW(index, width)][COL(index, width)] = tmp;
        
    }
    return solved;
}

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

    /* Allocate memory for constraints and map */
    int * constraints = (int *) malloc(argCount * sizeof(int));
    int ** map = (int **) malloc(width * sizeof(int*));
    for (int i = 0; i < width; i++)
    {
        map[i] = (int *) malloc(width * sizeof(int));
    }

    /* Allocate memory for the fixed position array */
    bool ** fixed = (bool **) malloc(width * sizeof(bool*));
    for (int i = 0; i < width; i++)
    {
        fixed[i] = (bool *) malloc(width * sizeof(bool));
        for (int j = 0; j < width; j++)
            fixed[i][j] = false; 
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
    
    /* Initialize map with valid data */
    // initMap(map, width);
    initMapNum(map, width, 1);
    printBoard(map, width, constraints);
    printLine();

    /* Solve the map and assert that it has been solved */
    // assert(permute(map, width, constraints, 0));
    preSolve(map, width, constraints, fixed);
    // printBoard(map, width, constraints);
    // printLine();
    // printFixed(fixed, width, constraints);
    assert(solve(map, width, constraints, fixed, 0));

    /* Assert that the solution is valid (not really necessary) */
    assert(isValid(map, width));

    /* Print the final state of the solved map */
    printBoard(map, width, constraints);
}