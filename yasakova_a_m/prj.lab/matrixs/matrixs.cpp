#include <matrixs/matrixs.hpp>
#include <iostream>
#include <cmath>
#include <vector>

MatrixS::MatrixS(){
    ptrdiff_t rows_ = 0;
    ptrdiff_t cols_ = 0;
    int* data_ = nullptr;
    ptrdiff_t size_ = 0;
}
MatrixS::MatrixS(const SizeType& size) : rows_{ std::get<0>(size) }, cols_{ std::get<1>(size) } {
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    data_ = new int[rows_ * cols_];
    std::fill(data_, data_ + rows_ * cols_, 0);
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) : rows_{ m }, cols_{ n } {
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    data_ = new int[rows_ * cols_];
    std::fill(data_, data_ + rows_ * cols_, 0);
}

MatrixS::MatrixS(const MatrixS& other) : rows_{ other.rows_ }, cols_{ other.cols_ } {
    data_ = new int[rows_ * cols_];
    std::copy(other.data_, other.data_ + rows_ * cols_, data_);
}

MatrixS::~MatrixS() {
    delete[] data_;
}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    if (this != &other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            delete[] data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = new int[rows_ * cols_];
        }
        std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    }
    return *this;
}

[[nodiscard]] int& MatrixS::at(const SizeType& elem) {
    const std::ptrdiff_t r = std::get<0>(elem);
    const std::ptrdiff_t c = std::get<1>(elem);
    if (r >= rows_ || c >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[r * cols_ + c];
}

[[nodiscard]] const int& MatrixS::at(const SizeType& elem) const {
    const std::ptrdiff_t r = std::get<0>(elem);
    const std::ptrdiff_t c = std::get<1>(elem);
    if (r >= rows_ || c >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[r * cols_ + c];
}

[[nodiscard]] int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i * cols_ + j];
}

[[nodiscard]] const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i * cols_ + j];
}

[[nodiscard]] std::ptrdiff_t MatrixS::nRows() const noexcept
{
    return rows_;
}
[[nodiscard]] std::ptrdiff_t MatrixS::nCols() const noexcept
{
    return cols_;
}

void MatrixS::resize(const std::ptrdiff_t row, const std::ptrdiff_t col)
{
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    MatrixS newMatrix(row, col);
    for (std::ptrdiff_t r = 0; r < row; ++r) {
        for (std::ptrdiff_t c = 0; c < col; ++c) {
            if (rows_ <= r || cols_ <= c) {
                newMatrix.at(SizeType(r, c)) = 0;
            }
            else {
                newMatrix.at(SizeType(r, c)) = at(SizeType(r, c));
            }
        }
    }
    *this = newMatrix;
}
void MatrixS::resize(const SizeType& s)
{
    if (std::get<0>(s) <= 0 || std::get<1>(s) <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    MatrixS newMatrix(std::get<0>(s), std::get<1>(s));
    for (std::ptrdiff_t r = 0; r < std::get<0>(s); ++r) {
        for (std::ptrdiff_t c = 0; c < std::get<1>(s); ++c) {
            if (rows_ <= r || cols_ <= c) {
                newMatrix.at(SizeType(r, c)) = 0;
            }
            else {
                newMatrix.at(SizeType(r, c)) = at(SizeType(r, c));
            }
        }
    }
    *this = newMatrix;
}

const MatrixS::SizeType &MatrixS::ssize() const noexcept{
    return SizeType(rows_, cols_);
}
