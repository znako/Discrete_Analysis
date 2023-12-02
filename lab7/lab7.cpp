#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <chrono>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    int rows, cols; 

    cin >> rows;
    cin >> cols;

    vector<vector<long long> > matrix(rows, vector<long long>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    vector<int> steps{-1, 0, 1};
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            long long minNeighb = LLONG_MAX;
            for (int k = 0; k < 3; k++) {
                int neighbInd = j + steps[k];
                if (neighbInd >= 0 && neighbInd < cols && matrix[i-1][neighbInd] < minNeighb) {
                    minNeighb = matrix[i-1][neighbInd];
                }
            }
            matrix[i][j] += minNeighb;
        }
    }

    long long minPenalty = matrix[rows-1][0];
    vector<pair<int, int> > coords;
    pair<int, int> minPenaltyCoords(rows, 1); 
    for (int i = 1; i < cols; i++) {
        if (matrix[rows-1][i] < minPenalty) {
            minPenalty = matrix[rows-1][i];
            minPenaltyCoords = make_pair(rows, i+1);
        }
    }
    coords.push_back(minPenaltyCoords);

    pair<int, int> currentCoords = make_pair(minPenaltyCoords.first, minPenaltyCoords.second);
    for (int i = rows - 2; i >= 0; i--) {
        long long minNeighb = LLONG_MAX;
        pair<int, int> minNeighbCoords;
        for (int k = 0; k < 3; k++) {
            int neighbInd = currentCoords.second - 1 + steps[k];
            if (neighbInd >= 0 && neighbInd < cols && matrix[i][neighbInd] < minNeighb) {
                minNeighb = matrix[i][neighbInd];
                minNeighbCoords = make_pair(i+1, neighbInd+1);
            }
        }
        currentCoords = minNeighbCoords;
        coords.push_back(minNeighbCoords);
    }

    cout << minPenalty << '\n';
    for (int i = coords.size() - 1; i >= 0; i--) {
        if (i != 0) {
            cout << '(' << coords[i].first << ',' << coords[i].second << ')' << ' ';
        }
        else {
            cout << '(' << coords[i].first << ',' << coords[i].second << ')';
        }
    }
}
