#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

unordered_set<string> getAllWords() {
    unordered_set<string> allWords;
    ifstream dictionary("evilhangman/res/dictionary.txt");
    string line;
    while (getline(dictionary, line)) {
        allWords.insert(line);
    }
    dictionary.close();
    return allWords;
}

const unordered_set<string> allWords = getAllWords();

int getMaxWordLength() {
    int maxLength = 0;
    for (const auto &word: allWords) {
        int wordLength = static_cast<int>(word.length());
        if (wordLength > maxLength) {
            maxLength = wordLength;
        }
    }
    return maxLength;
}

unordered_set<string> getWordsOfDesiredLength(const int length) {
    unordered_set<string> words;
    for (const auto &word: allWords) {
        if (static_cast<int>(word.length()) == length) {
            words.insert(word);
        }
    }
    return words;
}

void createWordFamily(char guessedLetter, pair<string, unordered_set<string>> &largestPair){
    unordered_map<string, unordered_set<string>> wordFamilies;
    for(const auto& word: largestPair.second){
        string pattern = word;
        for(int i= 0;i<static_cast<int>(word.size()); i++){
            if(word.at(i) != guessedLetter && largestPair.first.at(i) == '-'){
                pattern[i] = '-';
            }
        }

        // key already exists
        if (wordFamilies.count(pattern) > 0) {
            wordFamilies[pattern].insert(word);
        }
        // key needs to be created!
        else {
            wordFamilies[pattern] = unordered_set<string>({word});
        }

    }
    pair<string, unordered_set<string>> largestWordFamily;
    for(const auto& pair : wordFamilies){
        if(pair.second.size() > largestWordFamily.second.size()){
            largestWordFamily = pair;
        }
    }
    largestPair = largestWordFamily;
}

void daFluff(int &guessesAllowed, int& wordLength, bool &hint){
    cout << "Please input the desired word length under " << getMaxWordLength() << " : ";
    cin >> wordLength;
    cout << "Please input the amount of guesses you wish to have: ";
    cin >> guessesAllowed;
    string tempAnswer;
    cout << "Continue with hints (y/n)? ";
    getline(cin, tempAnswer);

    if (tempAnswer == "y"){
        hint = true;
    }

    }

int main() {
    int guessAmount;
    int desiredLength;
    bool hint = false;
    bool game = true;
    daFluff(guessAmount, desiredLength, hint);
    unordered_set<char> guessedLetters;
    const unordered_set<string> possibleWords = getWordsOfDesiredLength(desiredLength);
    const string firstPattern(desiredLength, '-');
    pair<string, unordered_set<string>> largestPair(firstPattern, possibleWords);

    while(guessAmount > 0){
        cout << "guess a letter!";

        char letter;
        cin >> letter;
        guessedLetters.insert(letter);
        cout << guessedLetters.count(letter) << endl;
        //if there are now more than 2 instances of letter then another guess is needed
        for(int i = 1; i < guessedLetters.count(letter); i++ ){
            cout << "Already guessed this letter: " << letter << endl;
            cout << "Guess again: ";
            cin >> letter;
        }


        cout << "current guess: " << letter << endl;
        createWordFamily(letter, largestPair);
        if(hint){
            cout << largestPair.first << " " << largestPair.second.size() << endl;
        }
        else{
            cout << largestPair.first << endl;
        }

        if(largestPair.first.find('-') == string::npos){
            cout << "U WON BRO" << endl;
            break;
        }
        guessAmount--;
    }
    for(const auto& letter: ALPHABET){




//       for(const auto& worrrrrd : largestPair.second){
//           cout << worrrrrd << " ";
//       }
    }


    return 0;
}
