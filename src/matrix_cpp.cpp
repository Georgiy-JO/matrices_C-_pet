#include "matrix_cpp.hpp"

#include "matrix_exceptions.hpp"

Matrix::Matrix(const int rows, const int cols) {
  if (rows <= 0 || cols <= 0) throw DimentionError();
  rows_ = rows;
  cols_ = cols;
  allocateMatrix();
}

void Matrix::allocateMatrix() {
  matrix_ = new double*[rows_];
  if (!matrix_) throw MemoryAllocationError();

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0};
    if (!matrix_[i]) {
      freeMatrixPart(i);
      throw MemoryAllocationError();
    }
  }
}

void Matrix::freeMatrixPart(const int n) noexcept {
  if (matrix_) {
    for (int i = 0; i < n; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

Matrix::~Matrix() noexcept {
  freeMatrix();
  setNullMatrix();
}

Matrix::Matrix(const Matrix& other) noexcept
    : Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

double Matrix::getElement(const int row, const int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw OutOfRangeError();
  return matrix_[row][col];
}

void Matrix::setElement(const int row, const int col, const double value) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw OutOfRangeError();
  if (!matrix_) throw MatrixSetError();
  MatrixService::doubleLegit(value);
  matrix_[row][col] = value;
}

void Matrix::setMatrix(const int n, const double array[]) {
  if (!matrix_) throw MatrixSetError();
  if (n < 0 || !array) throw InputError();
  if (n > rows_ * cols_) throw OutOfRangeError();

  for (int i = 0, k = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++, k++) {
      if (k < n) {
        MatrixService::doubleLegit(array[k]);
        matrix_[i][j] = array[k];
      } else
        matrix_[i][j] = 0;
    }
  }
}

std::unique_ptr<double[]> Matrix::getArrayFromMatrix() const {
  if (!matrix_) throw MatrixSetError();
  std::unique_ptr<double[]> array{std::make_unique<double[]>(rows_ * cols_)};
  for (int i = 0, k = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++, k++) {
      array[k] = matrix_[i][j];
    }
  }
  return array;
}

void Matrix::setDimentions(const int rows, const int columns) {
  if (rows < rows_ || columns < cols_)
    throw OutOfRangeError();
  else if (rows > rows_ || columns > cols_) {
    Matrix matrix2(rows, columns);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (i < this->rows_ && j < this->cols_)
          matrix2.setElement(i, j, this->matrix_[i][j]);
        else
          matrix2.setElement(i, j, 0);
      }
    }
    replaceMatrix(matrix2);
  }
}

bool Matrix::EqMatrix(const Matrix& other) const {
  bool output = matrixDimentionEq(other);
  for (int i = 0; output && i < rows_; i++) {
    for (int j = 0; output && j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j])
        output = MatrixService::doubleEqComplex(matrix_[i][j], other.matrix_[i][j]);
    }
  }
  return output;
}

bool Matrix::matrixDimentionEq(const Matrix& other) const {
  if (!matrix_ || !other.matrix_) throw MatrixSetError();
  return ((rows_ == other.rows_) && (cols_ == other.cols_));
}

void Matrix::setNullMatrix() noexcept {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other) noexcept {
  if (this != &other) {
    this->~Matrix();
    this->setDimentions(other.rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

void Matrix::replaceMatrix(Matrix& other) noexcept {
  this->~Matrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.setNullMatrix();
}

Matrix Matrix::matrixSumSub(const Matrix& other,
                                  SumSub mod) const {  // check??
  Matrix result;
  if (!matrixDimentionEq(other)) throw DimentionEqualityError();
  result.setDimentions(this->rows_, this->cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      MatrixService::doubleLegit(this->matrix_[i][j]);
      MatrixService::doubleLegit(other.matrix_[i][j]);
      switch (mod) {
        case SumSub::Sum:
          result.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
          break;
        case SumSub::Sub:
          result.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
          break;
      }
    }
  }

  return result;
}

Matrix Matrix::operator*(const double num) const {
  if (!matrix_) throw MatrixSetError();
  MatrixService::doubleLegit(num);
  Matrix result = *this;
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      MatrixService::doubleLegit(result.matrix_[i][j]);
      result.matrix_[i][j] = result.matrix_[i][j] * num;
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  if (!matrix_ || !other.matrix_) throw MatrixSetError();
  if (cols_ != other.rows_) throw DimentionAlignmentError();
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        MatrixService::doubleLegit(this->matrix_[i][k]);
        MatrixService::doubleLegit(other.matrix_[k][j]);
        result.matrix_[i][j] += ((matrix_[i][k]) * (other.matrix_[k][j]));
      }
    }
  }
  return result;
}

// template <typename T>       //sad
// Matrix& Matrix::operator*=(const T& other){
//     std::variant< double, Matrix> v{other};
//     switch (v.index()) {
//         case 0: this->MulNumber(other); break;
//         case 1: this->MulMatrix(other); break;
//         default: throw InputError();
//     }
//     return *this;
// }

Matrix::MatrixElement Matrix::operator()(const int row,
                                               const int col) const {
  if (!matrix_) throw MatrixSetError();
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw OutOfRangeError();
  return MatrixElement(*this, row, col);
}

double Matrix::MatrixElement::operator=(const double input) { 
  if (!ptr) throw MatrixSetError();
  MatrixService::doubleLegit(input);
  *ptr = input;
  return input;
}

void Matrix::print_matrix() const noexcept {
  using std::cout, std::endl;
  if (!matrix_)
    cout << nullptr << endl;
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) cout << matrix_[i][j] << " ";
      cout << endl;
    }
  }
}

Matrix Matrix::Transpose() const {
  if (!matrix_) throw MatrixSetError();
  Matrix new_matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return new_matrix;
}

double Matrix::Determinant() const {
  if (!matrix_) throw MatrixSetError();
  if (rows_ != cols_) throw SquarenessError();
  double det = 0;
  if (rows_ == 1)
    det = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++) {
      MatrixService::doubleLegit(matrix_[0][i]);
      det += pow(-1, i) * matrix_[0][i] * minorMaker(0, i).Determinant();
    }
  }
  return det;
}

Matrix Matrix::minorMaker(const int row, const int col) const {
  if (!matrix_) throw MatrixSetError();
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_ || rows_ == 1 ||
      cols_ == 1)
    throw OutOfRangeError();
  int n = (rows_ - 1) * (cols_ - 1);
  double ar[n]{0};
  for (int i = 0, k = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) ar[k++] = matrix_[i][j];
    }
  }
  return Matrix(rows_ - 1, cols_ - 1, n, ar);
}

Matrix Matrix::CalcComplements() const {
  if (!matrix_) throw MatrixSetError();
  if (rows_ != cols_) throw SquarenessError();
  Matrix new_matrix(rows_, cols_);
  if (rows_ == 1)
    new_matrix(0, 0) = 1;
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++)
        new_matrix.matrix_[i][j] =
            minorMaker(i, j).Determinant() * pow(-1, (i + j));
    }
  }
  return new_matrix;
}

Matrix Matrix::InverseMatrix() const {
  double inverse_determinamt = Determinant();
  if (inverse_determinamt == 0) throw NonInvertibleError();
  inverse_determinamt = 1.0 / inverse_determinamt;
  return CalcComplements().Transpose() * inverse_determinamt;
}
