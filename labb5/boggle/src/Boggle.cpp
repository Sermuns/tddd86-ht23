// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include <map>
#include <vector>
#include <set>
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

Boggle::Boggle() {
    gameBoard = Grid<char>(BOARD_SIZE, BOARD_SIZE);
    lexicon.addWordsFromFile(DICTIONARY_FILE);

}

bool Boggle::isValidWord(string &word) const {
    return lexicon.contains(word) && word.length() >= MIN_WORD_LENGTH;
}

void Boggle::fillWithJunk() {
    int index = 0;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            char currentRandomChar = CUBES[index].at(randomInteger(0, (CUBE_SIDES - 1)));
            gameBoard.set(y, x, currentRandomChar);
            index++;
        }
    }
    shuffle(gameBoard);
}

void Boggle::fillWithPlayerInput( string &input) {
    cout << "Type the 16 letters to appear on the board:";
    getline(cin, input);

    bool invalidInput = true;
    while(invalidInput){
        for(const auto& chars: input)
        {
           if(!isalpha(chars)){
               invalidInput = true;
               cout << "Error: "<< "Invalid input, requires letters only" << endl;
               break;
           }
           else{
               invalidInput = false;
           }
        }

        if(input.length() != 16){
            cout <<  "Error: "<<"Invalid size on board, input:  " << input.length() << " required 16 chars" << endl;
            invalidInput = true;
        }

        if(invalidInput){
            cout << "Type the 16 letters to appear on the board: ";
            getline(cin, input);
        }


    }


    string upperInput = toUpperCase(input);
    int index = 0;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            gameBoard.set(y, x, upperInput.at(index));
            index++;
        }
    }
}

void Boggle::resetGame(){
    guessedWords.clear();
}

set<string> Boggle::getAllPossibleWords() const {
    // Gets all words for the computers turn

    set<string> allWords = {};
    vector<vector<bool>> visitedCoords(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            string word = "";
            continueWordFromCoordinate({y, x}, word, visitedCoords, allWords);
        }
    }

    return allWords;
}


set<string> Boggle::getGuessedWords() const{
    return guessedWords;
}

// A vector within a vector simulates a 2d grid.
void
Boggle::continueWordFromCoordinate(const pair<int, int> &coord, string partialWord, vector<vector<bool>> &visitedCoords,
                                   set<string> &allWords) const {


    //Current coord is visited
    visitedCoords[coord.first][coord.second] = true;

    char nextChar = gameBoard.get(coord.first, coord.second);
    partialWord += nextChar;

    if (isValidWord(partialWord) && !isAlreadyGuessed(partialWord)) {
        allWords.insert(partialWord);
    } else if (lexicon.containsPrefix(partialWord) == false) {
        partialWord.pop_back(); //remove latest insert.
        visitedCoords[coord.first][coord.second] = false; //unvisit coord
        return; //not valid
    }

    map<pair<int, int>, char> neighbours = getNeighbours(coord);
    for (const auto &entry: neighbours) {
        // Already visited NEXT Neighbor thanks!
        if (visitedCoords[entry.first.first][entry.first.second] == true) continue;

        continueWordFromCoordinate(entry.first, partialWord, visitedCoords, allWords);

    }

    partialWord.pop_back();
    visitedCoords[coord.first][coord.second] = false;

}

bool Boggle::isAlreadyGuessed(const string &guess) const {
    for (const auto &word: guessedWords) {
        if (guess == word) {
            return true;
        }
    }
    return false;
}

map<pair<int, int>, char> Boggle::getNeighbours(const pair<int, int> &coord) const {
    map<pair<int, int>, char> outMap;
    for (int y = coord.first - 1; y < coord.first + 2; y++) {
        for (int x = coord.second - 1; x < coord.second + 2; x++) {
            if (y == coord.first && x == coord.second) continue;

            if (y < 0 || y >= gameBoard.numRows() || x < 0 || x >= gameBoard.numCols()) continue;

            pair<int, int> coord{y, x};
            outMap[coord] = gameBoard.get(y, x);

        }
    }
    return outMap;
}


void Boggle::printBoard() const {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            cout << gameBoard.get(y, x);
        }
        cout << endl;
    }
}

void Boggle::insertGuess(const string &guess) {
    guessedWords.insert(guess);
}

void Boggle::printPlayerStats() const {
    string wordsConnected = "";
    int wordsAmount = guessedWords.size();
    for (const auto& guess: guessedWords) {
        wordsConnected += toUpperCase(guess) + ", ";
    }
    cout << "Your words (" << wordsAmount << "): {" << wordsConnected << "}" << endl;
    cout << "Your score (" << getPoints(guessedWords) << ")";
    cout << endl;
}

bool Boggle::checkForWord(const string& input) const {

    string upperInput = toUpperCase(input);
    pair<int, int> coords = checkForChar(upperInput.at(0));

    // First character not in board!
    if (coords.first == -1) {
        std::cout << upperInput.at(0) << " not found" << std::endl;
        return false;
    }

    if (findWord(upperInput, coords)) {
        return true;
    }
}

int Boggle::getPoints(const set<string> listOfWords) const {
    int totalPoints = 0;
    for (const auto &word: listOfWords)
        totalPoints += word.length() - 3;

    return totalPoints;
}

bool Boggle::findWord(basic_string<char> input, const pair<int, int> &coord) const {

    if (input.length() == 0) return true;

    map<pair<int, int>, char> neighbours = getNeighbours(coord);

    char nextLetter = input.at(0);
    pair<int, int> coordOfNextLetter = {-1, -1}; // Assume NOT in neighbors

    for (const auto &pair: neighbours) {
        if (pair.second == nextLetter) {
            coordOfNextLetter = pair.first;
            break;
        }
    }

    if (coordOfNextLetter.first == -1) return false;

    return findWord(input.substr(1), coordOfNextLetter);
}


pair<int, int> Boggle::checkForChar(const char letter) const {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (gameBoard.get(y, x) == letter)
                return {y, x};
        }
    }
    return {-1, -1};
}


// TODO: implement the members you declared in Boggle.h
