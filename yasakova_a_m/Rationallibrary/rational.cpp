#include "rational.h"
#include <iostream>
#include <cmath>
#include <string>

Rational::Rational(){ //default
    numerator = 0;
    denominator = 1;
}
Rational::Rational(int32_t numeratorInp){ // int
    numerator = numeratorInp;
    denominator = 1;
}
Rational::Rational(const Rational& myRat){ // copy
    numerator = myRat.numerator;
    denominator = myRat.denominator;
}
Rational::Rational(const int32_t numeratorInp, const int32_t denominatorInp){
    if(denominatorInp <= 0){
        throw std::invalid_argument("It is not positive denominator");
    }
    numerator = numeratorInp;
    denominator = denominatorInp;
    reduce();
}
Rational& Rational::operator++(){
 *this += 1;
 return *this;
}
Rational Rational::operator++(int){
    Rational tmp(*this);
    ++(*this);
    return tmp;
}
Rational& Rational::operator--(){
    *this -= 1;
    return *this;
}
Rational Rational::operator--(int){
    Rational tmp(*this);
    --(*this);
    return tmp;
}
Rational& Rational::operator=(const Rational& rhs){
    numerator = rhs.numerator;
    denominator = rhs.denominator;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs){
    int32_t mult = rhs.denominator / gcd(denominator, rhs.denominator);
    numerator *= mult;
    denominator *= mult;
    numerator += denominator / rhs.denominator * rhs.numerator;
    reduce();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs){
    int32_t mult = rhs.denominator / gcd(denominator, rhs.denominator);
    numerator *= mult;
    denominator *= mult;
    numerator -= denominator / rhs.denominator * rhs.numerator;
    reduce();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs){
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    reduce();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs){
    if(rhs.isZero()){
        throw std::overflow_error("Divide by zero exception");
    }
    numerator *= rhs.denominator;
    denominator *= rhs.numerator;
    reduce();
    return *this;
}
Rational& Rational::operator%=(const Rational& rhs){
    int32_t mult = rhs.denominator / gcd(denominator, rhs.denominator);
    numerator *= mult;
    denominator *= mult;
    numerator %= denominator / rhs.denominator * rhs.numerator;
    reduce();
    return *this;
}
Rational Rational::operator+(){
    return *this;
}
Rational Rational::operator-(){
    Rational tmp;
    tmp -= *this;
    return tmp;
}
Rational operator+(Rational lhs, const Rational& rhs){
    lhs += rhs;
    return lhs;
}
Rational operator-(Rational lhs, const Rational& rhs){
    lhs -= rhs;
    return lhs;
}
Rational operator*(Rational lhs, const Rational& rhs){
    lhs *= rhs;
    return lhs;
}
Rational operator/(Rational lhs, const Rational& rhs){
    lhs /= rhs;
    return lhs;
}
Rational operator%(Rational lhs, const Rational& rhs){
    lhs %= rhs;
    return lhs;
}
Rational sqr(Rational myRat){
    myRat *= myRat;
    return myRat;
}
Rational pow(Rational myRat, int32_t power){
    Rational answer(1);
    while (power) {
        if (power & 1) {
            answer *= myRat;
        }
        myRat = sqr(myRat);
        power >>= 1;
    }
    return answer;
}
bool operator==(Rational lhs, const Rational& rhs){
    lhs -= rhs;
    return lhs.isZero();
}
bool operator>(Rational lhs, const Rational& rhs){
    lhs -= rhs;
    return lhs.isPositive();
}
bool operator<(Rational lhs, const Rational& rhs){
    lhs -= rhs;
    return lhs.isNegative();
}
bool operator!=(const Rational& lhs, const Rational& rhs){
    return !operator==(lhs, rhs);
}
bool operator<=(const Rational& lhs, const Rational& rhs){
    return !operator>(lhs, rhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs){
    return !operator<(lhs, rhs);
}
int32_t Rational::gcd(int32_t a, int32_t b) const{
    return b == 0?a:gcd(b, a%b);
}
void Rational::reduce(){
    int32_t dev = gcd(std::abs(numerator),denominator);
    numerator /= dev;
    denominator /= dev;
}
bool Rational::isPositive() const{
    return numerator >0;
}
bool Rational::isZero() const{
    return numerator == 0;
}
bool Rational::isNegative() const{
    return numerator < 0;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs){
    return rhs.writeTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs){
    return rhs.readFrom(istrm);
}
std::ostream& Rational::writeTo(std::ostream& ostrm) const{
  ostrm<< numerator << slash << denominator;
  return ostrm;
}
std::istream& Rational::readFrom(std::istream& istrm){
    int32_t numeratorInp(0);
    char separator(0);
    int32_t denominatorInp(0);
    istrm >> numeratorInp >> separator >> denominatorInp;
    if (istrm.good()) {
        if (Rational::slash == separator) {
            if (denominatorInp <= 0) {
                throw std::invalid_argument("Expected positive denominator");
            }
            numerator = numeratorInp;
            denominator = denominatorInp;
            reduce();
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}
