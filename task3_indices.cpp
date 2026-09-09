#include <iostream>
#include <vector>
using namespace std;


vector<int> findAllIndices(const vector<int>& arr, int key) {
    vector<int> indices;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == key) {
            indices.push_back(i);
        }
    }
    return indices;
}

void print(const vector<int>& v) {
    cout << "{";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << "}";
}

int main() {
    vector<int> arr;
    arr.push_back(4);
    arr.push_back(7);
    arr.push_back(4);
    arr.push_back(9);
    arr.push_back(4);

    cout << "Test 1 - multiple occurrences" << endl;
    cout << "  array = {4, 7, 4, 9, 4}, key = 4" << endl;
    cout << "  result = ";
    print(findAllIndices(arr, 4));
    cout << "   expected {0, 2, 4}" << endl;

    cout << "Test 2 - key not present" << endl;
    cout << "  array = {4, 7, 4, 9, 4}, key = 99" << endl;
    cout << "  result = ";
    print(findAllIndices(arr, 99));
    cout << "   expected {}" << endl;


    vector<int> empty;
    cout << "Test 3 - empty array" << endl;
    cout << "  array = {}, key = 4" << endl;
    cout << "  result = ";
    print(findAllIndices(empty, 4));
    cout << "   expected {}" << endl;

    return 0;
}