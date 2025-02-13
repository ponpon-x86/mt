#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "misc.h"

class Matrix {
    public:

    Matrix(const unsigned rows, const unsigned columns);
    Matrix(const std::vector< std::vector<double> > m);
    Matrix() = delete;
    ~Matrix() = default;

    const unsigned rows() const;
    const unsigned columns() const;

    const std::vector<double> getRow(const unsigned row) const;
    const std::vector<double> getColumn(const unsigned column) const;
    const std::vector< std::vector<double> > getMatrix() const;

    Matrix operator=(const std::vector< std::vector<double> > m);
    Matrix operator*(const Matrix& m);

    private:

    std::vector< std::vector<double> > matrix;
    friend std::ostream & operator<<(std::ostream &os, const Matrix& m);
};