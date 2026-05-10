#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

// Goal state for the 8-puzzle
vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

struct Node {
    vector<vector<int>> board;
    int g, h, f;
    int x, y; // Position of the blank space (0)
    Node* parent;

    Node(vector<vector<int>> b, int _g, int _x, int _y, Node* p) 
        : board(b), g(_g), x(_x), y(_y), parent(p) {
        h = calculateHeuristic();
        f = g + h;
    }

    int calculateHeuristic() {
        int dist = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 0) {
                    int val = board[i][j] - 1;
                    dist += abs(i - val / 3) + abs(j - val % 3);
                }
            }
        }
        return dist;
    }
};

struct CompareNodes {
    bool operator()(Node* a, Node* b) { return a->f > b->f; }
};

void printBoard(const vector<vector<int>>& b) {
    for (auto& row : b) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "---" << endl;
}

void solve(vector<vector<int>> start, int x, int y) {
    priority_queue<Node*, vector<Node*>, CompareNodes> pq;
    map<vector<vector<int>>, bool> visited;

    pq.push(new Node(start, 0, x, y, nullptr));

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();

        if (curr->board == goal) {
            cout << "Goal Reached! Moves: " << curr->g << endl;
            return;
        }

        visited[curr->board] = true;

        for (int i = 0; i < 4; i++) {
            int nx = curr->x + dx[i], ny = curr->y + dy[i];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> nextBoard = curr->board;
                swap(nextBoard[curr->x][curr->y], nextBoard[nx][ny]);

                if (!visited[nextBoard]) {
                    pq.push(new Node(nextBoard, curr->g + 1, nx, ny, curr));
                }
            }
        }
    }
}

int main() {
    // 0 represents the blank tile
    vector<vector<int>> start = {{1, 2, 3}, {4, 0, 6}, {7, 5, 8}};
    solve(start, 1, 1);
    return 0;
}