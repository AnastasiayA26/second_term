#ifndef PROGRAMMING_ARRAYD_H
#define PROGRAMMING_ARRAYD_H

#include <iosfwd>
#include <cstdint>

class ArrayD{
public:
    ArrayD();
    ArrayD(const ArrayD&);

    ~ArrayD();

    double& operator[](ptrdiff_t index);
    const double& operator[](ptrdiff_t index) const;

    void insert(const ptrdiff_t i, const double value);
    void resize(ptrdiff_t new_size);
    void push_back(double newElement);
    double pop_back();
    void remove(const ptrdiff_t i);
    ptrdiff_t ssize() const noexcept;

    ArrayD& operator=(const ArrayD& rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

private:
    ptrdiff_t size_;
    ptrdiff_t capacity_;
    double* data_;

    static const char cmm{ ',' };
};

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

#endif //PROGRAMMING_ARRAYD_H