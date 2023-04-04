#ifndef PROGRAMMING_ARRAYD_H
#define PROGRAMMING_ARRAYD_H

#include <iosfwd>
#include <cstdint>

class ArrayD{
public:
    ArrayD();
    ArrayD(const ArrayD&);
    ArrayD(const std::ptrdiff_t sizeInp, const double num);

    ~ArrayD();

    double& operator[](ptrdiff_t index);
    const double& operator[](ptrdiff_t index) const;

    void insert(const ptrdiff_t i, const double value);
    void resize(ptrdiff_t new_size);
    void push_back(double newElement);
    double pop_back();
    void remove(const ptrdiff_t i);
    explicit ArrayD(const std::ptrdiff_t len);

    ptrdiff_t ssize() const noexcept;

    ArrayD& operator=(const ArrayD& rhs);
    ArrayD& operator+=(const double rhs);
    ArrayD& operator-=(const double rhs);
    ArrayD& operator*=(const double rhs);
    ArrayD& operator/=(const double rhs);

    ArrayD& operator+();
    ArrayD& operator-();

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    ptrdiff_t capacity_;
    double* data_;
    ptrdiff_t size_;
    static const char cmm{ ',' };
};
    ArrayD operator+(ArrayD lhs, const double rhs);
    ArrayD operator-(ArrayD lhs, const double rhs);
    ArrayD operator*(ArrayD lhs, const double rhs);
    ArrayD operator/(ArrayD lhs, const double rhs);

bool operator==(const ArrayD& lhs, const ArrayD& rhs);
bool operator!=(const ArrayD& lhs, const ArrayD& rhs);
std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

#endif //PROGRAMMING_ARRAYD_H