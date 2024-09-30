#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>

using namespace std;

// Function to decode the value from a given base
long long decodeValue(int base, const string& value) {
    long long decodedValue = 0;
    for (char c : value) {
        int digit = (c >= '0' && c <= '9') ? c - '0' :
                    (c >= 'A' && c <= 'Z') ? c - 'A' + 10 : 0;  // Supports uppercase letters for bases above 10
        decodedValue = decodedValue * base + digit;
    }
    return decodedValue;
}

// Lagrange interpolation to find the constant term c
double lagrangeInterpolation(const vector<pair<int, long long>>& points) {
    double c = 0.0;
    int n = points.size();

    for (int i = 0; i < n; i++) {
        int xi = points[i].first;
        long long yi = points[i].second;
        double term = yi;

        for (int j = 0; j < n; j++) {
            if (i != j) {
                int xj = points[j].first;
                term *= (0.0 - xj) / (xi - xj);  // Lagrange polynomial multiplication
            }
        }

        c += term;
    }

    return round(c);  // Rounding to nearest integer
}

// Function to process the test cases
void processTestCases(const vector<map<string, map<string, string>>>& testCases) {
    for (int index = 0; index < testCases.size(); index++) {
        const map<string, map<string, string>>& testCase = testCases[index];
        int n = stoi(testCase.at("keys").at("n"));
        int k = stoi(testCase.at("keys").at("k"));

        vector<pair<int, long long>> points;

        // Decode the points (x, y)
        for (const auto& entry : testCase) {
            if (entry.first == "keys") continue;
            int x = stoi(entry.first);  // x is the key
            int base = stoi(entry.second.at("base"));
            long long y = decodeValue(base, entry.second.at("value"));  // Decode y
            points.push_back({x, y});
        }

        // We need at least k points to solve for the polynomial
        vector<pair<int, long long>> selectedPoints(points.begin(), points.begin() + k);

        // Find the secret constant 'c' using Lagrange Interpolation
        double secret = lagrangeInterpolation(selectedPoints);

        cout << "Test Case " << index + 1 << " Secret: " << secret << endl;

        // For the second test case, check for wrong points
        if (index == 1) {
            vector<pair<int, long long>> wrongPoints;
            for (const auto& point : points) {
                if (abs(point.second - secret) > 1000) {  // Simple heuristic
                    wrongPoints.push_back(point);
                }
            }
            cout << "Test Case " << index + 1 << " Wrong Points: ";
            for (const auto& wp : wrongPoints) {
                cout << "(" << wp.first << ", " << wp.second << ") ";
            }
            cout << endl;
        }
    }
}

// Main function to run the code
int main() {
    vector<map<string, map<string, string>>> testCases = {
        {
            {"keys", {{"n", "4"}, {"k", "3"}}},
            {"1", {{"base", "10"}, {"value", "4"}}},
            {"2", {{"base", "2"}, {"value", "111"}}},
            {"3", {{"base", "10"}, {"value", "12"}}},
            {"6", {{"base", "4"}, {"value", "213"}}}
        },
        {
            {"keys", {{"n", "9"}, {"k", "6"}}},
            {"1", {{"base", "10"}, {"value", "28735619723837"}}},
            {"2", {{"base", "16"}, {"value", "1A228867F0CA"}}},
            {"3", {{"base", "12"}, {"value", "32811A4AA0B7B"}}},
            {"4", {{"base", "11"}, {"value", "917978721331A"}}},
            {"5", {{"base", "16"}, {"value", "1A22886782E1"}}},
            {"6", {{"base", "10"}, {"value", "28735619654702"}}},
            {"7", {{"base", "14"}, {"value", "71AB5070CC4B"}}},
            {"8", {{"base", "9"}, {"value", "122662581541670"}}},
            {"9", {{"base", "8"}, {"value", "642121030037605"}}}
        }
    };

    // Process all test cases
    processTestCases(testCases);

    return 0;
}
