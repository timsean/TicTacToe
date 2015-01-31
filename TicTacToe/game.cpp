//
//  game.cpp
//  TicTacToe
//
//  Created by Tim on 1/23/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include "board.h"
#include "player.h"
#include "aiminimax.h"
#include "textdisp.h"
#include "game.h"

Game::Game() {
    //Nothing here
}

Game::Game(short size, Player player1, Player player2) {
    board = Board(size);
    this->player1 = player1;
    this->player2 = player2;
}

Board Game::getBoard() {
    return board;
}