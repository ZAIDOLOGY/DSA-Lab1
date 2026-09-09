#include <iostream>
#include <vector>
#include <map>
using namespace std;


vector<int> findModes(vector<int> arr) {
    vector<int> modes;
    if (arr.size() == 0) {
        return modes;
    }

   
    map<int, int> count;
    for (int i = 0; i < (int)arr.size(); i++) {
        count[arr[i]]++;
    }

    int highest = 0;
    map<int, int>::iterator it;
    for (it = count.begin(); it != count.end(); it++) {
        if (it->second > highest) {
            highest = it->second;
        }
    }

    
    for (it = count.begin(); it != count.end(); it++) {
        if (it->second == highest) {
            modes.push_back(it->first);
        }
    }
    return modes;
}

void print(vector<int> v) {
    cout << "{";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << "}";
}

int main() {
 
    vector<int> a;
    a.push_back(3); a.push_back(7); a.push_back(3);
    a.push_back(1); a.push_back(3);
    cout << "Test 1 - unique mode" << endl;
    cout << "  array = {3, 7, 3, 1, 3}" << endl;
    cout << "  mode  = "; print(findModes(a)); cout << "   expected {3}" << endl;

    
    vector<int> b;
    b.push_back(5); b.push_back(2); b.push_back(5);
    b.push_back(2); b.push_back(8);
    cout << "Test 2 - multiple modes" << endl;
    cout << "  array = {5, 2, 5, 2, 8}" << endl;
    cout << "  mode  = "; print(findModes(b)); cout << "   expected {2, 5}" << endl;

  
    vector<int> c;
    cout << "Test 3 - empty array" << endl;
    cout << "  array = {}" << endl;
    cout << "  mode  = "; print(findModes(c)); cout << "   expected {}" << endl;

    return 0;
}