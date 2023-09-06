#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;


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
const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


bool isValidWord(const string &word){
    return allWords.count(word) > 0;
}

queue<string> getNeighbors(const string &word){
    queue<string> validNeighbors;
    string potentialNeighbor;
    for(int i = 0; i < static_cast<int>(word.length()); i++){
        for(int j = 0; j < static_cast<int>(ALPHABET.length()); j++){
            potentialNeighbor = word;
            char letter = ALPHABET.at(j);
            potentialNeighbor[i] = letter;
            if(isValidWord(potentialNeighbor) && !(potentialNeighbor == word)){
                validNeighbors.push(potentialNeighbor);
            }
        }
    }
    return validNeighbors;
}

void wordChain(const string &wordOne, const string &wordTwo){
    // init empty queue of stacks
    queue<stack<string>> potentialChains;
    // add a queue consisting of wordOne
    potentialChains.push(stack<string>({wordOne}));

    unordered_set<string> usedWords;

    while(!potentialChains.empty()){
        stack<string> chain = potentialChains.front();
        string topWord = chain.top();
        potentialChains.pop();

        // CORRECT CHAIN FOUND!
        if(topWord == wordTwo){
            while(!chain.empty()){
                cout << chain.top() << ' ';
                chain.pop();
            }
            cout << endl;
        }else{
            queue<string> neighbors = getNeighbors(topWord);
            // LOOP OVER EVERY NEIGHBOR
            while(!neighbors.empty()){
                // pop the first neighbor
                string neighbor = neighbors.front();
                neighbors.pop();

                // check if unused
                if(usedWords.count(neighbor) == 0){
                    stack<string> chainCopy = chain;
                    chainCopy.push(neighbor);
                    potentialChains.push(chainCopy);
                    usedWords.insert(neighbor);
                }
            }
        }
    }
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string bothWords;
    getline(cin, bothWords);

    int posOfFirstSpace = bothWords.find_first_of(' ');

    string firstWord = bothWords.substr(0, posOfFirstSpace);
    string secondWord = bothWords.substr(posOfFirstSpace+1);

    cout << "Chain from " << secondWord << " back to " << firstWord << endl;

    wordChain(firstWord,secondWord);

    cout << "Have a nice day." << endl;

    return 0;
}
