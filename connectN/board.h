

#ifndef SUMMER2018TICTACTOE_BOARD_H
#define SUMMER2018TICTACTOE_BOARD_H
#include "move.h"

 typedef struct Board_Struct{
   char** theBoard;
   int numRows, numCols, numtowin;
   char blankChar;
 }Board;



Board makeBoard(int numRows, int numCols, char blankChar, int numtowin);
void printBoard(Board board);
void cleanUpBoard(Board* board);

void placeMove(Move move, Board* board, CursorTrackedWindow* win);

#endif //SUMMER2018TICTACTOE_BOARD_H