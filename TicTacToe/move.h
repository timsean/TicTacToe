//
//  move.h
//  TicTacToe
//
//  Created by Tim on 1/29/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__move__
#define __TicTacToe__move__

#include <stdio.h>

class Move {
public:
    int x, y;
    Move();
    Move(int, int);
};

#endif /* defined(__TicTacToe__move__) */