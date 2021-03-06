//
// Created by mfbut on 7/17/2018.
//
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "CursorTrakedWindow.h"

Board makeBoard(int numRows, int numCols, char blankChar, int numtowin) {
  Board board;

  board.theBoard = (char**)malloc(numRows * sizeof(char*));
  for (int i = 0; i < numRows; ++i) {
    board.theBoard[i] = (char *) malloc(numCols * sizeof(char));
    for (int j = 0; j < numCols; ++j) {
      board.theBoard[i][j] = blankChar;
    }
  }
  board.numRows = numRows;
  board.numCols = numCols;
  board.blankChar = blankChar;
  board.numtowin = numtowin;
  return board;
}

void printBoard(Board board) { //this will need to be removed or change it to make it right
  //print column header
  printf("  "); //make things line up
  for (int i = 0; i < board.numCols; ++i) {
    printf("%d ", i);
  }
  printf("\n");

  for (int row = 0; row < board.numRows; ++row) {
    printf("%d ", row); //print row header
    for (int col = 0; col < board.numCols; ++col) {
      printf("%c ", board.theBoard[row][col]);
    }
    printf("\n");
  }
}

void cleanUpBoard(Board* board) {

  for (int row = 0; row < board->numRows; ++row) {
    free(board->theBoard[row]);
  }
  free(board->theBoard);
  board->theBoard = NULL;
  board->numRows = 0;
  board->numCols = 0;
}

void placeMove(Move move, Board* board, CursorTrackedWindow* win) {
  board->theBoard[move.row][move.col] = move.marker;
  addCharacter(win, move.marker);
  CursorTrackedWindowMove(win, win->cursorRow, win->cursorCol);
  wrefresh(win->cursesWin);
}