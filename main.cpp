/*
 * Student name: Koichi Nakata
 * Created: February 8, 2024
 * Data from: U.S. Department of Energy - https://afdc.energy.gov/data
 * Description: The original data is sorted by the alphabetical order of state names. The function mergeSort sorts the data in the descending order of counts of EVs.
 * Algorithmic summary: Each mergeSort call will divide the array into two pieces until the piece is consisted of just one element. And the recursive function assembles the pieces in the descending order and goes back to the first call of mergeSort.
 * Runtime complexity: O(nlog2n)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void loadData(const string&, vector<pair<string, int>>&);
void merge(vector<pair<string, int>>&, int, int, int);
void mergeSort(vector<pair<string, int>>&, int, int);
void display(const vector<pair<string, int>>&);

int main() {
    string filePath = "/Users/claudio/Desktop/School/CS/LMC/COMSC210_DataStructure/Lab_Assignments/Lab2_MergeSort_ElectricVehicles/electricVehicleCountsByState.csv";
    vector<pair<string, int>> evByState;

    loadData(filePath, evByState);

    cout << "\nEV Registration Counts by State BEFORE Sort:" << endl;
    display(evByState);

    mergeSort(evByState, 0, evByState.size()-1);

    cout << "\nEV Registration Counts by State AFTER Sort:" << endl;
    display(evByState);

}

void loadData(const string& filePath, vector<pair<string, int>>& evByState) {
    fstream inputFile(filePath, ios::in); // Open file with read mode

    string line;
    // Store each line into string variable line, this looks like "state, 1234"
    while (getline(inputFile, line)) {
        // We want to convert string to sstream to use getline to separate data by comma
        stringstream convert(line);

        string state, counts;
        getline(convert, state, ',');
        getline(convert, counts, ',');

        pair<string, int> temp = {state, stoi(counts)};
        evByState.push_back(temp);
    }
    inputFile.close();
}

void merge(vector<pair<string, int>>& evByState, int i, int j, int k) {
    int left = i;
    int right = j + 1;
    vector<pair<string, int>> merged;

    while (left <= j || right <= k) {
        if (left > j) { // Left is out of index, but right is within index
            merged.push_back(evByState[right]);
            right++;
        } else if (right > k) { // Right is out of index, but left is within index
            merged.push_back(evByState[left]);
            left++;
        } else { // Both are within index, so we need to compare
            if (evByState[left].second > evByState[right].second) {
                merged.push_back(evByState[left]);
                left++;
            } else {
                merged.push_back(evByState[right]);
                right++;
            }
        }
    }
    // Copy merged into the original from the appropriate index
    for (int index = 0; index < merged.size(); index++) {
        evByState[i + index] = merged[index];
    }
}

void mergeSort(vector<pair<string, int>>& evByState, int i, int k) {
    if (i < k) { // If the piece is only 1 element, does nothing and goes back to the previous call to merge the pieces
        int j = (i + k) / 2;

        mergeSort(evByState, i, j);
        mergeSort(evByState, j + 1, k);

        // This is like a branch point returning the aggregated points
        merge(evByState, i, j, k);
    }
}

void display(const vector<pair<string, int>>& evByState) {
    for (auto pair : evByState) {
        cout << setw(20) << pair.first << ": " << setw(6) << pair.second << endl;
    }
}
