#pragma once

template<typename T>
class Vec {
public:
    Vec() {};
    Vec(unsigned size) {
        this->capacity = size * 2;
        ptr = new T[capacity];
        this->size = size;
    }
    Vec(unsigned size, unsigned val) {
        this->capacity = size * 2;
        ptr = new T[capacity];
        for(int i = 0; i < size; ++i)
            ptr[i] = val;
    }
    Vec(const Vec& other) {
        ptr = other.ptr;
        size = other.ptr;
        capacity = other.capacity;
    }
    Vec(Vec&& other) :
    ptr(std::move(other.ptr)),
    size(other.size),
    capacity(other.capacity) {

    }
    Vec& operator=(const Vec& other) {
        if (this != &other) {
            ptr = other.ptr;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }
    Vec& operator=(Vec&& other) {
        if (this != &other) {
            ptr = std::move(other.ptr);
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }
    ~Vec() {
        delete[] ptr;
    }

    void pushBack(T element) {
        if (size >= capacity) {
            auto new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* temp = new T[new_capacity];

            for (unsigned i = 0; i < size; ++i) {
                temp[i] = ptr[i];
            }

            delete[] ptr;
            ptr = temp;
            capacity = new_capacity;
        }
        
        ptr[size] = element;
        ++size;
    }
    void popBack() {
        if (size > 0) {
            ptr[size - 1].~T();
            --size;
        }
    }

    unsigned size() {
        return size;
    }
    unsigned capacity() {
        return capacity;
    }

    bool empty() {
        if (size == 0) return true;
        return false;
    }

    void resize(unsigned new_size) {
        if (new_size >= capacity) {
            auto new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* temp = new T[new_capacity];

            for (unsigned i = 0; i < size; ++i) {
                temp[i] = ptr[i];
            }

            delete[] ptr;
            ptr = temp;
            capacity = new_capacity;
        }

        if (new_size < size) { // 0 1 2 3 4 5 size = 6, new_size = 2
            for (auto i = new_size; i < size; ++i) {
                popBack();
            }

            capacity = size * 2;
        }
    }
    void reserve(unsigned new_capacity) {
        if (new_capacity <= capacity) return;
    
        T* temp = new T[new_capacity];
    
        for (unsigned i = 0; i < size; ++i) {
            temp[i] = ptr[i];
        }
    
        delete[] ptr;
        ptr = temp;
        capacity = new_capacity;
    }
private:
    T* ptr;
    unsigned size;
    unsigned capacity;
};