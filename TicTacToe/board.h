//
//  board.h
//  TicTacToe
//
//  Created by Tim on 1/17/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__board__
#define __TicTacToe__board__

#include <vector>
#include <stdio.h>
#include "boardsquare.h"
#include "move.h"

using namespace std;

class Board {
    short size; // Board size is size * size
    BoardSquare *board; // Array of board squares
    vector<short> openMoves; // Array keeping track of what moves are available
    short filled; // Number of squares filled
    bool hasWinner = false;
    char winner;
public:
    Board(short);
    bool isOngoing();
    vector<short> *getOpenMoves();
    void makeMove(char, Move);
    // Getters
    short getSize();
    BoardSquare getBoardSquare(short);
private:
    void calculateWinner(char, Move);
};

#endif /* defined(__TicTacToe__board__) */