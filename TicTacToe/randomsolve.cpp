//
//  randomsolve.cpp
//  TicTacToe
//
//  Created by Tim on 1/24/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include "randomsolve.h"
#include <stdlib.h>
#include <time.h>

RandomSolver::RandomSolver() {
    // Nothing to do;
}

Move RandomSolver::getNextMove(char player, Board *board) {
    Move move;
    vector<Move> openMoves = board->getOpenMoves();
    // Seed the random generator
    srand((int) time(NULL));
    move = openMoves[rand() % openMoves.size()];
    return move;
}