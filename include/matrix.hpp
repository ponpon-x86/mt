#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <future>

#include <chrono>

#include "misc.h"
#include "rng.hpp"

template<typename T>
class Matrix {
    public:
    Matrix(const unsigned rows, const unsigned columns) {
        common::fill(matrix, rows, columns);
    };

    Matrix(const std::vector< std::vector<T> > m) {
        if (m.size() == 0) return;
        unsigned columns = m.front().size();
        for (auto& row : matrix) {
            unsigned count = 0;
            for (unsigned i = 1; i < row.size(); ++i) {
                ++count;
            }
            if (count != columns) {
                std::cout << "\tMatrix::Matrix /// the number of columns does not match. Returning an empty matrix...\n";
                return;
            }
        }
        matrix = m;
    };

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

    const std::vector<T> getRow(const unsigned row) const;
    const std::vector<T> getColumn(const unsigned column) const;
    const std::vector< std::vector<T> > getMatrix() const;

    Matrix operator*(const Matrix& m);
    Matrix multiply_single_thread(const Matrix& m);
    Matrix multiply_multi_thread(const Matrix& m);

    private:

    RNG rng;
    std::vector< std::vector<T> > matrix;
    std::vector< std::future < std::vector<T> > > futures;

    std::vector<T> computeRow(const std::vector<T> row, const Matrix& m) const;

    friend std::ostream & operator<<(std::ostream &os, const Matrix& m);
};

template <typename T>
const unsigned Matrix<T>::rows() const {
    unsigned count = 0;
    for (auto& row : matrix) {
        ++count;
    }
    return count;
}

template <typename T>
const unsigned Matrix<T>::columns() const {
    unsigned count;
    if (this->rows() == 0) {
        std::cout << "\tMatrix::columns /// there are no rows in the matrix, chief. returning 0...\n";
        return 0;
    }
    
    unsigned reg = matrix.front().size();
    for (auto& row : matrix) {
        count = 0;
        for (auto& col : row) {
            ++count;
        }
        if (count != reg) {
            std::cout << "\tMatrix::Matrix /// the number of columns does not match. returning 0...\n";
            return 0;
        }
    }
    
    return count;
}

template <typename T>
const std::vector<T> Matrix<T>::getRow(const unsigned row) const {
    std::vector<T> result;
    if (row > this->rows() - 1) {
        std::cout << "\tMatrix::getRow /// requesting an out-of-scope row. returning an empty vector...\n";
        return result;
    }
    auto& r = matrix.at(row);
    for (auto& el : r) {
        result.push_back(el);
    }
    return result;
}

template <typename T>
const std::vector<T> Matrix<T>::getColumn(const unsigned column) const {
    std::vector<T> result;
    if (column > this->columns() - 1) {
        std::cout << "\tMatrix::getColumn /// requesting an out-of-scope column. returning an empty vector...\n";
        return result;
    }
    for (auto& r : matrix) {
        result.push_back(r.at(column));
    }
    return result;
}

template <typename T>
std::vector<T> Matrix<T>::computeRow(const std::vector<T> row, const Matrix& m) const {
    std::vector<T> new_row;
    for (unsigned i = 0; i < m.columns(); ++i) {
        new_row.push_back(common::dotProduct(row, m.getColumn(i)));
    }
    return new_row;
}

template <typename T>
Matrix<T> Matrix<T>::multiply_single_thread(const Matrix& m) {
    std::vector < std::vector<T> > result;
    if (this->columns() != m.rows()) {
        std::cout << "\tMatrix::operator* /// ok so there's this thing about matrixes,\n\t" <<
            "regarding their dimensions and dimensions of the result, MxN x NxP = MxP\n\t" <<
            "this uh. this is not the case here, chief. returning an empty matrix.\n";
        return Matrix(result);
    }

    for (auto& row : this->matrix) {
        std::vector<T> new_row;
        for (unsigned i = 0; i < m.columns(); ++i) {
            new_row.push_back(common::dotProduct(row, m.getColumn(i)));
        }
        result.push_back(new_row);
    }

    return Matrix(result);
}

template <typename T>
Matrix<T> Matrix<T>::multiply_multi_thread(const Matrix& m) {
    return *this * m;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& m) {
    std::vector < std::vector<T> > result;
    if (this->columns() != m.rows()) {
        std::cout << "\tMatrix::operator* /// ok so there's this thing about matrixes,\n\t" <<
            "regarding their dimensions and dimensions of the result, MxN x NxP = MxP\n\t" <<
            "this uh. this is not the case here, chief. returning an empty matrix.\n";
        return Matrix(result);
    }

    for (auto& row : this->matrix) {
        /*
        futures.push_back(std::async(std::launch::async, [this, row, &m]() {
            return this->computeRow(row, m);
        }));
        */
       futures.push_back(std::async(std::launch::async, &Matrix::computeRow, this, std::ref(row), std::ref(m)));
    }

    for (auto& future : futures) {
        result.push_back(future.get());
    }

    return Matrix(result);
}

template <typename T>
const std::vector< std::vector<T> > Matrix<T>::getMatrix() const {
    return matrix;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const Matrix<T>& m)
{
    std::string output = "\t[ ";
    for (auto& row : m.getMatrix()) {
        for (auto& el : row) {
            output += std::to_string(el);
            if (el != row.back()) output += "\t";
            else if (row != m.getMatrix().back()) output += " ]\n\t[ ";
            else output += " ]\n";
        }
    }
    return os << output;
}