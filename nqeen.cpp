#include <iostream>
#include <vector>
using namespace std;

// Function to print the n-Queens matrix
void printSolution(vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a queen can be placed at board[row][col]
bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check this column on the upper side
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper diagonal on the right side
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Function to solve n-Queens problem using backtracking
bool solveNQueens(vector<vector<int>>& board, int row, int n) {
    // Base case: If all queens are placed
    if (row >= n) {
        return true;
    }

    // Try placing queens in all columns of the current row
    for (int col = 0; col < n; col++) {
        // Check if placing a queen at board[row][col] is safe
        if (isSafe(board, row, col, n)) {
            // Place the queen at board[row][col]
            board[row][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueens(board, row + 1, n)) {
                return true;
            }

            // If placing queen here doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    // If no column is found, return false
    return false;
}

int main() {
    int n;
    cout << "Enter the number of queens (n): ";
    cin >> n;

    // Initialize the board with 0s
    vector<vector<int>> board(n, vector<int>(n, 0));

    // Place the first queen manually in the first row and first column
    board[0][0] = 1;

    // Use backtracking to place the remaining queens
    if (!solveNQueens(board, 1, n)) {  // Start from the second row
        cout << "No solution exists" << endl;
    } else {
        cout << "The solution to the n-Queens problem is:" << endl;
        printSolution(board, n);
    }

    return 0;
}
