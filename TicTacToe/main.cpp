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

#include "game.h"
#include "opengl.h"
#include "textdisp.h"

using namespace std;

Player p1;
Player p2;
Game game;

void setupGame() {
    p1 = Player('O', false);
    p2 = Player('X', false);
    game = Game(3, p1, p2);
    displayBoard(game.getBoard());
}

int main(void)
{
    //opengl();
    setupGame();
    return 0;
}