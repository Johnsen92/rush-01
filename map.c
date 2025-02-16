#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "map.h"

int factorial(int n)
{
    int f = 1;
    for (int i = 1; i <= n; i++)
        f *= n;
    return n;
}

int compare(void const* a, void const* b)
{
    return *(int *)a > *(int *)b;
}

bool isValid(int ** map, int width)
{
    int ** rowMap = (int **) malloc(width * sizeof(int*));
    int ** colMap = (int **) malloc(width * sizeof(int*));
    for (int i = 0; i < width; i++)
    {
        rowMap[i] = (int *) malloc(width * sizeof(int));
        colMap[i] = (int *) malloc(width * sizeof(int));
    }

    for (int row = 0; row < width; row++)
        for (int col = 0; col < width; col++)
        {
            colMap[col][row] = map[col][row];
            rowMap[col][row] = map[row][col];
        }

    for (int row = 0; row < width; row++)
    {
        qsort(rowMap[row], width, sizeof(int), compare);
        qsort(colMap[row], width, sizeof(int), compare);
    }

    bool isValid = true;
    for (int row = 0; row < width; row++)
        for (int col = 0; col < width - 1; col++)
        {
            isValid = isValid && rowMap[row][col] < rowMap[row][col + 1];
            isValid = isValid && colMap[row][col] < colMap[row][col + 1];
        }

    for (int i = 0; i < width; i++)
    {
        free(rowMap[i]);
        free(colMap[i]);
    }
    free(rowMap);
    free(colMap);
    return isValid;
}

int viewUp(int ** map, int width, int col)
{
    int view = 0;
    int max = 0;
    for (int row = 0; row < width; row++)
    {
        if (map[row][col] > max)
        {
            max = map[row][col];
            view++;
        }
    }
    return view;
}

int viewDown(int ** map, int width, int col)
{
    int view = 0;
    int max = 0;
    for (int row = width - 1; row >= 0; row--)
    {
        if (map[row][col] > max)
        {
            max = map[row][col];
            view++;
        }
    }
    return view;
}

int viewLeft(int ** map, int width, int row)
{
    int view = 0;
    int max = 0;
    for (int col = 0; col < width; col++)
    {
        if (map[row][col] > max)
        {
            max = map[row][col];
            view++;
        }
    }
    return view;
}

int viewRight(int ** map, int width, int row)
{
    int view = 0;
    int max = 0;
    for (int col = width - 1; col >= 0; col--)
    {
        if (map[row][col] > max)
        {
            max = map[row][col];
            view++;
        }
    }
    return view;
}

bool isSolved(int ** map, int width, int * constraints)
{
    bool isSolved = isValid(map, width);
    for (int pos = 0; (pos < width) && isSolved; pos++)
    {
        isSolved = isSolved && viewUp(map, width, pos) == constraints[VIEW_UP(pos)];
        isSolved = isSolved && viewDown(map, width, pos) == constraints[VIEW_DOWN(pos)];
        isSolved = isSolved && viewLeft(map, width, pos) == constraints[VIEW_LEFT(pos)];
        isSolved = isSolved && viewRight(map, width, pos) == constraints[VIEW_RIGHT(pos)];
    }
    return isSolved;
}

void printMap(int ** map, int width)
{
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < width; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }
}

void printConstraints(int * constraints, int width)
{
    printf("\"");
    for (int i = 0; i < (width*4) - 1; i++)
    {
        printf("%d ", constraints[i]);
    }
    printf("%d", constraints[(width*4) - 1]);
    printf("\"\n");
}

void printBoard(int ** map, int width, int * constraints)
{
    printf("  ");
    for (int col = 0; col < width; col++)
        printf("%d ", constraints[VIEW_UP(col)]);
    printf("\n");

    for (int row = 0; row < width; row++)
    {
        printf("%d ", constraints[VIEW_LEFT(row)]);
        for (int col = 0; col < width; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("%d \n", constraints[VIEW_RIGHT(row)]);
    }

    printf("  ");
    for (int col = 0; col < width; col++)
        printf("%d ", constraints[VIEW_DOWN(col)]);
    printf("\n"); 
}

void printLine(void)
{
    for (int i = 0; i < 120; i++)
        printf("-");
    printf("\n");
}

void swapRows(int ** map, int width, int row1, int row2)
{
    for (int col = 0; col < width; col++)
    {
        int temp = map[row1][col];
        map[row1][col] = map[row2][col];
        map[row2][col] = temp;
    }
}

void swapCols(int ** map, int width, int col1, int col2)
{
    for (int row = 0; row < width; row++)
    {
        int temp = map[row][col1];
        map[row][col1] = map[row][col2];
        map[row][col2] = temp;
    }
}

int initMap(int ** map, int width)
{
    for (int row = 0; row < width; row++)
        for (int col = 0; col < width; col++)
            map[row][(col + row) % width] = col + 1;
    return 0;
}

bool permute(int ** map, int width, int * constraints, int start)
{
    if (start == width)
        return false;

    bool solved = isSolved(map, width, constraints); 

    for(int i = start; (i < width) && !solved; i++)
    {
        swapRows(map, width, start, i);
        solved = permuteCols(map, width, constraints, 0);
        if (!solved)
            solved = permute(map, width, constraints, start + 1);
        if (!solved)
            swapRows(map, width, start, i);
    }
    return solved;
}

bool permuteCols(int ** map, int width, int * constraints, int start)
{
    if (start == width)
        return false;

    bool solved = isSolved(map, width, constraints); 

    for(int i = start; (i < width) && !solved; i++)
    {
        swapCols(map, width, start, i);
        solved = permuteCols(map, width, constraints, start + 1);
        if (!solved)
            swapCols(map, width, start, i);
    }
    return solved;
}