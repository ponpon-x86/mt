#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <future>

#include <chrono>

#include "misc.h"
#include "rng.hpp"

class Matrix {
    public:

    Matrix(const unsigned rows, const unsigned columns);
    Matrix(const std::vector< std::vector<double> > m);
    Matrix() = delete;
    ~Matrix() = default;

    Matrix(Matrix&& other) noexcept
    : matrix(std::move(other.matrix)),
    futures(std::move(other.futures)) {
        
    }

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            matrix = std::move(other.matrix);
            futures = std::move(other.futures);
        }
        return *this;
    }

    const unsigned rows() const;
    const unsigned columns() const;

    const std::vector<double> getRow(const unsigned row) const;
    const std::vector<double> getColumn(const unsigned column) const;
    const std::vector< std::vector<double> > getMatrix() const;

    Matrix operator*(const Matrix& m);
    Matrix multiply_single_thread(const Matrix& m);
    Matrix multiply_multi_thread(const Matrix& m);

    private:

    RNG rng;
    std::vector< std::vector<double> > matrix;
    std::vector< std::future < std::vector<double> > > futures;

    std::vector<double> computeRow(const std::vector<double> row, const Matrix& m) const;

    friend std::ostream & operator<<(std::ostream &os, const Matrix& m);
};