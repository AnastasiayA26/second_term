#include <arrayd/arrayd.h>
#include <iostream>
#include <string>

ArrayD::ArrayD() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

ArrayD::ArrayD(const ArrayD& other) {
    size_ = other.size_;
    capacity_ = other.size_;
    data_ = new double[capacity_];
    for (ptrdiff_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    delete[] data_;
}
void ArrayD::resize(const ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Size must be positive");
    }
    else if(sizeInp > capacity_){
        ptrdiff_t new_capacity = std::max(sizeInp, size_ * 2);
        double* temp = new double[new_capacity];
        for (ptrdiff_t i = 0; i < size_; ++i) {
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

[[nodiscard]] double& ArrayD::operator[] (const ptrdiff_t index) {
    if ((index < 0) || (index >= capacity_)) {
        throw std::invalid_argument("Index is out of acceptable area");
    }
    else {
        return data_[index];
    }
}
[[nodiscard]] const double& ArrayD::operator[] (const ptrdiff_t index) const {
    if ((index < 0) || (index >= capacity_)) {
        throw std::invalid_argument("Index is out of acceptable area");
    }
    else {
        return data_[index];
    }
}
ptrdiff_t ArrayD::ssize() const noexcept {
    return size_;
};

void ArrayD::push_back(const double newElem) {
    if (size_ == capacity_) {
        resize(static_cast<ptrdiff_t>(size_ + 1));
    }
    data_[size_ - 1] = newElem;
}

double ArrayD::pop_back() {
    double tmp = data_[size_ - 1];
    resize(size_ - 1);
    return tmp;
}
void ArrayD::remove(const ptrdiff_t i) {
    if ((i < 0) || (i > capacity_)) {
        throw std::invalid_argument("index out of range");
    }
    else {
        size_ -= 1;
        double* temp = new double[size_];
        for (ptrdiff_t index = 0; index < i; ++index) {
            temp[index] = data_[index];
        }
        for (ptrdiff_t index = i + 1; index <= (size_); ++index) {
            temp[index] = data_[index];
        }
        delete[] data_;
        data_ = temp;
        capacity_ -= 1;
    }
}

void ArrayD::insert(const ptrdiff_t i, const double value) {
    if (i < 0) {
        throw std::invalid_argument("index must be larger 0");
    }
    else {
        resize(size_ + 1);
        for (ptrdiff_t index = size_ - 1; index > i; --index) {
            data_[index] = data_[index - 1];
        }
        data_[i] = value;
        std::cout << "element was inserted" << std::endl;
    }
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;
    data_ = new double[capacity_];
    for (ptrdiff_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs) {
    return rhs.writeTo(ostrm);
}

std::ostream& ArrayD::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (ptrdiff_t i = 0; i < size_ - 1; ++i) {
        ostrm << data_[i] << cmm;
    }
    ostrm << data_[size_ - 1] << ']';
    return ostrm;
}