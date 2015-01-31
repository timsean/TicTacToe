//
//  boardsquare.cpp
//  TicTacToe
//
//  Created by Tim on 1/19/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include "boardsquare.h"

BoardSquare::BoardSquare() {
    this->player = ' '; // No player
}

BoardSquare::BoardSquare(char player) {
    this->player = player;
    this->occupied = true;
}

void BoardSquare::setPlayer(char player) {
    this->player = player;
    this->occupied = true;
}

bool BoardSquare::isOccupied() {
    return occupied;
}

char BoardSquare::getPlayer() {
    return player;
}