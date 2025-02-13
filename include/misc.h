#pragma once

#include <vector>

namespace addendum {
    inline double dotProduct(const std::vector<double> row, 
    std::vector<double> column) {
        if (row.size() != column.size()) return 0;

        unsigned size = row.size();
        double sum = 0;
        for (unsigned i = 0; i < size; ++i) {
            sum += row.at(i) * column.at(i);
        }

        return sum;
    }
}