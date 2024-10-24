#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure for an item which stores weight and corresponding value
struct Item {
    int value;
    int weight;

    // Constructor to initialize values
    Item(int value, int weight) : value(value), weight(weight) {}
};

// Comparison function to sort items based on value/weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;  // Sort in decreasing order of value/weight ratio
}

// Function to calculate the maximum total value in the knapsack
double fractionalKnapsack(int W, vector<Item>& items) {
    // Sort items based on value/weight ratio in descending order
    sort(items.begin(), items.end(), compare);

    int currentWeight = 0;  // Current weight in the knapsack
    double finalValue = 0.0;  // Result (total value in the knapsack)

    // Loop through all sorted items
    for (auto& item : items) {
        // If adding the entire item won't exceed capacity, add it
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            finalValue += item.value;
        }
        // If we can't add the entire item, add a fraction of it
        else {
            int remainingWeight = W - currentWeight;
            finalValue += item.value * ((double)remainingWeight / item.weight);
            break;  // Knapsack is full
        }
    }

    return finalValue;
}

int main() {
    int W;  // Maximum capacity of the knapsack
    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;

    int n;  // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items;
    for (int i = 0; i < n; i++) {
        int value, weight;
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value >> weight;
        items.push_back(Item(value, weight));
    }

    // Calculate the maximum value we can get in the knapsack
    double maxValue = fractionalKnapsack(W, items);

    cout << "Maximum value in the knapsack = " << maxValue << endl;

    return 0;
}


// Enter the maximum capacity of the knapsack: 50
// Enter the number of items: 3
// Enter value and weight of item 1: 60 10
// Enter value and weight of item 2: 100 20
// Enter value and weight of item 3: 120 30

// Maximum value in the knapsack = 240
