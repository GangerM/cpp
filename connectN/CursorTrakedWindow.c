#include "CursorTrakedWindow.h"

CursorTrackedWindow newCursorTrackedWindow(int numRows, int numCols, int rowStart, int colStart){
    CursorTrackedWindow window;
    window.cursesWin = newwin(numRows, numCols, rowStart, colStart);
    window.cursorRow = 0;
    window.cursorCol = 0;
    return window;
}

/**
 * Doesn't advance the cursor
 * @param win
 * @param fillChar
 */
void fillWindow(CursorTrackedWindow* win, char fillChar){
    int curRow = win->cursorRow, curCol = win->cursorCol;
    for (int i = 0; i < getNumRows(win); ++i) {
        for (int j = 0; j < getNumCols(win); ++j) {
            mvwaddch(win->cursesWin, i, j, fillChar);
        }
    }
    wmove(win->cursesWin, curRow, curCol);
}

int getNumRows(CursorTrackedWindow* win){
    return getmaxy(win->cursesWin);
}
int getNumCols(CursorTrackedWindow* win){
    return getmaxx(win->cursesWin);
}

void moveAndAddCharacter(CursorTrackedWindow* win, int row, int col, char toAdd) {
    mvwaddch(win->cursesWin, row, col, toAdd);
    win->cursorRow = row;
    win->cursorCol = col;
}

void addCharacter(CursorTrackedWindow* win, char toAdd) {
    moveAndAddCharacter(win, win->cursorRow, win->cursorCol, toAdd);
}

void CursorTrackedWindowMove(CursorTrackedWindow* win, int row, int col) {
    wmove(win->cursesWin, row, col);
    win->cursorRow = row;
    win->cursorCol = col;
}

