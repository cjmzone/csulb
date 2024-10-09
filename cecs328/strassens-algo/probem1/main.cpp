#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <fstream>
#include <future>
using namespace std;

// Helper function to read matrix from a file
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    getline(file, line);
    file.close();

    // Remove curly braces and format the matrix data
    if (line.front() == '{') line.erase(0, 2);
    if (line.back() == '}') line.erase(line.size() - 2);

    stringstream ss(line);
    string row;

    while (getline(ss, row, '}')) {
        if (!row.empty()) {
            row.erase(remove(row.begin(), row.end(), '{'), row.end());
            row.erase(remove(row.begin(), row.end(), ' '), row.end());

            stringstream rowStream(row);
            vector<int> rowValues;
            string value;

            while (getline(rowStream, value, ',')) {
                if (!value.empty()) {
                    rowValues.push_back(stoi(value));
                }
            }

            if (!rowValues.empty()) {
                matrix.push_back(rowValues);
            }
        }
    }

    return matrix;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }
}

// Function to multiply a single row of a matrix
void multiplyRow(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2, vector<vector<int>>& rslt, int row) {
    int C1 = mat1[0].size();
    int C2 = mat2[0].size();
    
    for (int j = 0; j < C2; j++) {
        for (int k = 0; k < C1; k++) {
            rslt[row][j] += mat1[row][k] * mat2[k][j];
        }
    }
}

// Function to multiply matrices using a limited number of threads
vector<vector<int>> mulMat(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    int R1 = mat1.size();
    int C2 = mat2[0].size();
    
    if (mat1[0].size() != mat2.size()) {
        cout << "The number of columns in Matrix-1 must "
                "be equal to the number of rows in "
                "Matrix-2"
             << endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<int>> rslt(R1, vector<int>(C2, 0));

    // Get the number of available hardware threads
    unsigned int numThreads = thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 2; // Fallback to 2 threads if the hardware doesn't support querying

    vector<thread> threads;

    for (int i = 0; i < R1; i++) {
        if (threads.size() >= numThreads) {
            for (auto& th : threads) {
                th.join();
            }
            threads.clear();
        }

        threads.emplace_back(multiplyRow, ref(mat1), ref(mat2), ref(rslt), i);
    }

    // Join any remaining threads
    for (auto& th : threads) {
        th.join();
    }

    return rslt;
}

// Function to sum all elements of a matrix
int sumMatrix(const vector<vector<int>>& matrix) {
    int total = 0;
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            total += value;
        }
    }
    return total;
}

int main() {
    string file1, file2;

    cout << "Enter the first matrix filename: ";
    cin >> file1;
    cout << "Enter the second matrix filename: ";
    cin >> file2;

    vector<vector<int>> mat1 = readMatrixFromFile(file1);
    vector<vector<int>> mat2 = readMatrixFromFile(file2);

    // Multiply matrices
    vector<vector<int>> multipliedMatrix = mulMat(mat1, mat2);

    // Sum the resulting matrix
    int totalSum = sumMatrix(multipliedMatrix);
    cout << "Sum of all elements in the multiplied matrix: " << totalSum << endl;

    return 0;
}
