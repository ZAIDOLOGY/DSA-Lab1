#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef vector< vector<int> > Matrix;


Matrix naiveMultiply(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}


Matrix addM(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subM(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}


Matrix getQuadrant(Matrix M, int rowStart, int colStart, int size) {
    Matrix Q(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            Q[i][j] = M[rowStart + i][colStart + j];
    return Q;
}


Matrix strassenMultiply(Matrix A, Matrix B) {
    int n = A.size();

    if (n == 1) {                       
        Matrix C(1, vector<int>(1, A[0][0] * B[0][0]));
        return C;
    }

    int h = n / 2;                      

  
    Matrix A11 = getQuadrant(A, 0, 0, h);
    Matrix A12 = getQuadrant(A, 0, h, h);
    Matrix A21 = getQuadrant(A, h, 0, h);
    Matrix A22 = getQuadrant(A, h, h, h);

    Matrix B11 = getQuadrant(B, 0, 0, h);
    Matrix B12 = getQuadrant(B, 0, h, h);
    Matrix B21 = getQuadrant(B, h, 0, h);
    Matrix B22 = getQuadrant(B, h, h, h);

   
    Matrix M1 = strassenMultiply(addM(A11, A22), addM(B11, B22));
    Matrix M2 = strassenMultiply(addM(A21, A22), B11);
    Matrix M3 = strassenMultiply(A11, subM(B12, B22));
    Matrix M4 = strassenMultiply(A22, subM(B21, B11));
    Matrix M5 = strassenMultiply(addM(A11, A12), B22);
    Matrix M6 = strassenMultiply(subM(A21, A11), addM(B11, B12));
    Matrix M7 = strassenMultiply(subM(A12, A22), addM(B21, B22));

    
    Matrix C11 = addM(subM(addM(M1, M4), M5), M7);
    Matrix C12 = addM(M3, M5);
    Matrix C21 = addM(M2, M4);
    Matrix C22 = addM(subM(addM(M1, M3), M2), M6);

   
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            C[i][j]         = C11[i][j];
            C[i][j + h]     = C12[i][j];
            C[i + h][j]     = C21[i][j];
            C[i + h][j + h] = C22[i][j];
        }
    }
    return C;
}

void printMatrix(Matrix M) {
    for (int i = 0; i < (int)M.size(); i++) {
        cout << "    ";
        for (int j = 0; j < (int)M[i].size(); j++) {
            cout << M[i][j] << "\t";
        }
        cout << endl;
    }
}

bool sameMatrix(Matrix A, Matrix B) {
    for (int i = 0; i < (int)A.size(); i++)
        for (int j = 0; j < (int)A.size(); j++)
            if (A[i][j] != B[i][j]) return false;
    return true;
}

int main() {
   
    Matrix A(2, vector<int>(2));
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    Matrix B(2, vector<int>(2));
    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

    cout << "Test 1 - 2x2 multiplication" << endl;
    cout << "  Strassen result:" << endl;
    printMatrix(strassenMultiply(A, B));
    cout << "  Naive result:" << endl;
    printMatrix(naiveMultiply(A, B));
    if (sameMatrix(strassenMultiply(A, B), naiveMultiply(A, B)))
        cout << "  Both methods agree." << endl;
    else
        cout << "  MISMATCH!" << endl;

 
    Matrix C(4, vector<int>(4));
    Matrix D(4, vector<int>(4));
    int value = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = value;
            value++;
            if (i == j) D[i][j] = 2;
            else        D[i][j] = 1;
        }
    }

    cout << endl << "Test 2 - 4x4 multiplication" << endl;
    cout << "  Strassen result:" << endl;
    printMatrix(strassenMultiply(C, D));
    if (sameMatrix(strassenMultiply(C, D), naiveMultiply(C, D)))
        cout << "  Both methods agree." << endl;
    else
        cout << "  MISMATCH!" << endl;

    cout << endl << "Test 3 - random 4x4 matrices" << endl;
    srand(42);
    bool allMatch = true;
    for (int test = 0; test < 5; test++) {
        Matrix R1(4, vector<int>(4));
        Matrix R2(4, vector<int>(4));
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                R1[i][j] = rand() % 10;
                R2[i][j] = rand() % 10;
            }
        }
        if (sameMatrix(strassenMultiply(R1, R2), naiveMultiply(R1, R2))) {
            cout << "  random test " << (test + 1) << ": match" << endl;
        } else {
            cout << "  random test " << (test + 1) << ": MISMATCH" << endl;
            allMatch = false;
        }
    }
    if (allMatch) cout << "  All random tests passed." << endl;

    return 0;
}