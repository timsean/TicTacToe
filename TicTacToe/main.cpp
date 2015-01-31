//
//  main.cpp
//  OpenGLModelLight
//
//  Created by Tim on 12/29/14.
//  Copyright (c) 2014 Tim. All rights reserved.
//

// Include standard headers
#include <stdio.h>
#include <iostream>

#include "solver.h"
#include "randomsolve.h"
#include "game.h"
#include "opengl.h"
#include "textdisp.h"

using namespace std;

Player p1;
Player p2;
Game game;
RandomSolver randomsolve;

void setupGame() {
    p1 = Player('O', false);
    p2 = Player('X', false);
    game = Game(3, p1, p2);
}

void playGame() {
    game.getBoard()->makeMove('O', randomsolve.getNextMove('O', game.getBoard()));
    //displayBoard(game.getBoard());
}

int main(void)
{
    //opengl();
    setupGame();
    while(game.getBoard()->isOngoing()) {
        playGame();
    }
    return 0;
}