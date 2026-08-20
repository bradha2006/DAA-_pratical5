#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve Knapsack and display chosen items
void solveKnapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    // K[i][w] will store the maximum value that can be attained with a capacity of 'w' using the first 'i' items
    vector<vector<int>> K(n + 1, vector<int>(capacity + 1, 0));

    // Build the DP table in a bottom-up manner
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            // If the weight of the current item is less than or equal to the current capacity
            if (weights[i - 1] <= w) {
                // Max of including the item vs excluding the item
                K[i][w] = max(values[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]);
            } else {
                // Exclude the item
                K[i][w] = K[i - 1][w];
            }
        }
    }

    // The maximum value is found at K[n][capacity]
    int maxValue = K[n][capacity];
    cout << "\n=========================================\n";
    cout << "Maximum Value in Knapsack = " << maxValue << endl;

    // Tracing back to find the exact items chosen
    cout << "Items selected (1-based index):\n";
    cout << "-----------------------------------------\n";
    
    int w = capacity;
    for (int i = n; i > 0 && maxValue > 0; i--) {
        // If the value comes from K[i-1][w], it means the item was NOT included.
        // If it is different, the item WAS included in the optimal set.
        if (maxValue != K[i - 1][w]) {
            cout << "Item " << i << " -> Weight: " << weights[i - 1] 
                 << ", Value: " << values[i - 1] << endl;
            
            // Deduct the item's value and weight to move to the previous state
            maxValue -= values[i - 1];
            w -= weights[i - 1];
        }
    }
    cout << "=========================================\n";
}

int main() {
    int n, capacity;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> values(n);
    vector<int> weights(n);

    cout << "Enter the values of the items:\n";
    for (int i = 0; i < n; i++) {
        cout << "Value of item " << i + 1 << ": ";
        cin >> values[i];
    }

    cout << "\nEnter the weights of the items:\n";
    for (int i = 0; i < n; i++) {
        cout << "Weight of item " << i + 1 << ": ";
        cin >> weights[i];
    }

    cout << "\nEnter the maximum capacity of the knapsack: ";
    cin >> capacity;

    solveKnapsack(capacity, weights, values, n);

    return 0;
}
