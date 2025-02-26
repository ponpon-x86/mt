#include <execution>
#include <algorithm>
#include <vector>

#include "matrix.hpp"
#include "array.hpp"

void matrixExperiment() {
    Matrix<double> m1(8, 100);
    Matrix<double> m2(100, 500);

    std::cout << "\tMT: ";
    common::measureTime([&m1, &m2]{
        m1 * m2;
    });

    std::cout << "\tST: ";
    common::measureTime([&m1, &m2]{
        m1.multiply_single_thread(m2);
    });
}

void sortExperiment() {
    Array<int> a1(1000000);
    Array<int> a2 = a1;
    Array<int> a3 = a1;

    std::cout << "\tST: ";
    common::measureTime([&a1]{
        a1.sort_single_thread();
    });

    std::cout << "\tMT: ";
    common::measureTime([&a2]{
        a2.sort_multi_thread();
    });
}

int main(int argc, char *argv[]) {
    sortExperiment();
    return 0;
}