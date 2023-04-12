#ifndef LIB_ARRAYT_HPP
#define LIB_ARRAYT_HPP

#include <iosfwd>
#include <iostream>
#include <cstdint>
#include <exception>

template<typename T>
class ArrayT{
public:
    ArrayT();
    ArrayT(const ArrayT<T>&);
    ArrayT(const std::ptrdiff_t sizeInp, const T num);

    ~ArrayT();

    T& operator[](ptrdiff_t index);
    const T& operator[](ptrdiff_t index) const;

    void insert(const ptrdiff_t i, const T value);
    void resize(ptrdiff_t new_size);
    void remove(const ptrdiff_t i);
    explicit ArrayT(const std::ptrdiff_t len);

    ptrdiff_t ssize() const noexcept;

    ArrayT<T>& operator=(const ArrayT<T>& rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    std::ptrdiff_t capacity_;
    T* data_;
    std::ptrdiff_t size_;
    static const char cmm{ ',' };
};

template<typename T>
ArrayT<T>::ArrayT() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}
template<typename T>
ArrayT<T>::ArrayT(const ArrayT<T>& other) {
    size_ = other.size_;
    capacity_ = other.size_;
    data_ = new double[capacity_];
    for (ptrdiff_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    delete[] data_;
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t sizeInp) {
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
template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t sizeInp, const T num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = num;
    }
}
template<typename T>
ArrayT<T>::~ArrayT()
{
    delete[] data_;
}
template<typename T>
[[nodiscard]] T& ArrayT<T>::operator[] (const ptrdiff_t index) {
    if ((index < 0) || (index >= capacity_)) {
        throw std::invalid_argument("Index is out of acceptable area");
    }
    else {
        return data_[index];
    }
}
template<typename T>
[[nodiscard]] const T& ArrayT<T>::operator[] (const ptrdiff_t index) const {
    if ((index < 0) || (index >= capacity_)) {
        throw std::invalid_argument("Index is out of acceptable area");
    }
    else {
        return data_[index];
    }
}
template<typename T>
ptrdiff_t ArrayT<T>::ssize() const noexcept {
    return size_;
};

template<typename T>
void ArrayT<T>::remove(const ptrdiff_t i) {
    if ((i < 0) || (i > capacity_)) {
        throw std::invalid_argument("index out of range");
    }
    else {
        size_ -= 1;
        T* temp = new T[size_];
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
template<typename T>
void ArrayT<T>::insert(const ptrdiff_t i, const T value) {
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

template<typename T>
void ArrayT<T>::resize(const ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Size must be positive");
    }
    else if(sizeInp > capacity_){
        ptrdiff_t new_capacity = std::max(sizeInp, ssize() * 2);
        T* temp = new T[new_capacity];
        for (ptrdiff_t i = 0; i < ssize(); ++i) {
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = new_capacity;
    }
    else{
        ptrdiff_t new_capacity = sizeInp;
        T* temp = new T[sizeInp];
        for (ptrdiff_t i = 0; i < sizeInp; ++i) {
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = new_capacity;
    }
    size_ = sizeInp;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;
    data_ = new T[capacity_];
    for (ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}
template<typename T>
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& rhs) {
    return rhs.writeTo(ostrm);
}
template<typename T>
std::ostream& ArrayT<T>::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (ptrdiff_t i = 0; i < size_ - 1; ++i) {
        ostrm << data_[i] << cmm;
    }
    ostrm << data_[size_ - 1] << ']';
    return ostrm;
}
#endif //LIB_ARRAYT_HPP

