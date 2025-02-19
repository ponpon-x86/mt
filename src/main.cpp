#include <algorithm>
#include <vector>

#include "matrix.hpp"

void matrixExperiment() {
    Matrix m1(8, 100);
    Matrix m2(100, 500);

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
    std::vector<int> array;
    common::fill(array, 200000);

    common::measureTime([&array]{
        common::heapSort(array);
    });
}

int main(int argc, char *argv[]) {
    sortExperiment();
    return 0;
}