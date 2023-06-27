#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayd/arrayd.hpp>
#include <iostream>

TEST_CASE("[arrayd] - ArrayD size & capacity") {
    ArrayD a(1, 0);
    CHECK(a[0] == 0);
    CHECK(a[1] == 1);
    a.insert(2, 2);
    CHECK(a[2] == 2);
    a.insert(1, 3);
}
