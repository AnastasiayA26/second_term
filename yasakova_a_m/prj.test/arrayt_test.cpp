#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayt/arrayt.hpp>
#include <iostream>

typedef double T;
TEST_CASE("[arrayd] - ArrayT<T> assignment arithmetic ops") {
    ArrayT<T> a(2, 4.0);
    ArrayT<T> b(2, 5.0);
}

