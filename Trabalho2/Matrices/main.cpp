#include <chrono>
#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <vector>
#include <bits/stdc++.h>

std::mt19937 rng;
int seed = 0;

int random(const int i, const int c, const int min, const int max) {
    rng.seed(seed + (i + 1) * (c + 1));
    std::uniform_int_distribution distribution(min, max);
    return distribution(rng);
}

int main() {
    const int N = 1000;
    const auto before = std::chrono::high_resolution_clock::now();
    int A[N*N] = { 0 }, B[N*N] = { 0 }, C[N*N] = { 0 };


    for (int i = 0; i < N; i++) {
        A[i] = random(i, 0, 0, 1000);
        B[i] = random(i, 1, 0, 1000);
    }

    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                C[(j-1) * N +i - 1] += A[(j-1) * N +i - 1] * B[(j-1) * N +i - 1];
            }
        }
    }
    const auto after = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::seconds>(after - before).count() <<
            " second(s)" << std::endl;
    return 0;
}
