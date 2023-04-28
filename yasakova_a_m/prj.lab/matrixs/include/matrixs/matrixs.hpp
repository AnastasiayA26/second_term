#ifndef LIB_MATRIXS_HPP
#define LIB_MATRIXS_HPP

#include <iosfwd>
#include <utility>
#include <tuple>
class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
public:
    MatrixS();
    explicit MatrixS(const SizeType& s);
    MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_);
    MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_, int num);
    MatrixS(const MatrixS&);

    ~MatrixS();

    [[nodiscard]] const int& at(const std::ptrdiff_t, const std::ptrdiff_t) const;
    [[nodiscard]] int& at(const std::ptrdiff_t, const std::ptrdiff_t);
    [[nodiscard]] const int& at(const SizeType) const;
    [[nodiscard]] int& at(const SizeType);

    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;
    [[nodiscard]] std::ptrdiff_t nCols() const noexcept;

    void resize(const std::ptrdiff_t, const std::ptrdiff_t);
    void resize(const SizeType&);

    [[nodiscard]] SizeType ssize() const noexcept;

    MatrixS& operator=(const MatrixS&);
   
public:
    ptrdiff_t rows_;
    ptrdiff_t cols_;
    ptrdiff_t len_;
    int* data_;
};

#endif //LIB_MATRIXS_HPP

