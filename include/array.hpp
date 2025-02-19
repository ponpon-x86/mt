#pragma once

#include <vector>
#include <iostream>
#include <future>

#include "misc.h"

template<typename T>
class Array {
public:
    Array(const unsigned size) {
        common::fill(array, size);
    };
    Array(const std::vector<T> array) {
        this->array = array;
    };
    Array() = delete;
    ~Array() = default;

    Array(Array&& other) noexcept 
    : array(std::move(other.array)),
    futures(std::move(other.futures)){
        
    };

    Array(const Array& other) {
        array = other.array;
    }

    Array& operator=(const Array& other) {
        if (this != other) {
            array = other.array;
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            array = std::move(other.array);
            futures = std::move(other.futures);
        }
        return *this;
    };

    const unsigned size() const {
        return array.size();
    };

    T getElementByIndex(unsigned index) const;
    const std::vector<T> getArray() const;

    void sort();
    void sort_single_thread();
    void sort_multi_thread();
private:
    std::vector<T> array;

    std::vector< std::future<void> > futures;

    friend std::ostream& operator<<(std::ostream &os, const Array& array) {
        std::string output;

        output = "\t[ ";
        for (auto& el : array.getArray()) output += std::to_string(el) + " ";
        output += "]\n";

        return os << output;
    };
};

template<typename T>
T Array<T>::getElementByIndex(unsigned index) const {
    if (index >= this->size()) {
        std::cout << "\tArray::getElementByIndex /// the index is out array's scope, boss. returning 0...\n";
        return 0;
    }

    return array.at(index);
}

template<typename T>
const std::vector<T> Array<T>::getArray() const {
    return array;
}

template<typename T>
void Array<T>::sort_single_thread() {
    common::heapSort(array);
}

template<typename T>
void Array<T>::sort_multi_thread() {
    const unsigned threads = 4;

    // first things first,
    // split the array into almost equal parts

    std::vector< std::vector<T> > parts;

    unsigned size = array.size() / threads;
    unsigned remainder = array.size() % threads;

    auto it = array.begin();
    for (unsigned i = 0; i < threads; ++i) {
        unsigned part_size = size + (i < remainder ? 1 : 0);
        parts.push_back(std::vector<T>(it, it + part_size));
        it += part_size;
    }

    // next,
    // sort the parts

    for (auto& part : parts) {
        futures.push_back(std::async(std::launch::async, [&part](){
            common::heapSort(part);
        }));
    }

    // just in case
    for (auto& future : futures) {
        future.get(); // block
    }

    // now we need to "merge" the results, we will merge
    // f1 and f2, f3 and f4, then merge the results again

    // to speed things up, we can merge in async too

    std::vector< std::future< std::vector<T> > > halves;
    for (unsigned i = 0; i < threads; i += threads/2) {
        halves.push_back(std::async(std::launch::async, [&parts, i](){
            return common::merge(parts.at(i), parts.at(i + 1));
        }));
    }

    this->array = common::merge(halves.front().get(), halves.back().get());
}

template<typename T>
void Array<T>::sort() {
    common::heapSort(array);
}