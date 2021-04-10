//
//  GameManager.cpp
//  Connect5
//
//  Created by Vikash Anand on 09/04/21.
//

#include "GameManager.hpp"
#include <iostream>
#include <sstream>
#include <ctype.h>

using namespace std;

int playerWon = 1;


//Get the value to be placed in the current turn
int turnCounter = 0;
int getTurn(){
    if(turnCounter % 2 != 0)
        return PLAYER1;
    else
        return PLAYER2;
}


void createMatrix(int matrix[ROW_SIZE][COLUMN_SIZE]){
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
            matrix[i][j] = EMPTY;
        }
    }
}

//Print the matrix
void printMatrix(int matrix[ROW_SIZE][COLUMN_SIZE]){
    system("clear");
    
    for(int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COLUMN_SIZE; j++){
            if (matrix[i][j] == EMPTY){
                cout << "-" << "  ";
            }else{
                cout << matrix[i][j] << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 1; i < 10; i++){
        cout << i << "  ";
    }
    cout << 0;
    if (!hasWon(matrix))
        cout << "\n\nPlayer '" << getTurn() << "',\nEnter a number[0-9] to make your move: ";
}

//Check if player has won
bool hasWon(int matrix[ROW_SIZE][COLUMN_SIZE]){
    bool hasWon = false;
    
    //Check if either player has won
    //Checking for lower matrix positions -- [1]
    for(int i = (ROW_SIZE - 1); i >= 4; i--){
        for(int j = 0; j < COLUMN_SIZE; j++){
            if (matrix[i][j] != EMPTY){
                int value = matrix[i][j];
                if(matrix[i-1][j] == value && matrix[i-2][j] == value && matrix[i-3][j] == value && matrix[i-4][j] == value){
                    hasWon = true;
                    playerWon = value;
                    break;
                }
                
                //Check left Diagonal Connect
                if(j >= 4 && hasWon == false){
                    if(matrix[i-1][j-1] == value && matrix[i-2][j-2] == value && matrix[i-3][j-3] == value && matrix[i-4][j-4] == value){
                        hasWon = true;
                        playerWon = value;
                        break;
                    }
                }
                if(COLUMN_SIZE - j >= 5 && hasWon == false){
                    //Check Horizntal Connect
                    if(matrix[i][j+1] == value && matrix[i][j+2] == value && matrix[i][j+3] == value && matrix[i][j+4] == value){
                        hasWon = true;
                        playerWon = value;
                        break;
                    }
                    //Check right Diagonal Connect
                    else if(matrix[i-1][j+1] == value && matrix[i-2][j+2] == value && matrix[i-3][j+3] == value && matrix[i-4][j+4] == value){
                        hasWon = true;
                        playerWon = value;
                        break;
                    }
            }
            }
        }
    }
    if (!hasWon){
        int counter = 0; // Counts the number of holes with the same value
        //Check the upper matrix positions -- [2]
        for(int i = 0; i < 4; i++){
            counter = 0;
            //left column of [2]
            if(matrix[i][MIDDLE_LEFT] != EMPTY){
                int value = matrix[i][MIDDLE_LEFT];
                //Left side of left column
                for(int j = MIDDLE_LEFT; j>=0; j--){
                    if(matrix[i][j] == value){
                        counter++;
                    }
                    else
                        break;
                }
                //Check if player has already won
                if (counter >= 5){
                    hasWon = true;
                    break;
                    
                    //Right side of left column
                    for(int j = MIDDLE_LEFT; j<COLUMN_SIZE; j++){
                        if(matrix[i][j] == value){
                            counter++;
                        }
                        else
                            break;
                    }
                }
            }
                //Check if player has already won
                if (counter >= 5){
                    hasWon = true;
                    break;
                }
            
            //Right column of [2]
            if(matrix[i][MIDDLE_RIGHT] != EMPTY){
                int value = matrix[i][MIDDLE_RIGHT];
                //Left side of left column
                for(int j = MIDDLE_RIGHT; j>=0; j--){
                    if(matrix[i][j] == value){
                        counter++;
                    }
                    else
                        break;
                }
                //Check if player has already won
                if (counter >= 5){
                    hasWon = true;
                    break;
                    
                    //Right side of left column
                    for(int j = MIDDLE_RIGHT; j<COLUMN_SIZE; j++){
                        if(matrix[i][j] == value){
                            counter++;
                        }
                        else
                            break;
                    }
                }
            }
        }
        
    }
    
    return hasWon;
}

//Return the player who has won the game.
int getPlayerWon(){
    return playerWon;
}

//Check if the game has ended in a tie.
bool isTie(int matrix[ROW_SIZE][COLUMN_SIZE]){
    bool istie = false;
    int numberOfEmptyHoles = 0;
    
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COLUMN_SIZE; j++)
        if(matrix[i][j] == EMPTY)
            numberOfEmptyHoles++;
    }
    
    if (numberOfEmptyHoles == 0)
        istie = true;
    
    return istie;
}

//Position the appropriate values into the matrix holes
void placeValue(int matrix[ROW_SIZE][COLUMN_SIZE], int valueToPlace, int indexNo){
    turnCounter++;
    for(int i = ROW_SIZE - 1; i >= 0; i--){
        if (indexNo == -1)
            indexNo = COLUMN_SIZE - 1;
        if(matrix[i][indexNo] == EMPTY){
            matrix[i][indexNo] = valueToPlace;
            break;
        }
    }
}

//Control the functions of the actual game
void startGame(){
    int matrix[ROW_SIZE][COLUMN_SIZE];
    createMatrix(matrix);
    printMatrix(matrix);
    
    
    char number;
    bool winstatus = hasWon(matrix);
    while(!winstatus){
        int numberIndexValue = 0;
        cin >> number;
        cin.clear();
        fflush(stdin);
        while(!isdigit(number)){
            printMatrix(matrix);
            cin >> number;
            cin.clear();
            fflush(stdin);
            numberIndexValue = (int)number - 48;
        }
        
        numberIndexValue = (int)number - 48;
            
        placeValue(matrix, getTurn(), numberIndexValue - 1);
        
        //Check win status
        winstatus = hasWon(matrix);
        printMatrix(matrix);
        if (winstatus){
            if(playerWon == PLAYER1)
                cout << "\nPlayer '1' has Won\n";
            else{
                cout << "\nPlayer '0' has won\n";
            }
        }
            
        //cout << "Status:" << winstatus;
    }
}
