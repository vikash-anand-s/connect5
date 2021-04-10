//
//  GameManager.hpp
//  Connect5
//
//  Created by Vikash Anand on 09/04/21.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>

#define EMPTY 9
#define PLAYER1 1
#define PLAYER2 0
#define ROW_SIZE 7
#define COLUMN_SIZE 10
#define MIDDLE_LEFT 4
#define MIDDLE_RIGHT 5

void createMatrix(int[ROW_SIZE][COLUMN_SIZE]);
void printMatrix(int[ROW_SIZE][COLUMN_SIZE]);
bool hasWon(int[ROW_SIZE][COLUMN_SIZE]);
int getPlayerWon();
bool isTie(int[ROW_SIZE][COLUMN_SIZE]);
void placeValue(int matrix[ROW_SIZE][COLUMN_SIZE], int valueToPlace, int indexNo);
void startGame();

#endif /* GameManager_hpp */
