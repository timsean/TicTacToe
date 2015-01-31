//
//  player.cpp
//  TicTacToe
//
//  Created by Tim on 1/17/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include "player.h"

Player::Player() {
    
}

Player::Player(char player, bool isHuman) {
    this->player = player;
    this->isHuman = isHuman;
}

char Player::getPlayerSymbol() {
    return player;
}