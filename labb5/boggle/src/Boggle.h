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

using namespace std;


class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const unsigned MIN_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 4;

    Boggle();

    /*
    * Method: fillWithJunk
    * Usage: boggle.fillWithJunk();
    * ---------------------
    * fills the grid with randomized characters.
    */
    void fillWithJunk();
    /*
    * Method: fillWithPlayerInput
    * Usage: boggle.fillWithPlayerInput(string of 16 chars);
    * ---------------------
    * fills the grid with user input by taking in 16 characters.
    */
    void fillWithPlayerInput(const string& input);
    /*
    * Method: checkForWord
    * Usage: boggle.checkForWord(word);
    * ---------------------
    * checks if it is possible to find input in the board. Returns a bool if it does exist
    */
    bool checkForWord(const string& input) const;
    /*
    * Method: checkForChar
    * Usage: boggle.checkForChar(char);
    * ---------------------
    * checks if the an char exist on board and returns its coords. 
    */
    pair<int,int> checkForChar(char letter) const;
    /*
    * Method: getNeighbours
    * Usage: boggle.getNeighbours(pair<int, int> coord));
    * ---------------------
    * returns all the letter neighbours in form of a map with coords as its key. 
    */
    map<pair<int,int>,char> getNeighbours(const pair<int, int>& coord) const;
    /*
    * Method: printBoard
    * Usage: boggle.printBoard());
    * ---------------------
    * prints the 2d grid.
    */
    void printBoard() const;
    /*
    * Method: findWord
    * Usage: boggle.findWord(string input, pair<int, int> coord);
    * ---------------------
    * returns true if it could find input as a word. recursively goes through the grid to find if word exists.
    */
    bool findWord(basic_string<char> input, const pair<int, int>& coord) const;
    /*
    * Method: printPlayerStats
    * Usage: boggle.printPlayerStats();
    * ---------------------
    * prints the players score and each of its guessed word in correct format. 
    */
    void printPlayerStats() const;
    /*
    * Method: getAllPossibleWords
    * Usage: boggle.getAllPossibleWords();
    * ---------------------
    * gets all possible words by starting a recursion loop by calling getAllPossibleWords for all coordinates as start points. 
    */
    set<string> getAllPossibleWords() const;
    /*
    * Method: continueWordFromCoordinate
    * Usage: boggle.continueWordFromCoordinate(pair<int,int> coord, string partialWord, vector<vector<bool>>& visitedCoords, set<string>& allWords);
    * ---------------------
    * Recursive backtracking to find all possible words and inserts it into a set.  
    */
    void continueWordFromCoordinate(const pair<int,int>& coord, string partialWord, vector<vector<bool>>& visitedCoords, set<string>& allWords) const;
    /*
    * Method: isAlreadyGuessed
    * Usage: boggle.isAlreadyGuessed(string guess);
    * ---------------------
    * checks if input is already in the private member gussedWords if so returns true or false.  
    */
    bool isAlreadyGuessed(const string& guess) const;
    /*
    * Method: insertGuess
    * Usage: boggle.insertGuess(string guess);
    * ---------------------
    * tries to insert a word into the private member guessed words
    */
    void insertGuess(const string& guess);
     /*
    * Method: isValidWord
    * Usage: boggle.isValidWord(string guess);
    * ---------------------
    * checks if word follows the boggle rules and is a real word. Returns true if it is otherwise false. 
    */
    bool isValidWord(string& word) const;
    /*
    * Method: getPoints
    * Usage: boggle.getPoints(set<string> listOfWords);
    * ---------------------
    * calculates the points from a list of words following the rules of boggle.
    */
    int getPoints(set<string> listOfWords) const;
private:

    Grid<char> gameBoard;
    Lexicon lexicon;
    set<string> guessedWords;
};

#endif
