#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

struct State {
    vector<int> queens; // queens[col] = row
    int g;  // queens placed so far
    int h;  // admissible heuristic
    int f;  // f = g + h

    bool operator>(const State& other) const {
        return f > other.f; // min-heap: kam f wala pehle
    }
};

// ✅ Admissible Heuristic:
// Remaining har column ke liye count karo ki kitni rows
// already attack mein hain — woh rows "blocked" hain.
// Minimum moves = remaining columns jinmein koi safe row nahi
// Yeh kabhi overestimate nahi karta — isliye admissible hai
int calculateHeuristic(const vector<int>& queens, int N) {
    int placed = queens.size();
    int h = 0;

    for (int col = placed; col < N; col++) {
        bool safeRowExists = false;

        for (int row = 0; row < N; row++) {
            bool safe = true;

            // Check karo ki koi placed queen is row ko attack karti hai
            for (int c = 0; c < placed; c++) {
                if (queens[c] == row || 
                    abs(queens[c] - row) == abs(c - col)) {
                    safe = false;
                    break;
                }
            }

            if (safe) {
                safeRowExists = true;
                break; // ek bhi safe row mili toh kaafi hai
            }
        }

        // Agar is column mein koi safe row nahi — yeh dead end hai
        // Hum isse cost mein add karte hain
        if (!safeRowExists) h++;
    }

    return h;
}

bool isSafe(const vector<int>& queens, int col, int row) {
    for (int c = 0; c < (int)queens.size(); c++) {
        if (queens[c] == row || 
            abs(queens[c] - row) == abs(c - col)) {
            return false;
        }
    }
    return true;
}

void printBoard(const vector<int>& queens, int N) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << (queens[col] == row ? "Q " : ". ");
        }
        cout << "\n";
    }
    cout << "\n";
}

void solve(int N) {
    // Min-heap — sabse kam f wala state pehle niklega
    priority_queue<State, vector<State>, greater<State>> pq;
    
    // ✅ Visited set — same configuration dobara explore na ho
    set<vector<int>> visited;

    // Shuru karo empty board se
    int h0 = calculateHeuristic({}, N);
    pq.push({{}, 0, h0, h0});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        // ✅ Visited check — agar pehle dekha hai toh skip karo
        if (visited.count(curr.queens)) continue;
        visited.insert(curr.queens);

        // Goal: saari N queens safe place ho gayi hain
        if (curr.g == N) {
            cout << "Solution found in " << curr.g << " steps!\n\n";
            printBoard(curr.queens, N);
            return;
        }

        int next_col = curr.g; // agla column = kitni queens rakhi hain

        for (int row = 0; row < N; row++) {
            // ✅ Sirf SAFE placements explore karo — pruning
            // Yeh N-Queens specific optimization hai
            // Unsafe placements ka h waise bhi zyada hoga
            if (!isSafe(curr.queens, next_col, row)) continue;

            vector<int> next_queens = curr.queens;
            next_queens.push_back(row);

            if (visited.count(next_queens)) continue;

            int g = curr.g + 1;                           // ek aur queen rakhi
            int h = calculateHeuristic(next_queens, N);   // admissible h
            int f = g + h;                                // ✅ true A*: f = g + h

            pq.push({next_queens, g, h, f});
        }
    }

    cout << "No solution found.\n";
}

int main() {
    int N = 8;
    solve(N);
    return 0;
}