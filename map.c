#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

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
    bool isSolved = true;
    for (int pos = 0; (pos < width) && isSolved; pos++)
    {
        isSolved = isSolved && viewUp(map, width, pos) == constraints[VIEW_UP(pos)];
        isSolved = isSolved && viewDown(map, width, pos) == constraints[VIEW_DOWN(pos)];
        isSolved = isSolved && viewLeft(map, width, pos) == constraints[VIEW_LEFT(pos)];
        isSolved = isSolved && viewRight(map, width, pos) == constraints[VIEW_RIGHT(pos)];
    }
    return true;
}

bool printMap(int ** map, int width)
{
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < width; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }
    return true;
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

void rotateRowsLeft(int ** map, int width, int start)
{
    for (int row = 0; row < width; row++)
    {
        int temp = map[row][start];
        for (int col = start; col < width - 1; col++)
        {
            map[row][col] = map[row][col + 1];
        }
        map[row][width - 1] = temp;
    }
}

void rotateColsLeft(int ** map, int width, int start)
{
    for (int col = start; col < width; col++)
    {
        int temp = map[start][col];
        for (int row = 0; row < width - 1; row++)
        {
            map[row][col] = map[row + 1][col];
        }
        map[width - 1][col] = temp;
    }
}

int initMap(int ** map, int width)
{
    for (int row = 0; row < width; row++)
        for (int col = 0; col < width; col++)
            map[row][(col + row) % width] = col + 1;
    return 0;
}