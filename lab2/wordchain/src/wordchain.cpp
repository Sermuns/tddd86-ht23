#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

unordered_set<string> getSetForWords(){
    unordered_set<string> allWords;
    ifstream dictionary("dictionary.txt");
    string line;
    while(getline(dictionary, line)){
        allWords.insert(line);
    }
    dictionary.close();
    return allWords;
}

const unordered_set<string> allWords = getSetForWords();

bool isValidWord(const string &word){
    if (allWords.count(word) > 0) {
        return true;
    }
    return false;
}

queue<string> getNeighbors(const string &word){        cout << "yoo" << endl;

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

void wordChain(string &wordOne, const string &wordTwo){
    queue<stack<string>> stackQueue;
    stack<string> words;
    words.push(wordOne);
    stackQueue.push(words);


//    while(!stackQueue.empty()){
//       stack<string> partialChainStack = stackQueue.front();
//       stackQueue.pop();
//       string topWord = partialChainStack.top();
//       if(topWord == wordTwo){
//           // THIS IS THE CORRECT WORDCHAIN! DO STUFF!
//       }else{
//           foreach(getNeighbors(topWord))
//       }

//    }
}
//while the queue is not empty:
//dequeue the partial-chain stack from the front of the queue
//i f the word at the top of the stack is the destinaction word:
//hooray! output the elements of the stack as the solution
//e l s e:
//f o r each valid English word that is a neighbour (differs
//by 1 letter) of the word at the top of the stack:
//i f that neighbour word has not already been used in a ladder before:
//create a copy of the current chain stack
//put the neighbour word at the top of the copy stack
//add the copy stack to the end of the queue

int main() {

    queue<string> aa = getNeighbors("car");
    while(!aa.empty()){
        cout << aa.front() << endl;
        aa.pop();
    }
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string bothWords;
    getline(std::cin, bothWords);

    size_t posOfFirstSpace = bothWords.find_first_of(' ');

    string firstWord = bothWords.substr(0, posOfFirstSpace);
    string secondWord = bothWords.substr(posOfFirstSpace+1);

    cout << firstWord <<' ' << secondWord << endl;

    return 0;
}
