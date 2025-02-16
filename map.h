#define VIEW_UP(col)    (col)
#define VIEW_DOWN(col)  (col + width)
#define VIEW_LEFT(row)  (row + 2*width)
#define VIEW_RIGHT(row) (row + 3*width)

#define MAX_SUM(width) ((width * (width + 1)) / 2)


int factorial(int n);
int compare(void const* a, void const* b);
bool isValid(int ** map, int width);
int viewUp(int ** map, int width, int col);
int viewDown(int ** map, int width, int col);
int viewLeft(int ** map, int width, int row);
int viewRight(int ** map, int width, int row);
bool isSolved(int ** map, int width, int * constraints);
void printMap(int ** map, int width);
void printConstraints(int * constraints, int width);
void printBoard(int ** map, int width, int * constraints);
void printFixed(bool ** fixed, int width, int * constraints);
void printLine(void);
int colSum(int ** map, int width, int col);
int rowSum(int ** map, int width, int col);
void swapRows(int ** map, int width, int row1, int row2);
void swapCols(int ** map, int width, int col1, int col2);
bool permute(int ** map, int width, int * constraints, int start);
bool permuteCols(int ** map, int width, int * constraints, int start);
void initMap(int ** map, int width);
void initMapNum(int ** map, int width, int num);