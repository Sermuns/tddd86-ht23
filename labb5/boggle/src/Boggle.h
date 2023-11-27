// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <set>
#include <string>
#include "lexicon.h"
#include "grid.h"

// TODO: include any other header files you need

using namespace std;


class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const unsigned MIN_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them

    Boggle();
    void fillWithJunk();
    void fillWithPlayerInput(string& input);
    bool checkForWord(string input);
    pair<int,int> checkForChar(char letter)const;
    map<pair<int,int>,char> getNeighbours(pair<int, int> coord) const;
    void printBoard() const;
    bool findWord(string input, pair<int, int> coord) const;
    void printPlayerStats();
    set<string> getAllPossibleWords() const;
    void continueWordFromCoordinate(pair<int,int> coord, string partialWord, vector<vector<bool>>& visitedCoords, set<string>& allWords) const;
    bool isAlreadyGuessed(const string& guess) const;
    void insertGuess(string& guess);
    bool isValidWord(string& word) const;
    int getPoints(set<string>& listOfWords);
private:
    // TODO: decide the private member variables/functions and declare them

    Grid<char> gameBoard;
    Lexicon lexicon;
    set<string> guessedWords;
};

#endif
