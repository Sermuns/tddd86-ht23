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

Grid<char> createGrid(const string &fileName){

    //Just don't do it wrong!!

    ifstream inputGrid(fileName);
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

int getNeighbours(const Grid<char> &grid, const int yCoord, const int xCoord){

    int neighbourAmount = 0;
    for(int y = (yCoord -1); y <= (yCoord + 1); y++){
        for(int x = (xCoord - 1); x <= (xCoord + 1);x++){
            bool notSelf = !(xCoord == x && yCoord == y);
            if(grid.inBounds(y,x) && notSelf){
                if(grid.get(y,x) == 'X'){
                    neighbourAmount++;
                }
            }
        }
    }
    return neighbourAmount;
}

void advanceGeneration(Grid<char> &grid){
    Grid<char> gridClone = grid;
    for(int y = 0; y < gridClone.numRows(); y++){
        for(int x = 0; x < gridClone.numCols(); x++){
            int neighbourAmount = getNeighbours(grid,y,x);
             if(neighbourAmount == 3){
                 gridClone.set(y, x, 'X');
             }
             else if(neighbourAmount < 2 || neighbourAmount > 3){
                 gridClone.set(y, x, '-');
             }
        }
  }
    grid = gridClone;
}


int main() {
    bool playing = true;
    printWelcomeMessage();
    string fileName = promptForFileName();
    Grid<char> lifeGrid = createGrid(fileName);
    printGrid(lifeGrid);
    string optionsText = "a)nimate, t)ick, q)uit? ";
    int sleepLength = 100;
    char chosenOption;
    while (playing) {
        cout << optionsText;
        cin >> chosenOption;
        switch (chosenOption) {
        case 'a':
            while (true) {
            pause(sleepLength);
            advanceGeneration(lifeGrid);
            clearConsole();
            printGrid(lifeGrid);
            }
        break;
        case 't':
            advanceGeneration(lifeGrid);
        break;

        case 'q':
            playing = false;
        break;
        }
        clearConsole();
        printGrid(lifeGrid);
    }

    cout << "Have a nice Life! "  << endl;
    return 0;
}

