//
//  player.h
//  TicTacToe
//
//  Created by Tim on 1/17/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__player__
#define __TicTacToe__player__

#include <stdio.h>

class Player {
    char player;
    bool isHuman;
public:
    Player(); // Default constructor
    Player(char, bool);
    char getPlayerSymbol();
};

#endif /* defined(__TicTacToe__player__) */