#include"Rationallibrary/rational.h"
#include<iostream>

int main() {
    Rational a(4, 5), b(3, 8);
    int32_t n{ 6 };
    std::cout << a << " + " << b << " -> " << a + b << std::endl;
    std::cout << a << " - " << b << " -> " << a - b << std::endl;
    std::cout << a << " * " << b << " -> " << a * b << std::endl;
    std::cout << a << " / " << b << " -> " << a / b << std::endl;
    std::cout << a << " % " << b << " -> " << a % b << std::endl;

    std::cout << a << " ^ " << n << " -> " << pow(a, n) << std::endl;
    std::cout << "sqr(" << a << ") -> " << sqr(a) << std::endl;

    std::cout << a << " < " << b << " -> " << (a < b) << std::endl;
    std::cout << a << " = " << b << " -> " << (a == b) << std::endl;
    std::cout << a << " > " << b << " -> " << (a > b) << std::endl;
    return 0;
}
//
// Created by Пользователь on 15.02.2023.
//
