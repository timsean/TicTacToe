//
//  solver.h
//  TicTacToe
//
//  Created by Tim on 1/20/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__solver__
#define __TicTacToe__solver__

#include "move.h"
#include "board.h"
#include <stdio.h>

class Solver {
public:
    virtual Move getNextMove(char, Board*) = 0;
};

#endif /* defined(__TicTacToe__solver__) */