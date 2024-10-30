#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

// Function to decode y values based on provided base
vector<int> decodeYValues(const map<int, Json::Value> &points) {
    vector<int> decodedY;
    for (const auto &point : points) {
        string value = point.second["value"].asString();
        int base = point.second["base"].asInt();
        decodedY.push_back(stoi(value, nullptr, base));
    }
    return decodedY;
}

// Function to interpolate and find the constant term (Lagrange Interpolation)
int findConstantTerm(const vector<int> &xValues, const vector<int> &yValues) {
    double result = 0.0;
    int n = xValues.size();

    // Lagrange Interpolation formula
    for (int i = 0; i < n; i++) {
        double term = yValues[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= static_cast<double>(-xValues[j]) / (xValues[i] - xValues[j]);
            }
        }
        result += term;
    }

    return static_cast<int>(round(result));
}

int main() {
    // Load JSON file
    ifstream file("test_cases.json");
    Json::Value root;
    file >> root;

    int n = root["keys"]["n"].asInt();
    int k = root["keys"]["k"].asInt();

    map<int, Json::Value> points;
    vector<int> xValues;

    // Extract points and organize them
    for (const auto& key : root["points"].getMemberNames()) {
        int x = stoi(key);
        xValues.push_back(x);
        points[x] = root["points"][key];
    }

    // Decode y values
    vector<int> yValues = decodeYValues(points);

    // Find the constant term (secret)
    int secret = findConstantTerm(xValues, yValues);

    // Output the result
    cout << secret << endl;

    return 0;
}
