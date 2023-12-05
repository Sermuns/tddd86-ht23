#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

const int SIZE = 4;

// Function to check if a given string is a valid word
bool isValidWord(const string &word, const unordered_set<string> &dictionary) {
    return dictionary.find(word) != dictionary.end();
}


bool isPartialStringInBiggerString(const string& partial, const string& bigger) {
    // Use std::string::find to check if 'partial' is present in 'bigger'
    size_t found = bigger.find(partial);
    
    // If 'partial' is found in 'bigger', 'found' will be the position of the first occurrence
    // Otherwise, 'found' will be string::npos
    return found != string::npos;
}

// Function to perform BFS on the Boggle grid
void bfsBoggle(const vector<vector<char>> &grid, const unordered_set<string> &dictionary) {
    // Define possible moves (8 directions)
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    queue<pair<pair<string, pair<int, int>>, unordered_set<pair<int, int>>>> queueWords; // (currentWord, (x, y))
    queue<pair<int, int>> visitedCoords; // (x, y)

    // Start BFS from each cell in the grid
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            unordered_set<pair<int, int>> current;
            queueWords.push({{string(1, grid[i][j]), {i, j}}, current }  );
        }
    }
    int oldX;
    int oldY;
    
    while (!queueWords.empty()) {
        vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));
        auto current = queueWords.front();
        queueWords.pop();

        string currentWord = current.first.first;
        int x = current.first.second.first;
        int y = current.first.second.second;
        visited[x][y] = true;




        // Check if the current word is valid
        if (isValidWord(currentWord, dictionary)) {
            cout << "Found valid word: " << currentWord << endl;
        }


        for (auto coord : current.second) {
            visited[coord.first][coord.second] = true;
        }
        // Explore neighbors
        for (int i = 0; i < 8; ++i) {
            int nx = (x + dx[i] + SIZE) % SIZE; // Wrap around using modulo
            int ny = (y + dy[i] + SIZE) % SIZE; // Wrap around using modulo

            if (!visited[nx][ny]) {
                // Check if the current word is a prefix of any word in the dictionary
                bool isPrefix = false;

                for (auto word : dictionary) {
                    if (isPartialStringInBiggerString(currentWord, word)) {
                        isPrefix = true;
                        break;
                    }
                }


                if (isPrefix)
                {
                visited[nx][ny] = true;
                unordered_set<pair<int, int>> visitedCoords = current.second;
                visitedCoords.insert({x, y});
                queueWords.push({{currentWord + grid[nx][ny], {nx, ny}}, visitedCoords});

                }
               
            }
        }


    }
}

int main() {
    // Sample Boggle grid
    vector<vector<char>> boggleGrid = {
        {'a', 'b', 'c', 'd'},
        {'e', 'f', 'g', 'h'},
        {'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p'}
    };

    // Sample dictionary of valid words
    unordered_set<string> dictionary = {"abcd", "efgh", "ijkl", "mnop", "aeim", "bfjn", "cgko", "dhlp", "adad"};
    cout << "Dictionary: ";
    bfsBoggle(boggleGrid, dictionary);

    return 0;
}
