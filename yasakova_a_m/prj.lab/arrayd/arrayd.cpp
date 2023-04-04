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
ArrayD::ArrayD(const std::ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = 0;
    }
}
void ArrayD::resize(const ptrdiff_t sizeInp) {
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
    if (ssize() == capacity_) {
        resize(static_cast<ptrdiff_t>(ssize() + 1));
    }
    data_[ssize() - 1] = newElem;
}

double ArrayD::pop_back() {
    double tmp = data_[ssize() - 1];
    resize(ssize() - 1);
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

void ArrayD::insert(const ptrdiff_t i, const double value) {
    if (i < 0) {
        throw std::invalid_argument("index must be larger 0");
    }
    else {
        resize(ssize() + 1);
        for (ptrdiff_t index = ssize() - 1; index > i; --index) {
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
    for (ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

ArrayD& ArrayD::operator+=(const double rhs) {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] += rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator-=(const double rhs) {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] -= rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator*=(const double rhs) {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] *= rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator/=(const double rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] /= rhs;
    }
    return *this;
}

ArrayD& ArrayD::operator+() {
    return *this;
}
ArrayD& ArrayD::operator-() {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = -data_[i];
    }
    return *this;
}
ArrayD operator+(ArrayD lhs, const double rhs) {
    lhs += rhs;
    return lhs;
}
ArrayD operator-(ArrayD lhs, const double rhs) {
    lhs -= rhs;
    return lhs;
}
ArrayD operator*(ArrayD lhs, const double rhs) {
    lhs *= rhs;
    return lhs;
}
ArrayD operator/(ArrayD lhs, const double rhs) {
    lhs /= rhs;
    return lhs;
}

bool operator==(const ArrayD& lhs, const ArrayD& rhs) {
    if (lhs.size_ != rhs.size_) {
        return false;
    }
    bool isEqual = true;
    for (std::ptrdiff_t i = 0; i < lhs.size_; ++i) {
        isEqual &= (std::abs(lhs[i] - rhs[i]) < 0.00000001);
    }
    return isEqual;
}

bool operator!=(const ArrayD& lhs, const ArrayD& rhs) {
    return !(lhs == rhs);
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