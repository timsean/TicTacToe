//
//  board.cpp
//  TicTacToe
//
//  Created by Tim on 1/17/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include <vector>
#include "boardsquare.h"
#include "move.h"
#include "board.h"

using namespace std;

Board::Board(short size) {
    this->size = size;
    this->board = new BoardSquare[size*size];
    this->openMoves = vector<short>(size*size);
    for(int i = 0; i < size*size; i++) {
        openMoves[i] = i;
    }
}

bool Board::isOngoing() {
    return filled != size*size && !hasWinner;
}

vector<short> *Board::getOpenMoves() {
    return &openMoves;
}

void Board::makeMove(char player, Move move) {
    short moveArrayIndex =move.y*size + move.x;
    // Make move
    if(board[moveArrayIndex].getPlayer() == ' ') {
        board[moveArrayIndex].setPlayer(player);
    } else {
        return;
    }
    // Remove move from list of open moves
    openMoves.erase(openMoves.begin() + moveArrayIndex-1);
    // Increase board fullness counter
    filled++;
    // Check if the game has been won
    calculateWinner(player, move);
}

short Board::getSize() {
    return size;
}

BoardSquare Board::getBoardSquare(short position) {
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
    if(move.x == move.y || move.x + move.y + 1 == size) {
        for(int i = 0; i < size; i++) {
            if(board[i*size + i].getPlayer() != player) {
                win = false;
                break;
            }
        }
        
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