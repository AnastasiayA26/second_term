#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <matrixs/matrixs.hpp>

TEST_CASE("MatrixS default constructor creates matrix of size 0x0") {
MatrixS mat;
CHECK(mat.nRows() == 0);
CHECK(mat.nCols() == 0);
}

TEST_CASE("MatrixS constructor with SizeType creates matrix of correct size") {
MatrixS::SizeType size{ 2, 3 };
MatrixS mat(size);
CHECK(mat.nRows() == 2);
CHECK(mat.nCols() == 3);
}

TEST_CASE("MatrixS constructor with m, n creates matrix of correct size") {
MatrixS mat(2, 3);
CHECK(mat.nRows() == 2);
CHECK(mat.nCols() == 3);
}

TEST_CASE("MatrixS copy constructor creates a new matrix with identical values") {
MatrixS mat1(2, 3);
mat1.at(0, 0) = 1;
MatrixS mat2(mat1);
CHECK(mat2.nRows() == 2);
CHECK(mat2.nCols() == 3);
CHECK(mat2.at(0, 0) == 1);
}

TEST_CASE("MatrixS copy assignment creates a new matrix with identical values") {
MatrixS mat1(2, 3);
mat1.at(0, 0) = 1;
MatrixS mat2 = mat1;
CHECK(mat2.nRows() == 2);
CHECK(mat2.nCols() == 3);
CHECK(mat2.at(0, 0) == 1);
}


