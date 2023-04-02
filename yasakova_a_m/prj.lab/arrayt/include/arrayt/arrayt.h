#ifndef LIB_ARRAYT_H
#define LIB_ARRAYT_H

#include <iosfwd>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>

template<typename T>
class ArrayT{
public:
    ArrayT();
    ArrayT(const ptrdiff_t len);
    ArrayT(const ArrayT<T>&);
    //ArrayD(ArrayD&&) = default;
    ArrayT(ptrdiff_t sizeInp, T number);

    ~ArrayT();

    T& operator[](const ptrdiff_t index);
    const T& operator[](const ptrdiff_t index) const;

    void reserve(ptrdiff_t newCapacity_);
    void resize(ptrdiff_t newSsize_);
    void push_back(T newElement);
    double pop_back();

    ArrayT<T>& operator=(const ArrayT<T>& rhs);
    ArrayT<T>& operator+=(const T rhs);
    ArrayT<T>& operator-=(const T rhs);
    ArrayT<T>& operator*=(const T rhs);
    ArrayT<T>& operator/=(const T rhs);

    ArrayT<T>& operator+();
    ArrayT<T>& operator-();

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

private:
    ptrdiff_t ssize_;
    ptrdiff_t capacity_;
    T* memory_;

    static const char cmm{ ',' };
};
template<typename T>
ArrayT<T>::ArrayT() {
    memory_ = nullptr;
    ssize_ = 0;
    capacity_ = 0;
}
template<typename T>
ArrayT<T>::ArrayT(const ArrayT<T>& prev) {
    ssize_ = prev.ssize_;
    capacity_ = prev.capacity_;
    memory_ = new double[capacity_];
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
    }
}
template<typename T>
ArrayT<T>::ArrayT(ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    ssize_ = sizeInp;
    capacity_ = sizeInp;
    memory_ = new T[capacity_];
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] = 0;
    }
}
template<typename T>
ArrayT<T>::ArrayT(ptrdiff_t sizeInp, T num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    ssize_ = sizeInp;
    capacity_ = sizeInp;
    memory_ = new double[capacity_];
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] = num;
    }
}

template<typename T>
ArrayT<T>::~ArrayT()
{
    delete[] memory_;
}
template<typename T>
T& ArrayT<T>::operator[](ptrdiff_t index) {
    if (index < 0 || index >= ssize_) {
        throw std::out_of_range("Index out of range");
    }
    return memory_[index];
}

//const double& ArrayD::operator[](ptrdiff_t index) const{ для чего const
//    if (index < 0 || index >= ssize_) {
//        throw std::out_of_range("Index out of range");
//    }
//    return memory_[index];
//}

template<typename T>
void ArrayT<T>::reserve(ptrdiff_t newCapacity_) {
    capacity_ = newCapacity_;
    if (capacity_ < ssize_) {
        ssize_ = capacity_;
        return;
    }
    T* newMemory_ = new T[capacity_];
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        newMemory_[i] = memory_[i];
    }
    for (ptrdiff_t i = ssize_; i < capacity_; ++i) {
        newMemory_[i] = 0;
    }
    delete[] memory_;
    memory_ = newMemory_;
}

template<typename T>
void ArrayT<T>::resize(ptrdiff_t newSsize_) {
    if (newSsize_ > capacity_) {
        reserve(newSsize_);
    }
    ssize_ = newSsize_;
}

template<typename T>
void ArrayT<T>::push_back(T newElement) {
    if (ssize_ == capacity_) {
        resize(static_cast<ptrdiff_t>(ssize_ + 1));
    }
    memory_[ssize_ - 1] = newElement;
}

template<typename T>
T ArrayT<T>::pop_back() {
    T tmp = memory_[ssize_ - 1];
    resize(ssize_ - 1);
    return tmp;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
    ssize_ = rhs.ssize_;
    capacity_ = rhs.capacity_;
    delete[] memory_;
    memory_ = new T[capacity_];
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        new (memory_ + i) T (rhs.memory_[i]);
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator+=(const T rhs) {
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] += rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator-=(const T rhs) {
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] -= rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator*=(const T rhs) {
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] *= rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator/=(const T rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] /= rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator+() {
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator-() {
    for (ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] = -memory_[i];
    }
    return *this;
}
template<typename T>
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& rhs) {
    return rhs.writeTo(ostrm);
}
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs) {
//    return rhs.readFrom(istrm);
//}
template<typename T>
ArrayT<T> operator+(ArrayT<T> lhs, const T rhs) {
    lhs += rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator-(ArrayT<T> lhs, const T rhs) {
    lhs -= rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator*(ArrayT<T> lhs, const T rhs) {
    lhs *= rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator/(ArrayT<T> lhs, const T rhs) {
    lhs /= rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator%(ArrayT<T> lhs, const T& rhs)
{
    lhs %= rhs;
    return lhs;
}
template<typename T>
bool operator==(const ArrayT<T>& lhs, const ArrayT<T>& rhs) {
    if (lhs.ssize_ != rhs.ssize_) {
        return false;
    }
    bool isEqual = true;
    for (ptrdiff_t i = 0; i < lhs.ssize_; ++i) {
        isEqual *= (lhs[i] == rhs[i]);
    }
    return isEqual;
}

template<typename T>
bool operator!=(const ArrayT<T>& lhs, const ArrayT<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
std::ostream& ArrayT<T>::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (ptrdiff_t i = 0; i < ssize_ - 1; ++i) {
        ostrm << memory_[i] << cmm;
    }
    ostrm << memory_[ssize_ - 1] << ']';
    return ostrm;
}

template<typename T>
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

template<typename T>
ArrayT<T> operator+(ArrayT<T> lhs, const T rhs);

template<typename T>
ArrayT<T> operator-(ArrayT<T> lhs, const T rhs);

template<typename T>
ArrayT<T> operator*(ArrayT<T> lhs, const T rhs);

template<typename T>
ArrayT<T> operator/(ArrayT<T> lhs, const T rhs);

template<typename T>
ArrayT<T> operator%(ArrayT<T> lhs, const T& rhs);

template<typename T>
bool operator==(const ArrayT<T>& lhs, const ArrayT<T>& rhs);

template<typename T>
bool operator!=(const ArrayT<T>& lhs, const ArrayT<T>& rhs);

#endif //LIB_ARRAYT_H
