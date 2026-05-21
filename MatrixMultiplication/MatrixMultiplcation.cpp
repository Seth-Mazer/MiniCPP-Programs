#include <vector>
#include <stdexcept>
#include <iostream>

// Multiplies A in R^(MxN) by B in R^(NxP), returning C in R^(MxP).
// Uses row-scaling (ikj) loop order for cache efficiency.
std::vector<std::vector<double>> multiply(const std::vector<std::vector<double>>&A,
    const std::vector<std::vector<double>>&B) {

    //Checking if A or B are empty, before multiplication.
    if (A.empty() || A[0].empty() || B.empty() || B[0].empty()) {
        throw std::invalid_argument("Matrix is empty or has empty dimensions.");
    }

    // Verify A is rectangular
    size_t colA = A[0].size();
    for (size_t i = 0; i < A.size(); i++) {
        if (A[i].size() != colA) {
            throw std::invalid_argument("Matrix A is jagged.");
        }
    }

    // Verify B is rectangular
    size_t colB = B[0].size();
    for (size_t i = 0; i < B.size(); i++) {
        if (B[i].size() != colB) {
            throw std::invalid_argument("Matrix B is jagged.");
        }
    }

    //Checking each matrices dimensions.
    if (colA != B.size()) {
        throw std::invalid_argument("Incompatible matrix dimensions.");
    }

    // //Initializing matrix C, with dimensions R^(MxP)
    std::vector<std::vector<double>> C(A.size(), std::vector<double>(B[0].size()));

    //Multiplying via row-scaling
    //For each row in A
    for (size_t i = 0, rowA = A.size(); i < rowA; i++) {
        // Scale row q of B by A[i][q]
        for (size_t q = 0, rowB = B.size(); q < rowB; q++) {
            // Accumulate the scaled row into row i of C
            for (size_t j = 0; j < colB; j++) {
                C[i][j] += A[i][q] * B[q][j];
            }
        }
    }

    return C;
}

//This main function is largely irrelevant, was mainly used so I can grasp how I'm actually gonna write the math function
//Eventually I'm going to put the multiply function into a library, so frankly this main function is irrelevant
int main() {

    //I'm using std::vector<std::vector<double>>, because it's just simpler for me to implement at the moment. Ik you
    //could do the flattened vector
    //I am also aware I can just directly write the values in each matrix, I am choosing not to for my own clarity
    //Im trying to understand how these math objects are treated in CPP

    //Rows of Matrix A; R7 => A in R^(3x7)
    const std::vector<double> a1 = {4.7, 1.3, 8.9, 2.1, 6.5, 3.8, 7.2};
    const std::vector<double> a2 = {9.4, 5.6, 2.7, 8.1, 1.9, 6.3, 4.0};
    const std::vector<double> a3 = {3.5, 7.8, 1.2, 9.6, 4.4, 2.9, 8.0};

    //Matrix A
    std::vector<std::vector<double>> A =
        {a1,
        a2,
        a3};

    //Rows of Matrix B; R3 => B in R^(7x3)
    const std::vector<double> b1 = {4,17,92};
    const std::vector<double> b2 = {31,58,7};
    const std::vector<double> b3 = {83,12,46};
    const std::vector<double> b4 = {25,99,64};
    const std::vector<double> b5 = {71,3,32};
    const std::vector<double> b6 = {81,3,88};
    const std::vector<double> b7 = {81,3,82};

    //Matrix B
    std::vector<std::vector<double>> B =
        {b1,
        b2,
        b3,
        b4,
        b5,
        b6,
        b7};

    //Multiplying A,B, and creating C
    std::vector<std::vector<double>> C = multiply(A,B);

    //Printing out C to the console
    for (size_t i = 0; i < C.size(); ++i) {
        for (size_t j = 0; j < C[i].size(); ++j) {
            std::cout << C[i][j] << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}
