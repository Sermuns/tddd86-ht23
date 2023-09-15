/*Takes two words as input and tries to convert the 2nd word into the 1st by chaining valid words between them till you get the 1st word.
 * made by Daniel Alchasov(Danal315) Samuel Åkesson(Samak519).
 *
 */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

/**
 * @brief getAllWords gets all lines of words in a given .txt file.
 * @return a unordered set of all the words in given .txt file.
 */
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
const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/**
 * @brief isValidWord checks if given word exists in our dictionary
 * @param word
 * @return a bool if it exists or not.
 */
bool isValidWord(const string &word, const unordered_set<string> &allWords){
    return allWords.count(word) > 0;
}
/**
 * @brief getNeighbors gets a queue of words that are neighbours and in the dictionary
 * @param word
 * @return queue of stings of neighbours.
 */
queue<string> getNeighbors(const string &word, const unordered_set<string> &allWords){
    queue<string> validNeighbors;
    string potentialNeighbor;
    for(int i = 0; i < static_cast<int>(word.length()); i++){
        for(int j = 0; j < static_cast<int>(ALPHABET.length()); j++){
            potentialNeighbor = word;
            char letter = ALPHABET.at(j);
            potentialNeighbor[i] = letter;
            if(isValidWord(potentialNeighbor, allWords) && !(potentialNeighbor == word)){
                validNeighbors.push(potentialNeighbor);
            }
        }
    }
    return validNeighbors;
}


/**
 * @brief wordChain Prints a word chain between wordTwo and wordOne by doing a bfs search between them and finding valid neighbours till wanted result.
 * @param wordOne
 * @param wordTwo
 */
void wordChain(const string &wordOne, const string &wordTwo, const unordered_set<string> &allWords){
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
            queue<string> neighbors = getNeighbors(topWord,allWords);
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


/**
 * @brief main fuction holding all the UX and function
 * @return
 */
int main() {
    const unordered_set<string> allWords = getAllWords();
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

    wordChain(firstWord,secondWord, allWords);

    cout << "Have a nice day." << endl;

    return 0;
}
