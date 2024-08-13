#include <iostream>
#include <limits.h>
using namespace std;

// Function to multiply two matrices
void multiplyMatrices(int row1, int col1, int A[][10], int row2, int col2, int B[][10], int C[][10]) {
    if (col1 != row2) {
        cout << "Matrices cannot be multiplied!" << endl;
        return;
    }
    
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to find the minimum number of scalar multiplications needed
int matrixChainOrder(int p[], int n) {
    int m[n][n];

    // m[i, j] = Minimum number of scalar multiplications needed to compute the matrix A[i]A[i+1]...A[j] = A[i..j]
    // The cost is zero when multiplying one matrix.
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    // L is chain length.
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n - 1];
}

int main() {
    int row1, col1, row2, col2;

    cout << "Enter rows and columns for first matrix: ";
    cin >> row1 >> col1;

    int A[10][10];
    cout << "Enter the elements of first matrix:" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter rows and columns for second matrix: ";
    cin >> row2 >> col2;

    int B[10][10];
    cout << "Enter the elements of second matrix:" << endl;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            cin >> B[i][j];
        }
    }

    int C[10][10];
    multiplyMatrices(row1, col1, A, row2, col2, B, C);

    cout << "Resultant Matrix after multiplication:" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    // Applying Matrix Chain Multiplication (MCM)
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;

    int p[n + 1];
    cout << "Enter the dimensions of matrices in the form of an array (e.g., for matrices A1: 10x20, A2: 20x30, enter 10 20 30): ";
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    int minCost = matrixChainOrder(p, n + 1);
    cout << "Minimum number of scalar multiplications is: " << minCost << endl;

    return 0;
}
