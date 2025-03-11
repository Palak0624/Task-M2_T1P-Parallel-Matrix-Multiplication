#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 500;

int main() {
    srand(time(0));

    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N, 0));

    // Initialize matrices
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    auto start = high_resolution_clock::now();

    #pragma omp parallel for schedule(static) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken for parallel (OpenMP) multiplication: " << duration.count() << " ms" << endl;

    ofstream outFile("output_parallel_openmp.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outFile << C[i][j] << " ";
        }
        outFile << endl;
    }

    outFile.close();
    return 0;
}
