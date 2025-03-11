#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 500;

void multiplyMatrices(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(0));

    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N));

    // Initialize matrices with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    auto start = high_resolution_clock::now();
    multiplyMatrices(A, B, C);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken for sequential multiplication: " << duration.count() << " ms" << endl;

    // Write output to file
    ofstream outFile("output_sequential.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outFile << C[i][j] << " ";
        }
        outFile << endl;
    }

    outFile.close();
    return 0;
}