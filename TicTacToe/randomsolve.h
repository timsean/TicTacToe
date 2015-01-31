//
//  randomsolve.h
//  TicTacToe
//
//  Created by Tim on 1/24/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__randomsolve__
#define __TicTacToe__randomsolve__

#include "solver.h"
#include "board.h"
#include <stdio.h>

class RandomSolver : public Solver {
public:
    RandomSolver();
    Move getNextMove(char, Board*);
};

#endif /* defined(__TicTacToe__randomsolve__) */