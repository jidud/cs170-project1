// g++ -std=c++17 main.cpp -o main
// ./main
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>

using namespace std;

struct Node {
    vector<vector<int>> puzzle;
    int g; // g(n)
    int h; // h(n)
    int depth;

    
    Node(vector<vector<int>> move, int g = 0, int h = 0, int d = 0) 
        : puzzle(move), g(g), h(h), depth(d){}
    
    int f() const { return g + h; } // f(n) = g(n) + h(n)
};

struct compareNodes {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

vector<vector<int>> goal = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };

int misplacedTiles(const vector<vector<int>>& puzzle) {
    int mt = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] != 0 && puzzle[i][j] != goal[i][j]) {
                mt++;
            }
        }
    }
    return mt;
}

// m.h formula
//https://www.geeksforgeeks.org/maximum-manhattan-distance-between-a-distinct-pair-from-n-coordinates/
int manhattanDistance(const vector<vector<int>>& puzzle) {
    int dist = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] != 0) {
                int value = puzzle[i][j] - 1;
                int goalX = value / 3;
                int goalY = value % 3;
                dist += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return dist;
}

void printPuzzle(const vector<vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        cout << "[";
        for (size_t i = 0; i < row.size(); i++) {
            cout << row[i] << (i < row.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }
}


int main() {

    vector<vector<int>> puzzle = {{1, 2, 3}, {0, 5, 6}, {4, 7, 8}};
    
    cout << "Enter “1” for a default puzzle or “2” to make your own puzzle." << endl;

    string choice;
    cin >> choice;


    if (choice == "1") {
    } else if (choice == "2") {
        cout << "Enter the first row, use space between numbers: ";
        for (int i = 0; i < 3; i++) cin >> puzzle[0][i];
        cout << "Enter the second row, use space between numbers: ";
        for (int i = 0; i < 3; i++) cin >> puzzle[1][i];
        cout << "Enter the third row, use space between numbers: ";
        for (int i = 0; i < 3; i++) cin >> puzzle[2][i];
    }

    cin.clear();
    cout << "Choose a search algorithm: " << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with Manhattan Distance heuristic" << endl;
    cin >> choice;

   
    if (choice == "1") {
        // UCS
    }
    else if (choice == "2") { 
        // M.T
    }
    else if (choice == "3") { 
        // M.D
    }
    return 0;
}
