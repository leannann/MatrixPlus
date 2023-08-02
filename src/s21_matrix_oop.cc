#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows >= 1 || cols >= 1) {
    this->rows_ = rows;
    this->cols_ = cols;
    this->matrix_ = new double*[rows_];

    for (int i = 0; i < this->rows_; ++i) this->matrix_[i] = new double[cols_];
  }

  else {
    std::cout << "Invalid matrix size" << std::endl;
    exit(1);
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];

  for (int i = 0; i < rows_; ++i) matrix_[i] = new double[cols_];

  for (int i = 0; i < other.rows_; ++i)
    for (int j = 0; j < other.cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < this->rows_; ++i) delete[] this->matrix_[i];

  delete[] this->matrix_;

  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::resizeMatrix(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    std::cout << "Invalid row/column size" << std::endl;
    exit(1);
  }

  else if (rows != rows_ || cols != cols_) {
    double** new_data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
      new_data[i] = new double[cols];
      for (int j = 0; j < cols; ++j)
        new_data[i][j] = (i < rows_ && j < cols_) ? matrix_[i][j] : 0;
    }
    deleteMatrix();
    matrix_ = new_data;
    rows_ = rows;
    cols_ = cols;
  }
}

void S21Matrix::setRows(int rows) {
  if (rows < 0) {
    std::cout << "Invalid row/column size" << std::endl;
    exit(1);
  }

  else if (rows != rows_) {
    double** new_data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
      new_data[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j)
        new_data[i][j] = (i < rows_ && j < cols_) ? matrix_[i][j] : 0;
    }
    deleteMatrix();
    matrix_ = new_data;
    rows_ = rows;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols < 0) {
    std::cout << "Invalid row/column size" << std::endl;
    exit(1);
  }

  else if (cols != cols_) {
    double** new_data = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      new_data[i] = new double[cols];
      for (int j = 0; j < cols; ++j)
        new_data[i][j] = (i < rows_ && j < cols_) ? matrix_[i][j] : 0;
    }
    deleteMatrix();
    matrix_ = new_data;
    cols_ = cols;
  }
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  bool status = true;

  if (rows_ != other.rows_ || cols_ != other.cols_)
    status = false;

  else
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j)
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-06) {
          status = false;
          break;
        }
  return status;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
      for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
        delete[] matrix_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = new double*[this->rows_];

        for (int i = 0; i < rows_; ++i) matrix_[i] = new double[this->cols_];
      }

    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) noexcept {
  if (rows_ == other.rows_ && cols_ == other.cols_)
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];

  else {
    std::cout << "Different matrix dimensions" << std::endl;
    exit(1);
  }

  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) noexcept {
  if (rows_ == other.rows_ && cols_ == other.cols_)
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];

  else {
    std::cout << "Different matrix dimensions" << std::endl;
    exit(1);
  }

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (cols_ == other.rows_) {
    S21Matrix temp(rows_, other.cols_);

    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < other.cols_; ++j) temp.matrix_[i][j] = 0;

    for (int i = 0; i < temp.rows_; ++i)
      for (int j = 0; j < temp.cols_; ++j)
        for (int k = 0; k < cols_; ++k)
          temp.matrix_[i][j] += (matrix_[i][k] * other.matrix_[k][j]);

    deleteMatrix();

    rows_ = temp.rows_;
    cols_ = temp.cols_;
    matrix_ = temp.matrix_;
    temp.rows_ = 0;
    temp.cols_ = 0;
    temp.matrix_ = nullptr;
  }

  else {
    std::cout << "The number of columns of the first matrix does not equal the "
                 "number "
                 "of rows of the second matrix"
              << std::endl;
    exit(1);
  }

  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) noexcept {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= number;

  return *this;
}

double& S21Matrix::operator()(int i, int j) const noexcept {
  if (i < 1 || j < 1 || i > rows_ || j > cols_) {
    std::cout << "Index is outside the matrix" << std::endl;
    exit(1);
  } else
    return this->matrix_[i - 1][j - 1];
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) result.matrix_[j][i] = matrix_[i][j];

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    std::cout << "The matrix is not square" << std::endl;
    exit(1);
  }

  else {
    int index1 = 0, index2 = 0;
    S21Matrix result(rows_, cols_);

    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < rows_; ++j) {
        index1 = i;
        index2 = j;

        S21Matrix temp(rows_ - 1, cols_ - 1);

        int tempIndex1 = 0, tempIndex2 = 0;

        for (int i = 0; i < rows_; ++i)
          if (i != index1) {
            tempIndex2 = 0;

            for (int j = 0; j < rows_; ++j)
              if (j != index2) {
                temp.matrix_[tempIndex1][tempIndex2] = matrix_[i][j];
                tempIndex2++;
              }
            tempIndex1++;
          }
        int res = pow(-1., index1 + 1 + index2 + 1) * temp.Determinant();
        result.matrix_[index1][index2] = res;
      }
    return result;
  }
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    std::cout << "The matrix is not square" << std::endl;
    exit(1);
  }

  else {
    double det = 0;
    if (rows_ == 1)
      det = matrix_[0][0];

    else if (rows_ == 2)
      det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];

    else
      for (int i = 0; i < rows_; ++i) {
        S21Matrix minor(rows_ - 1, cols_ - 1);

        for (int j = 1; j < rows_; ++j)
          for (int k = 0; k < cols_; ++k) {
            if (k < i)
              minor.matrix_[j - 1][k] = matrix_[j][k];
            else if (k > i)
              minor.matrix_[j - 1][k - 1] = matrix_[j][k];
          }
        det += pow(-1, i) * matrix_[0][i] * minor.Determinant();
      }
    return det;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();

  if (det != 0) {
    *this = CalcComplements();
    *this = Transpose();
    *this = *this * (1 / det);
  }

  else {
    std::cout << "Matrix determinant is 0" << std::endl;
    exit(1);
  }

  return *this;
}

void S21Matrix::deleteMatrix() {
  for (int i = 0; i < rows_; ++i) delete[] matrix_[i];
  delete[] matrix_;
}
