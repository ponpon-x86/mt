#include <execution>
#include <algorithm>
#include <vector>

#include "starter.hpp"

int main(int argc, char *argv[]) {
    Starter<double, int> starter(
        8, 100, 500,
        1000000
    );
    starter.matrixExperiment();
    starter.arrayExperiment();
    // starter.producerConsumerExperiment();
    return 0;
}