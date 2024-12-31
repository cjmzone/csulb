#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Function to solve the 0/1 knapsack problem
int knapsack(int C, vector<pair<int, int>>& bricks) {
    vector<int> dp(C + 1, 0);

    // Iterate over each brick (value, weight)
    for (auto& brick : bricks) {
        int value = brick.first;
        int weight = brick.second;

        // Traverse DP array in reverse to avoid using the same brick multiple times
        for (int j = C; j >= weight; j--) {
            dp[j] = max(dp[j], dp[j - weight] + value);
        }
    }

    return dp[C];
}

// Function to parse the input file
void parseInputFile(const string& filename, int& capacity, vector<pair<int, int>>& bricks) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    string line;
    getline(file, line);  // Read the whole file content in a single line

    // Remove unwanted characters {,}, whitespace
    line.erase(remove(line.begin(), line.end(), '{'), line.end());
    line.erase(remove(line.begin(), line.end(), '}'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

    // Replace commas with space to simplify stringstream processing
    replace(line.begin(), line.end(), ',', ' ');

    stringstream ss(line);
    ss >> capacity;  // First number is the knapsack capacity

    int value, weight, ignore;
    // Parse each set of brick values (v_i, w_i, 1)
    while (ss >> value >> weight >> ignore) {
        bricks.push_back({value, weight});
    }

    file.close();
}

int main() {
    string filename;
    cout << "Enter the filename containing the knapsack data: ";
    cin >> filename;

    int capacity;
    vector<pair<int, int>> bricks;

    // Parse the input from the file
    parseInputFile(filename, capacity, bricks);

    // Solve the knapsack problem
    int maxProfit = knapsack(capacity, bricks);
    cout << "The maximum total profit that can be stolen is: " << maxProfit << endl;

    return 0;
}
