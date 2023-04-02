#ifndef PROGRAMMING_RATIONAL_H
#define PROGRAMMING_RATIONAL_H
#include<iosfwd>
#include<cstdint>

class Rational{
public:
    Rational();
    Rational(const int32_t numInp) noexcept;
    Rational(const Rational&) = default;
    Rational(Rational&&) = default;
    Rational(int32_t numInp, int32_t denomInp);

    Rational& operator=(const Rational& other);
    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    Rational& operator%=(const Rational& other);

    bool IsPositive() const;
    bool IsZero() const;
    bool IsNegative() const;

    std::ostream& WriteTo(std::ostream& ostrm) const noexcept;
    std::istream& ReadFrom(std::istream& istrm);

private:
    int32_t gcd(int32_t a, int32_t b) const;
    void reduce();
private:
    int32_t num_ = 0;
    int32_t denom_ = 1;

    static const char slash{ '/' };
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);

Rational operator+(const Rational& rhs);
Rational operator-(const Rational& rhs);

Rational operator+(Rational lhs, const Rational& rhs);
Rational operator-(Rational lhs, const Rational& rhs);
Rational operator*(Rational lhs, const Rational& rhs);
Rational operator/(Rational lhs, const Rational& rhs);

Rational sqr(Rational myRat);
Rational pow(Rational myRat, int32_t power);

Rational operator%(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);


#endif //PROGRAMMING_RATIONAL_H
