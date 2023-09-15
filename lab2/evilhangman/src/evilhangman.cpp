/* The game of evilhangman where the computer tries to find the hardest to guess word and constantly changing it based on user input.
 * made by Daniel Alchasov(Danal315) Samuel Åkesson(Samak519).
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";


/**
 * @brief getAllWords, gets all word in given .txt file
 * @return an unordered set of strings with all words.
 */
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



/**
 * @brief getMaxWordLength loops through all words in dictionary and finds the longest
 * @return longest words .length()
 */
int getMaxWordLength(const unordered_set<string> &allWords) {
    int maxLength = 0;
    for (const auto &word: allWords) {
        int wordLength = word.length();
        if (wordLength > maxLength) {
            maxLength = wordLength;
        }
    }
    return maxLength;
}
/**
 * @brief getWordsOfDesiredLength gets a unordered set of all words that match the users preferred word length;
 * @param length
 * @return the wanted unordered set of words desired length.
 */
unordered_set<string> getWordsOfDesiredLength(const int length, const unordered_set<string> &allWords) {
    unordered_set<string> words;
    for (const auto &word: allWords) {
        if (static_cast<int>(word.length()) == length) {
            words.insert(word);
        }
    }
    return words;
}
/**
 * @brief updateLargestpair gets the largest word family by making a map of all possible word families and keeping the largest.
 * @param guessedLetter
 * @param largestPair
 */
void updateLargestpair(char guessedLetter, pair<string, unordered_set<string>> &largestPair){
    unordered_map<string, unordered_set<string>> wordFamilies;
    for(const auto& word: largestPair.second){
        string pattern = word;
        for(unsigned int i= 0;i<word.size(); i++){
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
/**
 * @brief userInputs gets the needed user input in a function.
 * @param guessesAllowed
 * @param wordLength
 * @param hint
 */
void userInputs(int &guessesAllowed, int& wordLength, bool &hint, const unordered_set<string> &allWords){
    cout << "Please input the desired word length under " << getMaxWordLength(allWords) << " : ";
    cin >> wordLength;
    while(getWordsOfDesiredLength(wordLength, allWords).size() <= 0){
        cout << "No words of that length exist, input another: ";
        cin >> wordLength;
    }
    cout << "Please input the amount of guesses you wish to have: ";
    cin >> guessesAllowed;
    string answer;
    cout << "Continue with hints (y/n)? ";
    cin >> answer;

    hint = answer.at(0) == 'y';

}
/**
 * @brief alreadyGuessed checks if the latest letteer has already been guessed giving the headups to the main function on what to do.
 * @param guessedCharacters
 * @param latestLetter
 * @return bool based on if word existed or not.
 */
bool alreadyGuessed(vector<char> &guessedCharacters, char latestLetter){
    for(const auto& letter : guessedCharacters){
       if(letter == latestLetter){
           return true;
       }
    }
    return false;

}
/**
 * @brief checkIfLetter checks if the input is a letter and not a string of random inputs.
 * @param input
 */
void checkIfLetter(string &input){

    while(!(ALPHABET.find(input.at(0)) != string::npos) || input.size() > 1){
         cout << "Invalid input try again: ";
         cin >> input;
    }
}
/**
 * @brief main holds all the function calls and order of program.
 * @return
 */
int main() {

    const bool CHEAT = false;


    int guessAmount;
    int desiredLength;
    bool hint;
    const unordered_set<string> allWords = getAllWords();
    bool playing = true;

    while(playing){
        hint = false;
        userInputs(guessAmount, desiredLength, hint, allWords);

        vector<char> guessedLetters;
        const unordered_set<string> possibleWords = getWordsOfDesiredLength(desiredLength, allWords);
        const string firstPattern(desiredLength, '-');
        pair<string, unordered_set<string>> largestPair(firstPattern, possibleWords);

        while(guessAmount > 0){
            cout << "guess a letter!";

            string input;
            cin >> input;
            checkIfLetter(input);
            //if there are now more than 2 instances of letter then another guess is needed
            while(alreadyGuessed(guessedLetters, input.at(0))){
                cout << "Already guessed this letter: " << input << endl;
                cout << "Guess again: ";
                cin >> input;
                checkIfLetter(input);
            }
            char letter = input.at(0);

            guessedLetters.insert(guessedLetters.end(),letter);

            cout << "current guess: " << input << endl;
            updateLargestpair(letter, largestPair);
            if(hint){
                cout << largestPair.first << " " << largestPair.second.size() << endl;
            }
            else{
                cout << largestPair.first << endl;
            }

            if(CHEAT){
                for(const auto& letter : ALPHABET){
                    updateLargestpair(letter, largestPair);
                    cout << largestPair.first << " " << largestPair.second.size() << endl;
                }
            }


            if(largestPair.first.find('-') == string::npos){
                cout << "U WON BRO" << endl;
                cout << "Want to continue playing (y/n): ";
                string line;
                cin >> line;
                playing = line.at(0) == 'y';
                break;
            }
            guessAmount--;
        }
        if(guessAmount == 0){
            cout << "You lost, couldn't guess the word in given guesses... " << endl;
            cout << "Want to continue playing (y/n): ";
            string line;
            cin >> line;
            playing = line.at(0) == 'y';
        }
    }



    return 0;
}
