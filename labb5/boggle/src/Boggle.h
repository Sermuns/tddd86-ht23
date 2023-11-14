// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"

// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them

    Boggle();
    void fillWithJunk();
    void fillWithPlayerInput(string& input);
    void checkForWord(string input) const;
    pair<int,int> checkForChar(char letter)const;
    void getNeighbours(pair<int, int> coord) const;

private:
    // TODO: decide the private member variables/functions and declare them

    Grid<char> gameBoard;

};

#endif
