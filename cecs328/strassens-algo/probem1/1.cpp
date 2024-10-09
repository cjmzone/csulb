#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to read matrix from file with curly braces and commas
vector<vector<int> > readMatrix(const string &filename) {
    ifstream file(filename);
    vector<vector<int> > matrix(3, vector<int>(3)); // Initialize 3x3 matrix

    char ch;
    int number;
    int row = 0, col = 0;
    string temp = "";

    // Read character by character
    while (file >> ch) {
        // If the character is a digit or a minus sign, append it to the temp string
        if (isdigit(ch) || ch == '-') {
            temp += ch;
        } else if (ch == ',' || ch == '}' || ch == '{') {
            // If a comma or curly brace is encountered and the temp string has a number
            if (!temp.empty()) {
                number = stoi(temp); // Convert the string to integer
                matrix[row][col] = number; // Store it in the matrix
                col++;
                if (col == 3) { // Move to the next row if the current row is filled
                    row++;
                    col = 0;
                }
                temp.clear(); // Clear the temp string for the next number
            }
        }
    }

    // Debug print to check if matrix is read correctly
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " "; // Print the matrix element
        }
        cout << endl; // Newline after each row
    }

    file.close();
    return matrix;
}

// Function to multiply two matrices and return the result
vector<vector<int> > multiplyMatrices(const vector<vector<int> > &a, const vector<vector<int> > &b) {
    vector<vector<int> > result(3, vector<int>(3, 0));

    // Perform matrix multiplication
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

// Function to compute the sum of the matrix elements
int sumMatrix(const vector<vector<int> > &matrix) {
    int sum = 0;

    // Sum all the elements of the matrix
    for (const auto &row : matrix) {
        for (int val : row) {
            sum += val;
        }
    }
    return sum;
}

int main(int argc, char* argv[]) {
    // Check if two file names are passed as arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <matrix_a_file> <matrix_b_file>" << endl;
        return 1;
    }

    // Reading matrices from files passed as command-line arguments
    string matrixAFile = argv[1];
    string matrixBFile = argv[2];
    
    vector<vector<int> > a = readMatrix(matrixAFile);
    vector<vector<int> > b = readMatrix(matrixBFile);

    // Multiplying matrices
    vector<vector<int> > result = multiplyMatrices(a, b);

    // Computing the sum of the entries in the result matrix
    int sum = sumMatrix(result);

    // Output the sum
    cout << "Sum of the entries in the result matrix: " << sum << endl;

    return 0;
}
