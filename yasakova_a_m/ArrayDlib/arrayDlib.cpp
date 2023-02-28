#include "arrayDlib.h"
#include <cassert>

arrayD::arrayD() {
    size = 0;
    capacity = 2;
    arr = new int[capacity];
}
arrayD::arrayD(int initial_size) {
    size = 0;
    capacity = initial_size;
    arr = new int[capacity];
}
arrayD::arrayD(const arrayD &other) {
    size = other.size;
    capacity = other.capacity;
    arr = new int[capacity];
    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}
arrayD::~arrayD() {
    delete[] arr;
}
int arrayD::get_size() {
    return size;
}
int arrayD::get_capacity() {
    return capacity;
}
void arrayD::push_back(int element) {
    if (size == capacity) {
        capacity *= 2;
        int *new_arr = new int[capacity];
        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }
    arr[size] = element;
    size++;
}
void arrayD::pop_back() {
    if (size > 0) {
        size--;
        if (size < capacity / 2) {
            capacity /= 2;
            int *new_arr = new int[capacity];
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
    }
}
int& arrayD::operator[](int index) {
    assert(index>= 0 && index < capacity);
    return arr[index];
}
arrayD& arrayD::operator=(const arrayD &other) {
    if (this != &other) {
        size = other.size;
        capacity = other.capacity;
        int *new_arr = new int[capacity];
        for (int i = 0; i < size; i++) {
            new_arr[i] = other.arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }
    return *this;
}


