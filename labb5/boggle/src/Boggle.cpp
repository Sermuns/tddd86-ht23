// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "random.h"
#include "shuffle.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = { // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle(){
    gameBoard = Grid<char>(BOARD_SIZE, BOARD_SIZE);
    fillWithJunk();
}

void Boggle::fillWithJunk(){
    int index =0
            ;

    for(int i = 0; i < BOARD_SIZE; i++){
         for(int j = 0; j < BOARD_SIZE; j++){
             char currentRandomChar = CUBES[index].at(randomInteger(0,(CUBE_SIDES - 1)));
             gameBoard.set(i,j, currentRandomChar);
             index++;

         }
    }
    shuffle(gameBoard);
}

void Boggle::fillWithPlayerInput(string& input){
    input = toUpperCase(input);
    int index =0;

    for(int i = 0; i < BOARD_SIZE; i++){
         for(int j = 0; j < BOARD_SIZE; j++){
             gameBoard.set(i,j, input.at(index));
             index++;

         }
    }
}

void Boggle::getNeighbours(pair<int, int> coord) const{
    string allLetters =  "";
    for(int i = coord.first-1; i < coord.first + 2; i++){
         for(int j = coord.second -1; j < coord.second +2; j++){
             if(i != coord.first && j != coord.second)
              {
             int clampedI = i;
             int clampedJ = j;
             if(i < 0) clampedI += gameBoard.numCols();
             else if(i >= gameBoard.numCols()) clampedI -= gameBoard.numCols();
             if(j < 0) clampedJ += gameBoard.numRows();
             else if(j >= gameBoard.numRows()) clampedJ -= gameBoard.numRows();

             allLetters += gameBoard.get(clampedI,clampedJ);
             }

         }
    }
    std::cout << allLetters << std::endl;
}

void Boggle::checkForWord(string input) const{
    input = toUpperCase(input);
    pair<int,int> coords = checkForChar(input.at(0));
    if(coords.first == -1)
        return;

    getNeighbours(coords);

}

pair<int, int> Boggle::checkForChar(char letter) const{
    for(int i = 0; i < BOARD_SIZE; i++){
         for(int j = 0; j < BOARD_SIZE; j++){
            if(gameBoard.get(i,j) == letter)
                return {i,j};
         }
    }
    return {-1,-1};
}


// TODO: implement the members you declared in Boggle.h
