#ifndef MATRIX_CPP_H
#define MATRIX_CPP_H
#include <iostream>
#include <memory>
#include <variant>

#include "matrix_exceptions.hpp"
#include "matrix_service.hpp"

/**
 * @brief Enumeration to indicate addition or subtraction operations.
 * @note Sum  ///< Represents addition.
 * @note Sub  ///< Represents addition.
 */
enum class SumSub { Sum, Sub };

/**
 * @brief A class representing a matrix with various operations and utilities.
 * @note Methods without "noexcept" keyword include verios of throws.
 * @see matrix_exceptions.hpp
 */
class S21Matrix : public MatrixService {
 private:
  int rows_{0}, cols_{0};  ///< Number of rows and columns in the matrix.
  double** matrix_ =
      nullptr;  ///< Pointer to the allocated memory for the matrix.

  /**
   * @brief Allocates memory for the matrix based on its dimensions.
   */
  void allocateMatrix();
  /**
   * @brief Frees a part of the allocated matrix.
   * @param n Number of rows to free.
   */
  void freeMatrixPart(const int n) noexcept;
  /**
   * @brief Frees the entire allocated memory for the matrix.
   */
  void freeMatrix() noexcept { freeMatrixPart(rows_); }
  /**
   * @brief Sets the matrix pointer to a null state and amount of rows and
   * columns to zero.
   */
  void setNullMatrix() noexcept;
  /**
   * @brief Performs addition or subtraction on matrices.
   * @param other The matrix to be added or subtracted to the one this method
   * was called from.
   * @param mod Indicates whether to add or subtract.
   * @return Resultant matrix after addition or subtraction.
   */
  S21Matrix matrixSumSub(const S21Matrix& other, SumSub mod) const;
  /**
   * @brief Creates a minor matrix by excluding a specific row and column.
   * @param row The row to exclude.
   * @param col The column to exclude.
   * @return The minor matrix.
   */
  S21Matrix minorMaker(const int row, const int col) const;

  /**
   * @brief A helper class to represent an element of the matrix.
   * @note This is used for index reference of matrix elements.
   * @see MatrixElement operator()(const int row, const int col) const;
   */
  class MatrixElement {
    double* ptr =
        nullptr;  ///< Pointer to the address of element in the matrix.
   public:
    /**
     * @brief Constructs a MatrixElement.
     * @param matrix The matrix object.
     * @param row Row index of the element.
     * @param col Column index of the element.
     */
    MatrixElement(const S21Matrix& matrix, const int row,
                  const int col) noexcept
        : ptr{&(matrix.matrix_[row][col])} {}
    /**
     * @brief Assigns a value to the matrix element.
     * @param input The value to assign.
     * @return The assigned value.
     */
    double operator=(const double input);
    /**
     * @brief Implicit conversion to the element's value.
     * @return The value of the matrix element.
     */
    operator double() const { return *ptr; }
  };

