//
//  move.cpp
//  TicTacToe
//
//  Created by Tim on 1/29/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include "move.h"

Move::Move() {
    // Do nothing
}

Move::Move(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Move::operator== (const Move &move2) {
    return x == move2.x && y == move2.y;
}

void Move::operator= (const Move &move2) {
    x = move2.x;
    y = move2.y;
}