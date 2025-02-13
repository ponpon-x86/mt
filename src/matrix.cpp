#include "matrix.hpp"

Matrix::Matrix(const unsigned rows, const unsigned columns) {
    matrix.resize(rows);
    for (auto& row : matrix) {
        matrix.resize(columns);
    }
}

Matrix::Matrix(const std::vector< std::vector<double> > m) {
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
}

const unsigned Matrix::rows() const {
    unsigned count = 0;
    for (auto& row : matrix) {
        ++count;
    }
    return count;
}

const unsigned Matrix::columns() const {
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

const std::vector<double> Matrix::getRow(const unsigned row) const {
    std::vector<double> result;
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

const std::vector<double> Matrix::getColumn(const unsigned column) const {
    std::vector<double> result;
    if (column > this->columns() - 1) {
        std::cout << "\tMatrix::getColumn /// requesting an out-of-scope column. returning an empty vector...\n";
        return result;
    }
    for (auto& r : matrix) {
        result.push_back(r.at(column));
    }
    return result;
}

Matrix Matrix::operator=(const std::vector< std::vector<double> > m) {
    this->matrix = m;
    return *this;
}

Matrix Matrix::operator*(const Matrix& m) {
    std::vector < std::vector<double> > result;
    if (this->columns() != m.rows()) {
        std::cout << "\tMatrix::operator* /// ok so there's this thing about matrixes,\n\t" <<
            "regarding their dimensions and dimensions of the result, MxN x NxP = MxP\n\t" <<
            "this uh. this is not the case here, chief. returning an empty matrix.\n";
        return Matrix(result);
    }

    for (auto& row : this->matrix) {
        std::vector<double> new_row;
        for (unsigned i = 0; i < m.columns(); ++i) {
            new_row.push_back(addendum::dotProduct(row, m.getColumn(i)));
        }
        result.push_back(new_row);
    }

    return Matrix(result);
}

const std::vector< std::vector<double> > Matrix::getMatrix() const {
    return matrix;
}

std::ostream& operator<<(std::ostream &os, const Matrix& m)
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