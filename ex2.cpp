#include <iostream>


void vectorAddition(float* C, const float* A, const float* B, size_t n) {
    for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }
}

int main(int argc, char** argv){

    float* A = new float[4];
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    A[3] = 4;

    float* B = new float[4];
    B[0] = 4;
    B[1] = 3;
    B[2] = 2;
    B[3] = 1;

    float* C = new float[4];

    int n = 4;

    vectorAddition(C, A, B, n);

    for (int i = 0; i < n; i++) {
        std::cout << C[i] << " " << std::endl;
    }
}