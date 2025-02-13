#include "matrix.hpp"

int main(int argc, char *argv[]) {
    Matrix m1({ { 4,3 }, { 8,3 } });
    Matrix m2({ { 9,3 }, { 5,7 } });

    std::cout << m1 * m2;
    return 0;
}