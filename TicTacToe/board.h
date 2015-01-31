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
    vector<BoardSquare> board; // Array of board squares
    vector<Move> openMoves; // Array keeping track of what moves are available
    short filled; // Number of squares filled
    bool hasWinner = false;
    char winner;
public:
    Board(short);
    bool isOngoing();
    vector<Move> getOpenMoves();
    void makeMove(char, Move);
    // Getters
    short getSize();
    BoardSquare getBoardSquare(int);
private:
    void calculateWinner(char, Move);
};

#endif /* defined(__TicTacToe__board__) */