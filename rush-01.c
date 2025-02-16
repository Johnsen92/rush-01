#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "map.h"

#define MAX_SUM(width) ((width * (width + 1)) / 2)

// static bool solve(int ** map, int width, int * constraints, int start)
// {
//     if (isSolved(map, width, constraints))
//         return true;

//     if (start < width) {
//         int i, j;
//         for (i = width-2; i >= start; i--) {
//             for (j = i + 1; j < width; j++) {
//                 swapCols(map, width, i, j);
//                 solve(map, width, constraints, i+1);
//                 if (isSolved(map, width, constraints))
//                     return true;
//             }
//             rotateRowsLeft(map, width, i);
//             if (isSolved(map, width, constraints))
//                 return true;
//         }
//     }
//     return false;
// }

static int colsum(int ** map, int width, int col)
{
    int sum = 0;
    for (int row = 0; row < width; row++)
    {
        sum += map[row][col];
    }
    return sum;
}

static int rowsum(int ** map, int width, int row)
{
    int sum = 0;
    for (int col = 0; col < width; col++)
    {
        sum += map[row][col];
    }
    return sum;
}

static bool solveBrute(int ** map, int width, int * constraints, int row, int col)
{
    printMap(map, width);
    for (int i = 0; i < width; i++)
    {

    }

    map[row][col] += 1;
    
    bool solved = isSolved(map, width, constraints);
    for (int r = 0; (r < width) && !solved; r++)
    {
        for (int c = 0; (c < width) && !solved; c++)
        {
            if (map[r][c] < width && rowsum(map, width, r) <= MAX_SUM(width) && colsum(map, width, c) <= MAX_SUM(width))
            {
                solved = solveBrute(map, width, constraints, r, c);
            }
        }
    }
    if (!solved)
        map[row][col] -= 1;
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

    int * constraints = (int *) malloc(argCount * sizeof(int));
    int ** map = (int **) malloc(width * sizeof(int*));
    for (int i = 0; i < width; i++)
    {
        map[i] = (int *) malloc(width * sizeof(int));
    }

    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < width; col++)
        {
            map[row][col] = 1;
        }
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
    
    printBoard(map, constraints, width);

    /* Assert that calculated number of constraints is equal to the number of parsed tokens */
    assert(i == argCount);
    // assert(solve(map, width, constraints, 0));
    assert(solveBrute(map, width, constraints, 0, 0));
    assert(isValid(map, width));
    printBoard(map, constraints, width);
}