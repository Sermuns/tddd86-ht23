#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

unordered_set<string> getAllWords() {
    unordered_set<string> allWords;
    ifstream dictionary("dictionary.txt");
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
map<string, unordered_set<string >> createWordFamilyMap(const unordered_set<string> &currentWords, char guessedLetter) {
    map<string, unordered_set<string>> wordFamilies;
    for (const auto &word: currentWords) {
        string pattern = word;
        // add '-' where unknown letter
        for (char &letter: pattern) {
            if (letter != guessedLetter) {
                letter = '-';
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


void removeSmallFamilies(map<string, unordered_set<string>> &wordFamilies){
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
    const int maxWordLength = getMaxWordLength();
    while(incorrect){
        cout << "Input desired word length: ";
        string line;
        getline(cin, line);
        wordLength = stoi(line);
        if (wordLength <= maxWordLength) {
            incorrect = false;
        }
    }
    cout << "Input the amount of guesses you want that is larger than 0: ";
    int guessAmount;
    cin >> guessAmount;
    cout << "Want a hint??? (yes/no)" << endl;
    unordered_set<string> correctLengthWords = getWordsOfDesiredLength(wordLength);
    string answer = "yes";
    if (answer == "yes") {
        cout << "The amount of words that are left: " << correctLengthWords.size() << endl;
    }

    unordered_set<char> guessedCharacters;
    while(true){
        cout << "Guesses left: " << guessAmount << endl;

        cout << "Guess a letter! " <<  endl;
        char letter;
        cin >> letter;
        guessedCharacters.insert(letter);
    }
    return 0;
}
