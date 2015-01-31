//
//  textdisp.cpp
//  TicTacToe
//
//  Created by Tim on 1/23/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include <iostream>
#include "board.h"
#include "textdisp.h"

using namespace std;

void displayBoard(Board *board) {
    // draw the board in command line
    short size = board->getSize();
    for(int row = 0; row < size; row++) {
        for(int a = 0; a < size*2+1; a++) {
            cout << "-";
        }
        cout << endl;
        for(int col = 0; col < size; col++) {
            cout << "|";
            cout << board->getBoardSquare(row*size+col).getPlayer();
        }
        cout << "|" << endl;
    }
    for(int a = 0; a < size*2+1; a++) {
        cout << "-";
    }
    cout << endl;
}