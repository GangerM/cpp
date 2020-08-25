#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "move.h"
#include "win.h"
#include "CursorTrakedWindow.h"


int main() {

    initscr();
    noecho();
    cbreak();

    int numrows, numcols, numtowin;
    scanf(" %d", &numrows);
    scanf(" %d", &numcols);
    scanf(" %d", &numtowin);

    CursorTrackedWindow boardWindow = newCursorTrackedWindow(numrows, numcols, 0, 0);
    fillWindow(&boardWindow, '*');
    keypad(boardWindow.cursesWin, true);
    wrefresh(boardWindow.cursesWin);



    //make a board

    Board board = makeBoard(numrows, numcols,'*', numtowin);
    TurnType playerTurn = Player1;
    // pick a starting player
    while(!isGameOver(board)){
        //show them the state of the game
        //printBoard(board);
        //get a move from the user
        Move move = getValidMove(&board, playerTurn, &boardWindow);
        //place their move on the board
        placeMove(move, &board, &boardWindow);
        //change turn
        //playerTurn = (playerTurn + 1) % 2;
        playerTurn = playerTurn == Player1 ? Player2 : Player1;
    }

    delwin(boardWindow.cursesWin);
    endwin();
    //print the winning board
    printBoard(board);

    //declare who wins or a tie
    declareWinner(board, playerTurn);
    //clean up
    cleanUpBoard(&board);

    return 0;
}