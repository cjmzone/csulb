#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>
#include <regex>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;
};

// Function to calculate Euclidean distance between two points
double euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Function to find the smallest distance between any two points
double findClosestDistance(vector<Point>& points, int start, int end) {
    if (end - start <= 1) {
        return numeric_limits<double>::max(); // Base case: fewer than two points
    }

    double minDist = numeric_limits<double>::max();

    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j <= end; ++j) {
            double dist = euclideanDistance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return minDist;
}

// Recursive function to divide the set and find the smallest distance
double closestRecursive(vector<Point>& points, int start, int end) {
    if (end - start <= 3) {  // If the number of points is small, use brute force
        return findClosestDistance(points, start, end);
    }

    int mid = (start + end) / 2;

    double leftDist = closestRecursive(points, start, mid);
    double rightDist = closestRecursive(points, mid + 1, end);

    return min(leftDist, rightDist);
}

// Function to read points from file in the format: {{x1, y1}, {x2, y2}, ...}
vector<Point> readPointsFromFile(const string& filePath) {
    ifstream file(filePath);
    vector<Point> points;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Use a regex to extract the points in the format {x, y}
            regex pointPattern("\\{([0-9\\.\\-]+), ([0-9\\.\\-]+)\\}");
            smatch match;

            string::const_iterator searchStart(line.cbegin());
            while (regex_search(searchStart, line.cend(), match, pointPattern)) {
                Point p;
                p.x = stod(match[1]);
                p.y = stod(match[2]);
                points.push_back(p);

                searchStart = match.suffix().first; // Move to the next point in the line
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file!" << endl;
    }

    return points;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file-path>" << endl;
        return -1;
    }

    string filePath = argv[1];

    vector<Point> points = readPointsFromFile(filePath);
    if (points.size() < 2) {
        cerr << "Not enough points to calculate distances." << endl;
        return -1;
    }

    double minDistance = closestRecursive(points, 0, points.size() - 1);
    cout << fixed << setprecision(3) << "Minimum distance: " << minDistance << endl;

    return 0;
}
