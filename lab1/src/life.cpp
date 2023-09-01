// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <string>
#include<fstream>
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

Grid<char> createGrid(){
    ifstream inputGrid("simple.txt");
    string line;
    int row, column;
    getline(inputGrid, line);
    row = stoi(line);
    getline(inputGrid, line);
    column = stoi(line);
    Grid<char> lifeGrid(row, column);

    for(int y = 0; y < row; y++){
        getline(inputGrid, line);
        for(int x = 0; x < column; x++){
            char input = line.at(x);
            lifeGrid.set(y, x, input);
        }
    }
    inputGrid.close();
    return lifeGrid;
}

string promptForFileName(){
    cout << "Grid input file name?" << endl;
    string filename;
    cin >> filename;

    return filename;
}

void printGrid(const Grid<char> &grid){
    for(int y = 0; y < grid.numRows(); y++){
        for(int x = 0; x < grid.numCols(); x++){
            cout << grid.get(y,x);
        }
        cout << endl;
    }
}

void advanceGeneration(Grid<char> &grid){

}

int main() {
    printWelcomeMessage();
 // promptForFileName();
    Grid<char> lifeGrid = createGrid();
    printGrid(lifeGrid);
    cout << "Have a nice Life! "  << endl;
    return 0;
}
