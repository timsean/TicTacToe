//
//  boardsquare.h
//  TicTacToe
//
//  Created by Tim on 1/19/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__boardsquare__
#define __TicTacToe__boardsquare__

#include <stdio.h>

class BoardSquare {
    char player = ' ';
    bool occupied = false;
public:
    BoardSquare();
    BoardSquare(char);
    void setPlayer(char);
    bool isOccupied();
    char getPlayer();
};

#endif /* defined(__TicTacToe__boardsquare__) */