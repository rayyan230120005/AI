#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>

using namespace std;

struct State {
    vector<int> queens; // index = col, value = row
    int conflicts;
    int g; // number of queens placed

    // We want the state with the lowest conflicts (h) and most queens (g)
    bool operator>(const State& other) const {
        if (conflicts == other.conflicts) {
            return g < other.g; 
        }
        return conflicts > other.conflicts;
    }
};

class NQueensSolver {
    int N;

public:
    NQueensSolver(int n) : N(n) {}

    // Heuristic: Calculates number of attacking pairs
    int calculateConflicts(const vector<int>& queens) {
        int conflicts = 0;
        int n = queens.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Check same row or same diagonal
                if (queens[i] == queens[j] || abs(queens[i] - queens[j]) == abs(i - j)) {
                    conflicts++;
                }
            }
        }
        return conflicts;
    }

    void solve() {
        priority_queue<State, vector<State>, greater<State>> pq;
        
        // Initial empty state
        pq.push({{}, 0, 0});

        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            // Goal check: All queens placed with zero conflicts
            if (current.g == N && current.conflicts == 0) {
                printBoard(current.queens);
                return;
            }

            // Try placing a queen in the next available column
            int next_col = current.g;
            if (next_col < N) {
                for (int row = 0; row < N; row++) {
                    vector<int> next_queens = current.queens;
                    next_queens.push_back(row);
                    
                    int h = calculateConflicts(next_queens);
                    // Standard A*: f = g + h, but here we prioritize h = 0
                    pq.push({next_queens, h, (int)next_queens.size()});
                }
            }
        }
        cout << "No solution found." << endl;
    }

    void printBoard(const vector<int>& queens) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (queens[j] == i) cout << "Q ";
                else cout << ". ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n = 8; 
    NQueensSolver solver(n);
    solver.solve();
    return 0;
}