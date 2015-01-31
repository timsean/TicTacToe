//
//  board.cpp
//  TicTacToe
//
//  Created by Tim on 1/17/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include "boardsquare.h"
#include "move.h"
#include "textdisp.h"
#include "board.h"

using namespace std;

Board::Board(short size) {
    this->size = size;
    this->board = vector<BoardSquare>(size*size);
    this->openMoves = vector<Move>(size*size);
    for(int y = 0; y < size; y++) {
        for(int x = 0; x < size; x++) {
            openMoves[y*size+x] = Move(x,y);
        }
    }
}

bool Board::isOngoing() {
    return filled != size*size && !hasWinner;
}

vector<Move> Board::getOpenMoves() {
    return openMoves;
}

void Board::makeMove(char player, Move move) {
    cout << move.x << " " << move.y << endl;
    int moveArrayIndex =move.y*size + move.x;
    // Make move
    if(board[moveArrayIndex].getPlayer() == ' ') {
        board[moveArrayIndex].setPlayer(player);
    } else {
        return;
    }
    // Remove move from list of open moves
    openMoves.erase(find(openMoves.begin(), openMoves.end(), move));
    // Increase board fullness counter
    filled++;
    // Check if the game has been won
    calculateWinner(player, move);
    displayBoard(this);
}

short Board::getSize() {
    return size;
}

BoardSquare Board::getBoardSquare(int position) {
    return board[position];
}

void Board::calculateWinner(char player, Move move) {
    bool win = true;
    // Check column
    for(int i = 0; i < size; i++) {
        if(board[i*size + move.x].getPlayer() != player) {
            win = false;
            break;
        }
    }
    
    if(win) {
        hasWinner = true;
        winner = player;
        return;
    }
    
    win = true;
    
    // Check horizontal
    for(int i = 0; i < size; i++) {
        if(board[move.y*size + i].getPlayer() != player) {
            win = false;
            break;
        }
    }
    
    if(win) {
        hasWinner = true;
        winner = player;
        return;
    }
    
    // Check diagonal if move was placed on diagonal
    if(move.x == move.y) {
        win = true;
        for(int i = 0; i < size; i++) {
            if(board[i*size + i].getPlayer() != player) {
                win = false;
                break;
            }
        }
    }
    
    if(win) {
        hasWinner = true;
        winner = player;
        return;
    }
    
    if(move.x + move.y + 1 == size) {
        win = true;
        for(int i = 0; i < size; i++) {
            if(board[i*size + size-i-1].getPlayer() != player) {
                win = false;
                break;
            }
        }
    }
    
    if(win) {
        hasWinner = true;
        winner = player;
        return;
    }
}