#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <vector>
#include <iosfwd>
#include "Rational.hpp"

class Matrix
{
public:
    // constructor
    Matrix(std::size_t row = 0, std::size_t column = 0, Rational value = 0);
    std::size_t row() const;
    std::size_t column() const;
    // get matrix
    void getmatrix(std::size_t row, std::size_t column);
    // access members
    Rational at(std::size_t i, std::size_t j) const;
    Rational &at(std::size_t i, std::size_t j);
    Rational operator()(std::size_t i, std::size_t j) const;
    Rational &operator()(std::size_t i, std::size_t j);
    // operator overload
    friend std::ostream &operator<<(std::ostream &out, const Matrix &a);
    friend Matrix operator+(const Matrix &a, const Matrix &b);
    Matrix &operator+=(const Matrix &b);
    friend Matrix operator-(const Matrix &a);
    friend Matrix operator-(const Matrix &a, const Matrix &b);
    Matrix &operator-=(const Matrix &b);
    friend Matrix operator*(Rational s, const Matrix &a);
    friend Matrix operator*(const Matrix &a, Rational s);
    friend Matrix operator*(const Matrix &a, const Matrix &b);
    // identity
    static Matrix identity(std::size_t n);
    // power
    Matrix power(int a) const;
    // transpose
    Matrix transpose() const;
    // ERO
    Matrix &swap_two_lines(std::size_t s, std::size_t t);
    Matrix &multiply_one_line(Rational a, std::size_t s);
    Matrix &add_one_to_another(Rational a, std::size_t s, std::size_t t);
    // REF
    Matrix &find_std_leading(std::size_t &s_r, std::size_t &s_c);
    Matrix &reduce_by_std_leading(std::size_t &s_r, std::size_t &s_c);
    Matrix &change_leading_to_one(std::size_t &s_r, std::size_t &s_c);
    Matrix &one_REF(std::size_t &s_r, std::size_t &s_c);
    Matrix &REF();
    // RREF
    std::size_t find_the_leading_one_in_line_s(std::size_t s);
    Matrix &change_column_to_zero(std::size_t row_lead, std::size_t col_lead);
    Matrix &RREF();
    // rank
    std::size_t rank();
    // null & col
    Matrix null();
    bool is_variable(std::size_t s);
    Matrix col();
    // solve equation
    Matrix augmented(Matrix const &b) const;
    Matrix solve(Matrix b);
    // ERO for det
    Matrix &swap_two_lines(std::size_t s, std::size_t t, Rational &det);
    Matrix &multiply_one_line(Rational a, std::size_t s, Rational &det);
    Matrix &add_one_to_another(Rational a, std::size_t s, std::size_t t, Rational &det);
    // REF for deç
    Matrix &find_std_leading(std::size_t &s_r, std::size_t &s_c, Rational &det);
    Matrix &reduce_by_std_leading(std::size_t &s_r, std::size_t &s_c, Rational &det);
    Matrix &change_leading_to_one(std::size_t &s_r, std::size_t &s_c, Rational &det);
    Matrix &one_REF(std::size_t &s_r, std::size_t &s_c, Rational &det);
    Matrix &REF(Rational &det);
    // det
    bool is_square() const;
    Rational det();
    // reverse
    Matrix inverse() const;

private:
    std::size_t row_;
    std::size_t column_;
    std::vector<Rational> data;
};
#endif