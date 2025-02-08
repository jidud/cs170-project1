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

vector<vector<int>> nextMove(const vector<vector<int>>& puzzle, int x, int y, int newX, int newY) {
    vector<vector<int>> newPuzzle = puzzle;
    swap(newPuzzle[x][y], newPuzzle[newX][newY]);
    return newPuzzle;
}

vector<vector<vector<int>>> getNeighbors(const vector<vector<int>>& puzzle) {
    vector<vector<vector<int>>> neighbors;
    int x = 0;
    int y = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] == 0) {
                x = i; 
                y = j;
            }
        }
    }
    
    vector<pair<int, int>> moves = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    for (auto& move : moves) {
        int newX = x + move.first;
        int newY = y + move.second;
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            neighbors.push_back(nextMove(puzzle, x, y, newX, newY));
        }
    }
    return neighbors;
}

void printPuzzle(const vector<vector<int>>& puzzle) {
    for (const auto& x : puzzle) {
        cout << "[";
        for (size_t i = 0; i < x.size(); i++) {
            cout << x[i] << (i < x.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }
}

// about priority_queue
// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
void search(vector<vector<int>> start, int heuristicType) {
    // USC == 0; MT == 1; MD == 2
    auto heuristic = (heuristicType == 1) ? misplacedTiles : (heuristicType == 2 ? manhattanDistance : [](auto){ return 0; });
    priority_queue<Node*, vector<Node*>, compareNodes> pq;
    set<vector<vector<int>>> visited;
    int nodesExpanded = 0;
    int maxQueue = 0;
    pq.push(new Node(start, 0, heuristic(start), 0));
    
    while (!pq.empty()) {
        maxQueue = max(maxQueue, (int)pq.size());
        Node* current = pq.top(); 
        pq.pop();
        if (visited.find(current->puzzle) != visited.end()) {
            continue;
        }
        visited.insert(current->puzzle);
        nodesExpanded++;
        
        cout << "The best state to expand with a g(n) = " << current->g << " and h(n) = " << current->h << " is..." << endl;
        printPuzzle(current->puzzle);
        
        if (current->puzzle == goal) {
            cout << "Goal state!" << endl;
            cout << "Depth: " << current->depth << endl;
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Max queue size: " << maxQueue << endl;
            return;
        }
        
        for (auto& next : getNeighbors(current->puzzle)) {
            if (visited.find(next) == visited.end()) {
                pq.push(new Node(next, current->g + 1, heuristic(next), current->depth + 1));
            }
        }
    }
    cout << "No solution found!" << endl;
}

int main() {

    vector<vector<int>> puzzle = { {1, 2, 3}, {0, 5, 6}, {4, 7, 8} };
    
    cout << "Enter “1” for a default puzzle or “2” to make your own puzzle." << endl;

    string choice;
    cin >> choice;

    if (choice == "1") {
    } else if (choice == "2") {
        cout << "Enter first row(use space between numbers): ";
        for (int i = 0; i < 3; i++) cin >> puzzle[0][i];
        cout << "Enter second row(use space between numbers): ";
        for (int i = 0; i < 3; i++) cin >> puzzle[1][i];
        cout << "Enter third row(use space between numbers): ";
        for (int i = 0; i < 3; i++) cin >> puzzle[2][i];
    }

    cin.clear();
    cout << "Choose a search algorithm: " << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with Manhattan Distance heuristic" << endl;
    cin >> choice;

    if (choice == "1") {
        search(puzzle, 0);
    }
    else if (choice == "2") { 
        search(puzzle, 1);
    }
    else if (choice == "3") { 
        search(puzzle, 2);
    }
    return 0;
}
