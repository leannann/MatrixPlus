#ifndef S21_MATRIX_PLUS_SRC_S21_MATRIX_OOP_H_
#define S21_MATRIX_PLUS_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix() noexcept;  // A basic constructor that initialises a matrix of
                         // some predefined dimension
  explicit S21Matrix(
      int rows,
      int cols);  // Parametrized constructor with number of rows and columns
  S21Matrix(const S21Matrix& other);             // Copy constructor
  S21Matrix(S21Matrix&& other) noexcept;         // Move constructor
  S21Matrix& operator=(const S21Matrix& other);  // Assignment of values from
                                                 // one matrix to another one

  ~S21Matrix();  // Destructor

  // Accessors
  inline int getRows() const noexcept { return rows_; };
  inline int getCols() const noexcept { return cols_; };
  // Mutators
  void resizeMatrix(int rows, int cols);
  void setRows(int rows);
  void setCols(int cols);

  inline S21Matrix& operator+(const S21Matrix& other) {
    return *this += other;
  };  // Addition of two matrices
  inline S21Matrix& operator-(const S21Matrix& other) {
    return *this -= other;
  };  // Subtraction of one matrix from another
  inline S21Matrix& operator*(const S21Matrix& other) {
    return *this *= other;
  };  // Matrix multiplication
  S21Matrix& operator*(double number) {
    return *this *= number;
  };  //  Matrix multiplication by a number
  bool operator==(const S21Matrix& other)
      const noexcept;  // Checks for matrices equality (EqMatrix)
  S21Matrix& operator+=(
      const S21Matrix& other) noexcept;  // Addition assignment (SumMatrix)
  S21Matrix& operator-=(
      const S21Matrix& other) noexcept;  // Difference assignment (SubMatrix)
  S21Matrix& operator*=(
      const S21Matrix& other);  // Multiplication assignment (MulMatrix)
  S21Matrix& operator*=(
      double number) noexcept;  // Multiplication assignment (MulNumber)
  double& operator()(
      int i,
      int j) const noexcept;  // Indexation by matrix elements (row, column)

  inline bool EqMatrix(const S21Matrix& other) const {
    return *this == other;
  };  // Checks matrices for equality with each other
  inline void SumMatrix(const S21Matrix& other) {
    *this += other;
  };  // Adds the second matrix to the current one
  inline void SubMatrix(const S21Matrix& other) {
    *this -= other;
  };  // Subtracts another matrix from the current one
  inline void MulNumber(const double number) {
    *this *= number;
  };  // Multiplies the current matrix by a number
  inline void MulMatrix(const S21Matrix& other) {
    *this *= other;
  };                            // Multiplies the current matrix by
                                // the second matrix
  S21Matrix Transpose() const;  // Creates a new transposed matrix from the
                                // current one and returns it
  S21Matrix CalcComplements()
      const;                   // Calculates the algebraic addition matrix of
                               // the current one and returns it
  double Determinant() const;  // Calculates and returns the determinant of the
                               // current matrix
  S21Matrix InverseMatrix();   // Calculates and returns the inverse matrix

 private:
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

  void deleteMatrix();  // Free Matrix;
};

#endif  // S21_MATRIX_PLUS_SRC_S21_MATRIX_OOP_H_