//
//  game.h
//  TicTacToe
//
//  Created by Tim on 1/23/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __TicTacToe__game__
#define __TicTacToe__game__

#include <stdio.h>
#include "board.h"
#include "player.h"

class Game {
    Board board = Board(1);
    Player player1 = Player('O', false);
    Player player2 = Player('X', false);
public:
    Game(); //Default constructor
    Game(short, Player, Player);
    Board getBoard();
};

#endif /* defined(__TicTacToe__game__) */
