#include "matrix.hpp"

int main(int argc, char *argv[]) {
    /*
    Matrix m1({ { 4,3,3 }, { 8,3,3 } });
    Matrix m2({ { 9,3 }, { 5,7 }, { 1,6.6 } });
    */

    Matrix m1(8, 100);
    Matrix m2(100, 500);
    std::cout << "\tMT: ";
    m1 * m2;
    std::cout << "\tST: ";
    m1.multiply_single_thread(m2);
    return 0;
}