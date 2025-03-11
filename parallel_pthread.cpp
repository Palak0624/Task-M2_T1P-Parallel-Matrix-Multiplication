#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <pthread.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 500;
const int MAX_THREADS = 4;

vector<vector<int>> A(N, vector<int>(N));
vector<vector<int>> B(N, vector<int>(N));
vector<vector<int>> C(N, vector<int>(N));

int step_i = 0;

void* multiply(void* arg) {
    int core = step_i++;

    for (int i = core * N / MAX_THREADS; i < (core + 1) * N / MAX_THREADS; i++) 
    {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    srand(time(0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    pthread_t threads[MAX_THREADS];

    auto start = high_resolution_clock::now();

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, multiply, (void*)NULL);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken for parallel (pthread) multiplication: " << duration.count() << " ms" << endl;

    ofstream outFile("output_parallel_pthread.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outFile << C[i][j] << " ";
        }
        outFile << endl;
    }

    outFile.close();
    return 0;
}
