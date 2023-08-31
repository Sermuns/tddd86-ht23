// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <string>
#include "lifeutil.h"
#include "grid.h"

using namespace std;

void printWelcomeMessage() {
    cout << "Welcome to the TDDD86 Game of Life,\n";
    cout << "a simulation of the lifecycle of a bacteria colony.\n";
    cout << "Cells (X) live and die by the following rules:\n";
    cout << "- A cell with 1 or fewer neighbours dies.\n";
    cout << "- Locations with 2 neighbours remain stable.\n";
    cout << "- Locations with 3 neighbours will create life.\n";
    cout << "- A cell with 4 or more neighbours dies.\n";
}

string promptForFileName(){
    cout << "Grid input file name?" << endl;
    string filename;
    cin >> filename;
    return filename;
}

int main() {
    printWelcomeMessage();
    cout << "Have a nice Life! "  << endl;
    return 0;
}
