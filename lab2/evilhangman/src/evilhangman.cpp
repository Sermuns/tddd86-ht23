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


int main() {
    cout << "Welcome to Hangman." << endl;

    bool incorrect = true;
    int wordLength;
    while(incorrect){
        cout << "Mata in ordlängd: ";
        string line;
        getline(cin, line);
        wordLength = stoi(line);
        if(allWords.siz
    }

    return 0;
}
