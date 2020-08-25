//
// Created by mfbut on 7/17/2018.
//

#include <stdio.h>
#include "move.h"
#include "board.h"
#include "InputValidation.h"
#include "CursorTrakedWindow.h"

Move getValidMove(struct Board_Struct* board, TurnType playerTurn, CursorTrackedWindow* win) {
  Move move;

  while (true) {

    char input = wgetch(win->cursesWin);
    /*if (input == 'w' || input == (KEY_UP & A_CHARTEXT)) {
      if (win->cursorRow > 0) {
        win->cursorRow -= 1;
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
      }
    }
     */
    if (input == 'a' || input == 'j') {
      if (win->cursorCol > 0) {
        win->cursorCol -= 1;
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
      }
    } /*else if (input == 's' || input == (KEY_DOWN & A_CHARTEXT)) {
      if (win->cursorRow < board->numRows - 1) {
        win->cursorRow += 1;
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
      }
    }*/ else if (input == 's' || input == 'k') {
      if (win->cursorCol < board->numCols - 1) {
        win->cursorCol += 1;
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
      }

    } else if ((input == ' ' || input == '\n') &&
        board->theBoard[win->cursorRow][win->cursorCol] == board->blankChar) {
      move.row = win->cursorRow;
      move.col = win->cursorCol;
      move.marker = "XO"[playerTurn];
      return move;
    }
    wrefresh(win->cursesWin);
  }

}

bool isValidMove(Move move, struct Board_Struct* board, int numArgsRead, int numArgsNeeded) {
  return isValidFormat(numArgsRead, numArgsNeeded) &&
      isInRange(move.row, 0, board->numRows - 1) &&
      isInRange(move.col, 0, board->numCols - 1) &&
      board->theBoard[move.row][move.col] == board->blankChar;
}

const char* PlayerToString(TurnType player) {
  static const char p1[] = "Player1";
  static const char p2[] = "Player2";
  if (player == Player1) {
    return p1;
  } else {
    return p2;
  }
}