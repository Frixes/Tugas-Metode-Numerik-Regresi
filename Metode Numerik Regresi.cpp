#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>


using namespace std;



struct DataPoint {
    double x;
    double y;
};

vector<DataPoint> readCSV(const string &filename) {
    vector<DataPoint> data;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return data;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> row;

        while (getline(ss, token, ',')) {
            row.push_back(token);
        }

        if (row.size() >= 6) {
            double x = stod(row[4]);
            double y = stod(row[5]);
            data.push_back({x, y});
        }
    }

    return data;
}

void linearRegression(const vector<DataPoint> &data, double &slope, double &intercept) {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int n = data.size();

    for (const auto &point : data) {
        sumX += point.x;
        sumY += point.y;
        sumXY += point.x * point.y;
        sumX2 += point.x * point.x;
    }

    slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    intercept = (sumY - slope * sumX) / n;
}

void powerRegression(const vector<DataPoint> &data, double &a, double &b, double &C) {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2Y = 0, sumXX = 0;
    int n = data.size();

    for (const auto &point : data) {
        sumX += log(point.x);
        sumY += log(point.y);
        sumXY += log(point.x) * log(point.y);
        sumXX += pow(log(point.x), 2);
        sumX2Y += pow(log(point.x), 2) * log(point.y);
    }

    b = (n * sumXY - sumX * sumY) / (n * sumXX - pow(sumX, 2));
    a = (sumY * sumXX - sumX * sumXY) / (n * sumXX - pow(sumX, 2));
    C = exp(a);
}

int main() {
    string filename = "..\\Student_Performance.csv";
    vector<DataPoint> data = readCSV(filename);

    if (data.empty()) {
        cerr << "No data read from the file!" << endl;
        return 1;
    }

    double slope, intercept;
    linearRegression(data, slope, intercept);

    cout << "Slope: " << slope << endl;
    cout << "Intercept: " << intercept << endl;


    double a, b, C;
    for (auto &point : data) {
    if (point.x == 0 || point.y == 0) {
        point.x = 0.000000000001; // Ganti dengan nilai epsilon kecil
        point.y = 0.000000000001; // Ganti dengan nilai epsilon kecil
    }
}
    powerRegression(data, a, b, C);

    cout << "\nPower Regression:" << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "C: " << C << endl;


    return 0;
}
