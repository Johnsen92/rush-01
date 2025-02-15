#define VIEW_UP(col)    (col)
#define VIEW_DOWN(col)  (col + width)
#define VIEW_LEFT(row)  (row + 2*width)
#define VIEW_RIGHT(row) (row + 3*width)

int compare(void const* a, void const* b);
bool isValid(int ** map, int width);
int viewUp(int ** map, int width, int col);
int viewDown(int ** map, int width, int col);
int viewLeft(int ** map, int width, int row);
int viewRight(int ** map, int width, int row);
bool isSolved(int ** map, int width, int * constraints);
bool printMap(int ** map, int width);
void swapRows(int ** map, int width, int row1, int row2);
void swapCols(int ** map, int width, int col1, int col2);
void rotateRowsLeft(int ** map, int width, int start);
void rotateColsLeft(int ** map, int width, int start);
int initMap(int ** map, int width);