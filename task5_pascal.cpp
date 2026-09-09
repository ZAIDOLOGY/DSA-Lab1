#include <iostream>
#include <vector>
using namespace std;


vector< vector<int> > pascalsTriangle(int n) {
    vector< vector<int> > triangle;

    for (int i = 0; i < n; i++) {
        vector<int> row(i + 1, 1);        
        for (int j = 1; j < i; j++) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
        triangle.push_back(row);
    }
    return triangle;
}

void printTriangle(vector< vector<int> > triangle) {
    if (triangle.size() == 0) {
        cout << "  (no rows)" << endl;
        return;
    }
    for (int i = 0; i < (int)triangle.size(); i++) {
        cout << "  row " << (i + 1) << ": {";
        for (int j = 0; j < (int)triangle[i].size(); j++) {
            if (j > 0) cout << ", ";
            cout << triangle[i][j];
        }
        cout << "}" << endl;
    }
}

int main() {
    cout << "Test 1 - n = 0" << endl;
    printTriangle(pascalsTriangle(0));

    cout << "Test 2 - n = 1" << endl;
    printTriangle(pascalsTriangle(1));

    cout << "Test 3 - n = 5" << endl;
    vector< vector<int> > t = pascalsTriangle(5);
    printTriangle(t);

    cout << endl << "Checking row 5 should be {1, 4, 6, 4, 1}" << endl;
    vector<int> row5 = t[4];
    bool correct = (row5.size() == 5 && row5[0] == 1 && row5[1] == 4 &&
                    row5[2] == 6 && row5[3] == 4 && row5[4] == 1);
    if (correct) {
        cout << "  Row 5 is correct." << endl;
    } else {
        cout << "  Row 5 is WRONG." << endl;
    }
    return 0;
}