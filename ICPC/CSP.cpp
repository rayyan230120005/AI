#include <iostream>
#include <vector>

using namespace std;

class NQueensCSP {
    int n;
    int solutionsCount;
    vector<int> board; // index = row, value = column
    
    // Branch and Bound Arrays (Constraints)
    vector<bool> cols;      // Column constraint
    vector<bool> diag1;     // Primary diagonal constraint (\)
    vector<bool> diag2;     // Secondary diagonal constraint (/)

public:
    NQueensCSP(int _n) : n(_n), solutionsCount(0) {
        board.resize(n);
        cols.assign(n, false);
        diag1.assign(2 * n - 1, false);
        diag2.assign(2 * n - 1, false);
    }

    void solve() {
        backtrack(0);
        cout << "Total solutions found for " << n << "-Queens: " << solutionsCount << endl;
    }

private:
    void backtrack(int row) {
        // Base Case: All queens placed
        if (row == n) {
            solutionsCount++;
            if (solutionsCount == 1) printFirstSolution();
            return;
        }

        for (int col = 0; col < n; col++) {
            // --- Branch and Bound Pruning ---
            // diag1 index: row - col + (n-1) keeps it positive
            // diag2 index: row + col
            if (!cols[col] && !diag1[row - col + n - 1] && !diag2[row + col]) {
                
                // Place Queen (Make Choice)
                board[row] = col;
                cols[col] = diag1[row - col + n - 1] = diag2[row + col] = true;

                // Move to next row
                backtrack(row + 1);

                // Backtrack (Undo Choice)
                cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
            }
        }
    }

    void printFirstSolution() {
        cout << "First Solution Map:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i] == j) cout << "Q ";
                else cout << ". ";
            }
            cout << endl;
        }
        cout << "---" << endl;
    }
};

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive integer." << endl;
    } else {
        NQueensCSP problem(n);
        problem.solve();
    }

    return 0;
}