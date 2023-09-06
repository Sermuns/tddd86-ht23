// This is the CPP file you will edit and turn in.
// Made by Daniel Alchasov(danal315) & Samuel Åkesson(samak519).

#include <iostream>
#include <string>
#include<fstream>
#include "lifeutil.h"
#include "grid.h"

using namespace std;

/**
 * Print a bunch of welcome text.
 */
void printWelcomeMessage() {
    cout << "Welcome to the TDDD86 Game of Life,\n";
    cout << "a simulation of the lifecycle of a bacteria colony.\n";
    cout << "Cells (X) live and die by the following rules:\n";
    cout << "- A cell with 1 or fewer neighbours dies.\n";
    cout << "- Locations with 2 neighbours remain stable.\n";
    cout << "- Locations with 3 neighbours will create life.\n";
    cout << "- A cell with 4 or more neighbours dies.\n\n";
}

/**
 * @brief Construct a grid using filename to a .txt file
 * @param fileName
 * @return a grid object
 */
Grid<char> createGrid(const string &fileName){
    ifstream inputGrid(fileName);
    string line;

    // getting row and column from file
    getline(inputGrid, line);
    int row = stoi(line);
    getline(inputGrid, line);
    int column = stoi(line);

    Grid<char> lifeGrid(row, column);

    // getting the grid from file
    for(int y = 0; y < row; y++){
        getline(inputGrid, line);
        for(int x = 0; x < column; x++){
            char value = line.at(x);
            lifeGrid.set(y, x, value);
        }
    }
    inputGrid.close();

    return lifeGrid;
}

/**
 * @brief promptForFileName asks for which grid should be used
 * @return string of filename.
 */
string promptForFileName(){
    cout << "Grid input file name? ";
    string filename;
    cin >> filename;

    return filename;
}

/**
 * @brief printGrid prints the given .txt files grid as a string
 * @param grid.
 */
void printGrid(const Grid<char> &grid){
    for(int y = 0; y < grid.numRows(); y++){
        for(int x = 0; x < grid.numCols(); x++){
            cout << grid.get(y,x);
        }
        cout << endl;
    }
}

/**
 * @brief getNeighbours, gets neighbours for a given cell by checking its surroundings.
 * @param grid
 * @param yCoord
 * @param xCoord
 * @return amount of infected cells at given coord.
 */
int getNeighbours(const Grid<char> &grid, const int yCoord, const int xCoord){
    int neighbourAmount = 0;
    for(int y = (yCoord -1); y <= (yCoord + 1); y++){
        for(int x = (xCoord - 1); x <= (xCoord + 1);x++){
            bool notSelf = !(xCoord == x && yCoord == y);
            if(grid.inBounds(y,x) && grid.get(y,x) == 'X' && notSelf){
                neighbourAmount++;
            }
        }
    }
    return neighbourAmount;
}
/**
 * @brief advanceGeneration advances the given grid based on the given rules the game follows
 * @param grid
 */
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
/**
 * @brief main plays the game of life.
 * @return 0
 */
int main() {
    bool playing = true;
    printWelcomeMessage();
    Grid<char> lifeGrid = createGrid(promptForFileName());
    printGrid(lifeGrid);
    const string optionsText = "a)nimate, t)ick, q)uit? ";
    const int SLEEP_LENGTH = 100;
    string chosenOption;
    while (playing) {
        cout << optionsText;
        cin >> chosenOption;

        switch (chosenOption.at(0)) {
        case 'a':
            for(int i=0; i<50;i++) {
                pause(SLEEP_LENGTH);
                advanceGeneration(lifeGrid);
                clearConsole();
                printGrid(lifeGrid);
            }
            break;

        case 't':
            advanceGeneration(lifeGrid);
            printGrid(lifeGrid);
            break;

        case 'q':
            playing = false;
            break;

        default:
            cout << "Invalid input!" << endl;
            break;
        }
    }

    // Ending
    cout << "Have a nice Life!"  << endl;
    return 0;
}

