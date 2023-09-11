#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <map>

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

unordered_set<string> getAllWords() {
    unordered_set<string> allWords;
    ifstream dictionary("lab2/evilhangman/res/di.txt");
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

/**
 * Returns a filtered copy of input words which doesn't contain any of the chars in input letters
 * @param words words to be filtererd
 * @param letters letters that aren't allowed
 * @return
 */
unordered_set<string> getWordsWithoutLetters(const unordered_set<string> &words, const unordered_set<char> &letters) {
    unordered_set<string> filtered;
    for (const auto &word: words) {
        for (const auto &letter: letters) {
            // checks if current letter does exist in word!
            if (word.find(letter) != string::npos) {
                filtered.insert(word);
            }
        }
    }
    return filtered;
}


/**
 * Takes a wordFamilies map and limits it based on input letter
 * @param wordFamilies
 * @param guessedLetter
 */
unordered_map<string, unordered_set<string >> createWordFamilyMap(const unordered_set<string> &currentWords, list<char> &guessedCharacters) {
    unordered_map<string, unordered_set<string>> wordFamilies;
    char guessedLetter = guessedCharacters.front();
    for (const auto &word: currentWords) {
        string pattern = word;
        // add '-' where unknown letter
        for (int i= 0; i < pattern.size(); i++) {
            bool found = false;
            for(char &guessedChar : guessedCharacters){
                if(pattern[i] == guessedChar){
                    found = true;
                    break;
                }
            }
            if(!found){
                pattern[i] = '-';
            }
        }

        // if pattern already exists as key!
        if (wordFamilies.count(pattern) > 0) {
            wordFamilies[pattern].insert(word);
        }
        // if key needs to be created!
        else {
            wordFamilies[pattern] = unordered_set<string>({word});
        }
    }

    return wordFamilies;
}


void removeSmallFamilies(unordered_map<string, unordered_set<string>> &wordFamilies){
    int largestValueSize = 0;
    unordered_set<string> largestValue;
    string largestKey;
    unordered_set<string> currValue;
    for(const auto& pair : wordFamilies){
        currValue = pair.second;
        int valueSize = static_cast<int>(currValue.size());
        if(valueSize > largestValueSize) {
            largestValueSize = valueSize;
            largestKey = pair.first;
            largestValue = pair.second;
        }
    }
    wordFamilies.clear();
    wordFamilies[largestKey] =  (largestValue);
}


void printWelcomeMessages(const int maxWordLength, unordered_set<string> &correctLengthWords) {
    cout << "Welcome to Hangman." << endl;
    bool incorrect = true; // reversed logical boolean.
    int wordLength;
    while (incorrect) {
        cout << "Input desired word length: ";
        string line;
        getline(cin, line);
        wordLength = stoi(line);
        if (wordLength <= maxWordLength) {
            incorrect = false;
        }
    }

    correctLengthWords = getWordsOfDesiredLength(wordLength);

    cout << "Input the amount of guesses you want that is larger than 0: ";
    int guessAmount;
    cin >> guessAmount;
    cout << "Want a hint??? (yes/no)" << endl;
    string answer = "yes";
    if (answer == "yes") {
        cout << "The amount of words that are left: " << correctLengthWords.size() << endl;
    }
}

bool useHint = false;

int main() {
    const int maxWordLength = getMaxWordLength();
    unordered_set<string> possibleWords;

    printWelcomeMessages(maxWordLength, possibleWords);

    list<char> guessedCharacters;
    unordered_map<string, unordered_set<string>> wordFamilies;
    while (true) {
        cout << "Guess now: " << endl;
        char letter;
        cin >> letter;

        guessedCharacters.insert(letter);
        wordFamilies = createWordFamilyMap(correctLengthWords, letter);

        removeSmallFamilies(wordFamilies);
        modifyPossibleWords(possibleWords, guessedCharacters);

        for(const auto& stuff : wordFamilies){
            cout << stuff.first << " ||| " << (stuff.second.size()) << endl;
        }
    }
    return 0;
}
