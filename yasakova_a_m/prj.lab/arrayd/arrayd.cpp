#include <arrayd/arrayd.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

ArrayD::ArrayD() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

ArrayD::ArrayD(const ArrayD& other) {
    size_ = other.size_;
    capacity_ = other.size_;
    data_ = new double[other.capacity_];
    for (ptrdiff_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    delete[] data_;
}
ArrayD::ArrayD(const std::ptrdiff_t sizeInp, const double num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = num;
    }
}
ArrayD::ArrayD(const std::ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new double[sizeInp];
    for (std::ptrdiff_t i = 0; i < ssize(); i++) {
        data_[i] = 0;
    }
}
void ArrayD::resize(const std::ptrdiff_t sizeInp) { // посмтори const в hader
    if (sizeInp < 0) {
        throw std::out_of_range("Size must be positive");
    }
    else if(sizeInp > capacity_){
        ptrdiff_t new_capacity = std::max(sizeInp, ssize() * 2);
        double* temp = new double[new_capacity];
        for (ptrdiff_t i = 0; i < ssize(); ++i) {
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = new_capacity;
    }
    else{
        ptrdiff_t new_capacity = sizeInp;
        double* temp = new double[sizeInp];
        for (ptrdiff_t i = 0; i < sizeInp; ++i) {
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = new_capacity;
    }
    size_ = sizeInp;
}

ArrayD::~ArrayD()
{
    delete[] data_;
}

double& ArrayD::operator[] (const ptrdiff_t index) {
    if ((index < 0) || (index >= ssize())) {
        throw std::out_of_range("Index is out of acceptable area");
    }
    return data_[index];
}
const double& ArrayD::operator[] (const ptrdiff_t index) const {
    if ((index < 0) || (index >= ssize())) {
        throw std::out_of_range("Index is out of acceptable area");
    }
        return data_[index];
}
std::ptrdiff_t ArrayD::ssize() const noexcept {
    return size_;
};


void ArrayD::remove(std::ptrdiff_t i) {
    if ((i < 0) || (i > ssize())) {
        throw std::out_of_range("index out of range");
    }
    for (std::ptrdiff_t start = i + 1; i < ssize(); ++i) {
        data_[start-1] = data_[start];
    }
    resize(ssize() - 1);
}


void ArrayD::insert(const std::ptrdiff_t i, const double value) {
    if (i < 0 || i > ssize()) {
        throw std::out_of_range("index must be larger 0");
    }
    resize(ssize() +1);
    for (ptrdiff_t index = ssize() - 1; index > i; --index) {
        data_[index] = data_[index - 1];
    }
    data_[i] = value;
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;
    data_ = new double[capacity_];
    for (ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs) {
    return rhs.writeto(ostrm);
}

std::ostream& ArrayD::writeto(std::ostream& ostrm) const
{
    ostrm << '[';
    for (ptrdiff_t i = 0; i < ssize() - 1; ++i) {
        ostrm << data_[i] << cmm;
    }
    ostrm << data_[ssize() - 1] << ']';
    return ostrm;
}
