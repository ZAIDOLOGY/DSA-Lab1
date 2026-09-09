#include <iostream>
#include <string>
using namespace std;


int naiveSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) {
        return 0;       
    }
    if (m > n) {
        return -1;      
    }

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i;   
        }
    }
    return -1;
}

int main() {
    string text = "algorithms are fun";
    cout << "Text: \"" << text << "\"" << endl << endl;

    cout << "Test 1 - pattern at beginning" << endl;
    cout << "  pattern \"algo\" -> " << naiveSearch(text, "algo") << "   expected 0" << endl;

    cout << "Test 2 - pattern at end" << endl;
    cout << "  pattern \"fun\"  -> " << naiveSearch(text, "fun") << "   expected 15" << endl;

    cout << "Test 3 - pattern not present" << endl;
    cout << "  pattern \"xyz\"  -> " << naiveSearch(text, "xyz") << "   expected -1" << endl;

    cout << "Test 4 - empty pattern" << endl;
    cout << "  pattern \"\"     -> " << naiveSearch(text, "") << "   expected 0" << endl;

    return 0;
}