#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

int main() {
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

    cout << firstWord << secondWord << endl;

    return 0;
}
