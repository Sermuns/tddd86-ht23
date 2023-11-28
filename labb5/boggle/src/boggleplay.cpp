// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "lexicon.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle &boggle) {
    bool playerTurn = true;

    while (playerTurn) {
        boggle.printPlayerStats();
        boggle.printBoard();
        cout << "Type a word (or press Enter to end your turn):";

        //loop till the players gets the wrong answer
        string answer;
        getline(cin, answer);
        if (answer.length() < boggle.MIN_WORD_LENGTH) {
            cout << "Incorrect length a minimum of 4 letters is required" << endl;
            continue;
        }
        if (boggle.checkForWord(answer) && boggle.isValidWord(answer)) {
            boggle.insertGuess(answer);
        } else {
            cout << "Word not found" << endl;
            playerTurn = false;
        }

    }


    //Computer wins : D
    cout << "It's my turn :D" << endl;
    set<string> allWords = boggle.getAllPossibleWords();
    string connectedWords = "";
    for (string word: allWords) {
        connectedWords += word + ", ";
    }
    cout << "My words (" << allWords.size() << ") {" << connectedWords << "}" << endl;
    cout << "My score(" << boggle.getPoints(allWords) << ")" << endl;

    cout << "I won... most likely..." << endl;

}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
