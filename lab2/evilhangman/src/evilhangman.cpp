#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

unordered_set<string> getAllWords(){
    unordered_set<string> allWords;
    ifstream dictionary("dictionary.txt");
    string line;
    while(getline(dictionary, line)){
        allWords.insert(line);
    }
    dictionary.close();
    return allWords;
}

const unordered_set<string> allWords = getAllWords();

int getMaxWordLength(){
    int maxLength = 0;
    for(const auto& word: allWords){
        int wordLength = static_cast<int>(word.length());
        if(wordLength > maxLength){
            maxLength = wordLength;
        }
    }
    return maxLength;
}

unordered_set<string> getWordsOfDesiredLength(const int length){
    unordered_set<string> words;
    for(const auto& word: allWords){
        if(static_cast<int>(word.length()) == length){
            words.insert(word);
        }
    }
    return words;
}

unordered_set<string> getWordsWithoutLetters(const unordered_set<string> &words, const unordered_set<char> &letters){
    unordered_set<string> filtered;
    for(const auto& word: words){
        for(const auto& letter: letters){
            // checks if current letter does exist in word!
            if(word.find(letter) != string::npos){
                filtered.insert(word);
            }
        }
    }
    return filtered;
}

unordered_set<string> returnPossibleAnswers(const unordered_set<string> &possibleWords, const unordered_set<char> &currentGuesses){
    unordered_set<string> currentPossibleAnswers = getWordsWithoutLetters(possibleWords, currentGuesses);
    if(currentPossibleAnswers.size() <= 0){
        //oopsie

    }
    return currentPossibleAnswers;
}
int main() {
    cout << "Welcome to Hangman." << endl;
    bool incorrect = true; // reversed logical boolean.
    int wordLength;
    const int maxWordLength = getMaxWordLength();
    while(incorrect){
        cout << "Input desired word length: ";
        string line;
        getline(cin, line);
        wordLength = stoi(line);
        if(wordLength <= maxWordLength)
        {
            incorrect = false;
        }
    }
    cout << "Input the amount of guesses you want that is larger than 0: ";
    int guessAmount;
    cin >> guessAmount;
    cout << "Want a hint??? (yes/no)" << endl;
    unordered_set<string> correctLengthWords = getWordsOfDesiredLength(wordLength);
    string answer = "yes";
    if(answer == "yes"){
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
