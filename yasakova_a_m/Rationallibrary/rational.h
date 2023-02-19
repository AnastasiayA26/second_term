#ifndef PROJECTC_RATIONAL_H
#define PROJECTC_RATIONAL_H
#include<iosfwd>
#include<cstdint>

class Rational{

private:
    int32_t  numerator{0};
    int32_t  denominator{1};
    int32_t gcd(int32_t a, int32_t b) const; //нод
    void reduce(); // сокращает дробь
    static const char slash{'/'};


public:
    Rational();
    Rational(const int32_t numerator, const int32_t denominator);
    Rational(const int32_t numeratorInp);
    Rational(const Rational& myRat); //копирующий конструктор

    ~Rational()=default;

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    Rational& operator%=(const Rational& rhs);

    Rational& operator=(const Rational& rhs);
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational operator+();
    Rational operator-();

    bool isPositive() const;
    bool isZero() const;
    bool isNegative() const;

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);


Rational operator+(Rational lhs, const Rational& rhs);
Rational operator-(Rational lhs, const Rational& rhs);
Rational operator*(Rational lhs, const Rational& rhs);
Rational operator/(Rational lhs, const Rational& rhs);
Rational operator%(Rational lhs, const Rational& rhs);

Rational sqr(Rational myRat);
Rational pow(Rational myRat, const int32_t power);

bool operator==(Rational lhs, const Rational& rhs);
bool operator>(Rational lhs, const Rational& rhs);
bool operator<(Rational lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

#endif //PROJECTC_RATIONAL_H
