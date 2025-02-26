#pragma once

#include "matrix.hpp"
#include "array.hpp"

template <typename...> class Starter;

template<typename A, typename B>
class Starter<A, B> {
public:
    Starter() = delete;

    Starter(
        unsigned m_M,   // rows of first M
        unsigned m_N,   // cols and rows of second M
        unsigned m_P,   // cols of second M
        unsigned a_N    // size of array
    )
    : matrices{ Matrix<A>(m_M, m_N), Matrix<A>(m_N, m_P) }, 
    arrays{ Array<B>(a_N), Array<B>(a_N) } {
        
    }

    Starter(Starter&& other) : 
    matrices(std::move(other.matrices)),
    arrays(std::move(other.arrays)) {

    };

    Starter(const Starter& other) {
        matrices = other.matrices;
        arrays = other.arrays;
    }

    Starter& operator=(const Starter& other) {
        if (this != other) {
            matrices = other.matrices;
            arrays = other.arrays;
        }
        return *this;
    };

    Starter& operator=(Starter&& other) {
        if (this != &other) {
            matrices(std::move(other.matrices));
            arrays(std::move(other.arrays));
        }
        return *this;
    };

    void matrixExperiment();
    void arrayExperiment();
private:
    std::pair< Matrix<A>, Matrix<A> > matrices;
    std::pair< Array<B>, Array<B> > arrays;
};

template<typename A, typename B>
void Starter<A, B>::matrixExperiment() {
    std::cout << "\t--- Starter::matrixExperiment() fired... ---\n";
    std::cout << "\tMT: ";
    common::measureTime([this]{
        this->matrices.first * this->matrices.second;
    });

    std::cout << "\tST: ";
    common::measureTime([this]{
        this->matrices.first.multiply_single_thread(this->matrices.second);
    });
}

template<typename A, typename B>
void Starter<A, B>::arrayExperiment() {
    std::cout << "\t--- Starter::arrayExperiment() fired... ---\n";
    std::cout << "\tMT: ";
    common::measureTime([this]{
        this->arrays.second.sort_multi_thread();
    });

    std::cout << "\tST: ";
    common::measureTime([this]{
        this->arrays.first.sort_single_thread();
    });
}