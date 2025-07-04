#pragma once

#include "matrix.hpp"
#include "array.hpp"

#include "bus.hpp"
#include "producer.hpp"
#include "consumer.hpp"

template <typename...> class Starter;

template<typename A, typename B>
class Starter<A, B> {
public:
    Starter() = delete;

    Starter(
        unsigned m_M,   // rows of first M
        unsigned m_N,   // cols of first M and rows of second M
        unsigned m_P,   // cols of second M
        unsigned a_N    // size of array
    )
    : matrices{ Matrix<A>(m_M, m_N), Matrix<A>(m_N, m_P) }, 
    arrays{ Array<B>(a_N), Array<B>(a_N) }, consumer(&bus), producer(&bus) {
        
    }

    Starter(Starter&& other) : 
    matrices(std::move(other.matrices)),
    arrays(std::move(other.arrays)),
    consumer(std::move(other.consumer)),
    producer(std::move(other.producer)),
    bus(std::move(other.bus)) {

    }

    Starter(const Starter& other) {
        matrices = other.matrices;
        arrays = other.arrays;
        consumer = other.consumer;
        producer = other.producer;
        bus = other.bus;
    }

    Starter& operator=(const Starter& other) {
        if (this != &other) {
            matrices = other.matrices;
            arrays = other.arrays;
            consumer = other.consumer;
            producer = other.producer;
            bus = other.bus;
        }
        return *this;
    }

    Starter& operator=(Starter&& other) {
        if (this != &other) {
            matrices = (std::move(other.matrices));
            arrays = (std::move(other.arrays));
            consumer = (std::move(other.consumer));
            producer = (std::move(other.producer));
            bus = (std::move(other.bus));
        }
        return *this;
    }

    void matrixExperiment();
    void arrayExperiment();
    void producerConsumerExperiment();
private:
    std::pair< Matrix<A>, Matrix<A> > matrices;
    std::pair< Array<B>, Array<B> > arrays;

    Bus bus;
    Consumer consumer;
    Producer producer;
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

template<typename A, typename B>
void Starter<A, B>::producerConsumerExperiment() {
    std::cout << "\t--- Starter::producerConsumerExperiment() fired... ---\n";
    producer.start();
    consumer.start();
}