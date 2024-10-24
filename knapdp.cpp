#include <iostream>
#include <vector>
using namespace std;

// Function to solve 0-1 Knapsack problem using dynamic programming
int knapsackDP(int W, vector<int>& weights, vector<int>& values, int n) {
    // Create a 2D array to store the maximum value for each subproblem
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the dp array
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                // Either include the item or exclude it
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                // Exclude the item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right corner contains the maximum value for the knapsack
    return dp[n][W];
}

int main() {
    int W; // Maximum weight of the knapsack
    cout << "Enter the maximum weight of the knapsack: ";
    cin >> W;

    int n; // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> values(n), weights(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> values[i] >> weights[i];
    }

    // Solve the 0-1 Knapsack problem using dynamic programming
    int maxValue = knapsackDP(W, weights, values, n);

    cout << "Maximum value in the knapsack = " << maxValue << endl;

    return 0;
}



// Enter the maximum weight of the knapsack: 50
// Enter the number of items: 3
// Enter value and weight of item 1: 60 10
// Enter value and weight of item 2: 100 20
// Enter value and weight of item 3: 120 30

// Maximum value in the knapsack = 220
