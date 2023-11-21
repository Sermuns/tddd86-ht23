// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include <map>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "random.h"
#include "shuffle.h"

using namespace std;

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

    for(int y = 0; y < BOARD_SIZE; y++){
         for(int x = 0; x < BOARD_SIZE; x++){
             char currentRandomChar = CUBES[index].at(randomInteger(0,(CUBE_SIDES - 1)));
             gameBoard.set(y,x, currentRandomChar);
             index++;

         }
    }
    shuffle(gameBoard);
}

void Boggle::fillWithPlayerInput(string& input){
    input = toUpperCase(input);
    int index =0;

    for(int y = 0; y < BOARD_SIZE; y++){
         for(int x = 0; x < BOARD_SIZE; x++){
             gameBoard.set(y,x, input.at(index));
             index++;
         }
    }
}

map<pair<int, int>, char> Boggle::getNeighbours(pair<int, int> coord) const{
    map<pair<int, int>, char> outMap;
    for(int y = coord.first-1; y < coord.first + 2; y++){
         for(int x = coord.second -1; x < coord.second +2; x++){
             if(y == coord.first && x == coord.second) continue;

             int clampedY = y;
             int clampedX = x;

             if(y < 0) clampedY += gameBoard.numRows();
             else if(y >= gameBoard.numRows()) clampedY -= gameBoard.numRows();
             if(x < 0) clampedX += gameBoard.numCols();
             else if(x >= gameBoard.numCols()) clampedX -= gameBoard.numCols();

             pair<int,int> coord{clampedY, clampedX};
             outMap[coord] = gameBoard.get(clampedY, clampedX);

         }
    }
    return outMap;
}

void Boggle::printBoard() const{
    for(int y = 0; y < BOARD_SIZE; y++){
         for(int x = 0; x < BOARD_SIZE; x++){
            cout << gameBoard.get(y, x);
         }
         cout << endl;
    }
}

void Boggle::printGuesses() const{
    for(auto& guess : guessedWords){
        cout << guess << ", ";
    }
    cout << endl;
}

void Boggle::checkForWord(string input){

    input = toUpperCase(input);
    pair<int,int> coords = checkForChar(input.at(0));

    // First characeter not in board!
    if(coords.first == -1)
    {
        std::cout << input.at(0) << " not found" << std::endl;
        return;
    }

    if(findWord(input, coords)){
        guessedWords.insert(input);
    }

}

bool Boggle::findWord(string input, pair<int, int> coord) const{

    if(input.length() == 0) return true;

    map<pair<int, int>, char> neighbours = getNeighbours(coord);

    char nextLetter = input.at(0);
    pair<int,int> coordOfNextLetter = {-1, -1}; // Assume NOT in neighbors

    for(const auto& pair : neighbours){
        if(pair.second == nextLetter){
            coordOfNextLetter = pair.first;
            break;
        }
    }

    if(coordOfNextLetter.first == -1) return false;

    return findWord(input.substr(1), coordOfNextLetter);
}



pair<int, int> Boggle::checkForChar(char letter) const{
    for(int y = 0; y < BOARD_SIZE; y++){
         for(int x = 0; x < BOARD_SIZE; x++){
            if(gameBoard.get(y,x) == letter)
                return {y,x};
         }
    }
    return {-1,-1};
}


// TODO: implement the members you declared in Boggle.h