 public:
  /**
   * @brief Default constructor.
   */
  S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}
  /**
   * @brief Parametrized constructor with dimensions.
   * @param rows Number of rows.
   * @param cols Number of columns.
   */
  S21Matrix(const int rows, const int cols);
  /**
   * @brief Parametrized constructor with dimensions and values passed as array.
   * @param rows Number of rows.
   * @param cols Number of columns.
   * @param n Number of elements in the array.
   * @param arr Array of values to initialize the matrix.
   */
  S21Matrix(const int rows, const int cols, const int n, const double arr[])
      : S21Matrix(rows, cols) {
    setMatrix(n, arr);
  }
  /**
   * @brief Copy constructor.
   * @param other The matrix to copy.
   */
  S21Matrix(const S21Matrix& other) noexcept;
  /**
   * @brief Move constructor.
   * @param other The matrix to move.
   */
  S21Matrix(S21Matrix&& other) noexcept
      : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.setNullMatrix();
  }
  /**
   * @brief Destructor.
   */
  ~S21Matrix() noexcept;

  // Getters and setters
  /**
   * @brief Retrieves the number of rows in the matrix.
   * @return Number of rows.
   */
  int getRows() const noexcept { return rows_; }
  /**
   * @brief Retrieves the number of columns in the matrix.
   * @return Number of columns.
   */
  int getCols() const noexcept { return cols_; }
  /**
   * @brief Retrieves the matrix dimensions.
   * @param rows Output parameter for rows.
   * @param columns Output parameter for columns.
   */
  void getDimentions(int& rows, int& columns) const noexcept {
    rows = rows_;
    columns = cols_;
  }
  /**
   * @brief Retrieves the matrix as a constant pointer.
   * @return Constant pointer to the matrix.
   */
  const double** getMatrix() const noexcept {
    return const_cast<const double**>(matrix_);
  }
  /**
   * @brief Retrieves the value of a specific matrix element.
   * @param row Row index of the element.
   * @param col Column index of the element.
   * @return The value of the element.
   */
  double getElement(const int row, const int col) const;
  /**
   * @brief Converts the matrix to a one-dimensional array.
   * @return A unique pointer to the resulting array.
   */
  std::unique_ptr<double[]> getArrayFromMatrix() const;

  /**
   * @brief Sets the value of a specific element in the matrix.
   * @param row Row index of the element.
   * @param col Column index of the element.
   * @param value The value to assign.
   */
  void setElement(const int row, const int col, const double value);
  /**
   * @brief Sets the matrix values from a one-dimensional array.
   * @param n The number of elements in the array.
   * @param array The array of values.
   */
  void setMatrix(const int n, const double array[]);
  /**
   * @brief Sets the number of rows in the matrix.
   * @param rows The new number of rows.
   */
  void setRows(const int rows) { setDimentions(rows, cols_); }
  /**
   * @brief Sets the number of columns in the matrix.
   * @param cols The new number of columns.
   */
  void setCols(const int cols) { setDimentions(rows_, cols); }
  /**
   * @brief Sets new dimensions to the matrix.
   * @param rows The number of rows.
   * @param columns The number of columns.
   */
  void setDimentions(const int rows, const int columns);
  /**
   * @brief Sets both the dimensions and values of the matrix.
   * @param r The number of rows.
   * @param c The number of columns.
   * @param n The number of elements in the array.
   * @param ar The array of values.
   */
  void setFull(const int r, const int c, const int n, const double ar[]) {
    setDimentions(r, c);
    setMatrix(n, ar);
  }

  // service methods
  /**
   * @brief Checks if the dimensions of the current matrix match another matrix.
   * @param other The matrix to compare with.
   * @return True if the dimensions match, false otherwise.
   */
  bool matrixDimentionEq(const S21Matrix& other) const;
  /**
   * @brief Prints the matrix to the console.
   */
  void print_matrix() const noexcept;
  /**
   * @brief Replaces the current matrix with another matrix.
   * @param other The matrix to replace with.
   */
  void replaceMatrix(S21Matrix& other) noexcept;

  // methods
  /**
   * @brief Checks matrices for equality.
   * @param other The matrix to compare with.
   * @return True if the matrices are equal, false otherwise.
   */
  bool EqMatrix(const S21Matrix& other) const;
  /**
   * @brief Adds another matrix to the current one.
   * @param other The matrix to add.
   */
  void SumMatrix(const S21Matrix& other) {
    S21Matrix res(*this + other);
    this->replaceMatrix(res);
  }
  /**
   * @brief Subtracts another matrix from the current one.
   * @param other The matrix to subtract.
   */
  void SubMatrix(const S21Matrix& other) {
    S21Matrix res(*this - other);
    this->replaceMatrix(res);
  }
  /**
   * @brief Multiplies the current matrix by a scalar value.
   * @param num The scalar value to multiply with.
   */
  void MulNumber(const double num) {
    S21Matrix res((*this) * num);
    this->replaceMatrix(res);
  }
  /**
   * @brief Multiplies the current matrix by another matrix.
   * @param other The matrix to multiply with.
   */
  void MulMatrix(const S21Matrix& other) {
    S21Matrix res((*this) * other);
    this->replaceMatrix(res);
  }
  /**
   * @brief Transposes the current matrix and returns the result.
   * @return The transposed matrix.
   */
  S21Matrix Transpose() const;
  /**
   * @brief Creates a matrix of complements.
   * @return The matrix of complements.
   */
  S21Matrix CalcComplements() const;
  /**
   * @brief Calculates the determinant of the matrix.
   * @return The determinant of the matrix.
   */
  double Determinant() const;
  /**
   * @brief Creates an inversed matrix.
   * @return The inversed matrix.
   */
  S21Matrix InverseMatrix() const;

  // operators overload
  /**
   * @brief Ollows access (adjust or return) to the matrix's element with it's
   * index.
   * @return The value of the element.
   */
  MatrixElement operator()(const int row, const int col) const;
  /**
   * @brief Overloading the "==" operator.
   * @param other The matrix to compare with.
   * @return True if the matrices are equal, false otherwise.
   */
  bool operator==(const S21Matrix& other) const {
    return this->EqMatrix(other);
  }
  /**
   * @brief Overloading the "=" (set) operator.
   * @param other The matrix to take values from with.
   * @return Reference to the matrix values were set to.
   */
  S21Matrix& operator=(const S21Matrix& other) noexcept;
  /**
   * @brief Overloading the "+"(add) operator.
   * @param other The matrix to add to the left one.
   * @return Resulting matrix.
   */
  S21Matrix operator+(const S21Matrix& other) const {
    return matrixSumSub(other, SumSub::Sum);
  }
  /**
   * @brief Overloading the "-"(substraction) operator.
   * @param other The matrix to substract.
   * @return Resulting matrix.
   */
  S21Matrix operator-(const S21Matrix& other) const {
    return matrixSumSub(other, SumSub::Sub);
  }
  /**
   * @brief Overloading the "+="(addition assignment) operator.
   * @param other The matrix to add.
   * @return Resulting matrix reference.
   */
  S21Matrix& operator+=(const S21Matrix& other) {
    this->SumMatrix(other);
    return *this;
  }
  /**
   * @brief Overloading the "-="(substraction assignment) operator.
   * @param other The matrix to substract.
   * @return Resulting matrix reference.
   */
  S21Matrix& operator-=(const S21Matrix& other) {
    this->SubMatrix(other);
    return *this;
  }
  /**
   * @brief Overloading the "*"(multiplication) by a matrix operator.
   * @param other The matrix to multiply by.
   * @return Resulting matrix.
   */
  S21Matrix operator*(const S21Matrix& other) const;
  /**
   * @brief Overloading the "*"(multiplication) by a number operator.
   * @param other The number to multiply by.
   * @return Resulting matrix.
   */
  S21Matrix operator*(const double num) const;
  /**
   * @brief Overloading the "*="(multiplication assignment) by a matrix
   * operator.
   * @param other The matrix to multiply by.
   * @return Resulting matrix reference.
   */
  S21Matrix& operator*=(const S21Matrix& other) {
    this->MulMatrix(other);
    return *this;
  }
  /**
   * @brief Overloading the "*="(multiplication assignment) by a matrix
   * operator.
   * @param other The number to multiply by.
   * @return Resulting matrix reference.
   */
  S21Matrix& operator*=(const double other) {
    this->MulNumber(other);
    return *this;
  }
};
#endif  // MATRIX_CPP_H
