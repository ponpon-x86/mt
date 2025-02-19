#pragma once

#include <vector>
#include "rng.hpp"

namespace common {
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

    template <typename T>
    inline bool isDifferent(T a, T b) {
        if constexpr (std::is_floating_point<T>::value) {
            constexpr double EPSILON = 1e-6;
            return std::fabs(a - b) > EPSILON;
        } else {
            return a != b;
        }
    }

    template <typename T>
    inline void fill(std::vector<T>& array, unsigned size) {
        RNG rng;
        if constexpr (std::is_floating_point<T>::value) {
            for (unsigned i = 0; i < size; ++i)
                array.push_back(rng.generateDouble());
        } else {
            for (unsigned i = 0; i < size; ++i)
                array.push_back(rng.generateInt());
        }
    }

    template <typename T>
    inline void fill(std::vector< std::vector<T> >& matrix, unsigned rows, unsigned columns) {
        RNG rng;
        matrix.resize(rows);
        for (auto& row : matrix) {
            row.resize(columns);
            
            if constexpr (std::is_floating_point<T>::value) {
                for (auto& el : row)
                    el = rng.generateDouble();
            } else {
                for (auto& el : row)
                    el = rng.generateInt();
            }
        }
    }

    template<typename Func>
    inline void measureTime(Func&& func) {
        auto start = std::chrono::system_clock::now();
        func();
        auto end = std::chrono::system_clock::now();
        std::cout << "\tExecution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << ".\n";
    }

    template<typename T>
    inline void heapify(std::vector<T>& array, int size, int index) {
        int largest = index;
        // in array version of a tree,
        // this is left node:
        int left = 2 * index + 1;
        // and this is right node:
        int right = 2 * index + 2;
    
        // check if left node is largest
        if (left < size && array[left] > array[largest])
            largest = left;
        // check if right is largest
        if (right < size && array[right] > array[largest])
            largest = right;
    
        // and now, well
        // if largest changed...
        if (isDifferent(largest, index)) {
            std::swap(array[index], array[largest]);
            // ... we should heapify the whole thing
            heapify(array, size, largest);
        }
    }

    template<typename T>
    inline void heapSort(std::vector<T>& array) {
        auto size = array.size();
    
        // in a complete binary tree, all leaf nodes are in
        // the second half of the array (indices n / 2 to n - 1)
        // ... so we only heapify the first half:
        // the array represents a heap
        for (int index = size / 2 - 1; index >= 0; index--)
            heapify(array, size, index);

        // ok, then we
        for (int index = size - 1; index > 0; index--) {
            // move the root to the _current_ end
            std::swap(array[0], array[index]);
            // heapify
            heapify(array, index, 0);
            // and pray to the higher powers that this works
        }
    }
}