#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <cstdio>
#include <cstddef>
#include <algorithm>
#include <string.h>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);
  Matrix(const Matrix& that);
  ~Matrix();
  
  std::size_t get_rows();
  std::size_t get_cols();
  void set(std::size_t, std::size_t, int);
  int get(std::size_t, std::size_t) const;
  void print(FILE*) const;
  
  Matrix& operator=(const Matrix& that);
  
  Matrix operator+(const Matrix&) const;
  Matrix operator-(const Matrix&) const;
  Matrix operator*(const Matrix&) const;

  Matrix& operator+=(const Matrix&);
  Matrix& operator-=(const Matrix&);
  Matrix& operator*=(const Matrix&);

  bool operator==(const Matrix&) const;
  bool operator!=(const Matrix&) const;
private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

#endif
