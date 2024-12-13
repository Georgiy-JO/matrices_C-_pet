#ifndef MATRIX_EXCEPTIONS
#define MATRIX_EXCEPTIONS

/**
 * @brief Base class for matrix-related exceptions.
 * @note This class extends std::exception to provide a custom error message for
 * matrix-related errors.
 */
class MatrixError : public std::exception {
  std::string msg;

 public:
  /**
   * @brief Constructs a MatrixError with a default or custom message.
   * @param error A string describing the error. Defaults to "Unknown error!".
   */
  MatrixError(const char* error = "Unknown error!") : msg(error) {}
  /**
   * @brief Copy constructor for MatrixError.
   * @param other The MatrixError object to copy.
   */
  MatrixError(const MatrixError& other) : msg(other.msg) {}

  /**
   * @brief Provides the error message.
   * @note Overrides std::exception::what.
   * @return A C-string representing the error message.
   */
  const char* what() const noexcept override { return msg.c_str(); }
};

/**
 * @brief Exception for matrix dimension errors.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class DimentionError : public MatrixError {
 public:
  DimentionError(
      const char* error =
          "Matrix sizes error: matrix dimensions should be positive.")
      : MatrixError(error) {}
};

/**
 * @brief Exception for data-related errors.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class DataError : public MatrixError {
 public:
  DataError(const char* error =
                "Incorrect data: impossible to input/calculate due to data "
                "error (inf, nan, etc).")
      : MatrixError(error) {}
};

/**
 * @brief Exception for unequal matrix dimensions.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class DimentionEqualityError : public MatrixError {
 public:
  DimentionEqualityError(
      const char* error =
          "Calculation impossible: matrices' dimensions are not equal.")
      : MatrixError(error) {}
};

/**
 * @brief Exception for misaligned matrix dimensions.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class DimentionAlignmentError : public MatrixError {
 public:
  DimentionAlignmentError(
      const char* error =
          "Calculation impossible: the number of columns of the first matrix "
          "does not equal the number of rows of the second matrix.")
      : MatrixError(error) {}
};

/**
 * @brief Exception for memory allocation failures.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class MemoryAllocationError : public MatrixError {
 public:
  MemoryAllocationError(
      const char* error =
          "Memory allocation problem: congratulations, you got it somehow!")
      : MatrixError(error) {}
};

/**
 * @brief Exception for out-of-range access.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class OutOfRangeError : public MatrixError {
 public:
  OutOfRangeError(const char* error =
                      "Out of range error: you are trying to reach an element "
                      "out of matrix bounds.")
      : MatrixError(error) {}
};

/**
 * @brief Exception for uninitialized or invalid matrices.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class MatrixSetError : public MatrixError {
 public:
  MatrixSetError(const char* error = "Matrix not set or does not exist.")
      : MatrixError(error) {}
};

/**
 * @brief Exception for non-square matrices.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class SquarenessError : public MatrixError {
 public:
  SquarenessError(const char* error = "The matrix is not square")
      : MatrixError(error) {}
};

/**
 * @brief Exception for non-invertible matrices.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class NonInvertibleError : public MatrixError {
 public:
  NonInvertibleError(
      const char* error =
          "The matrix is not invertible: the determinant is zero.")
      : MatrixError(error) {}
};

/**
 * @brief Exception for invalid input parameters or data.
 * @note Thrown when matrix dimensions are invalid (e.g., negative or zero).
 * @details Includes a constructor with a default or custom message. Massege
 * passe to the constructor by c-string parameter "error".
 */
class InputError : public MatrixError {
 public:
  InputError(const char* error = "Input parameter or data error.")
      : MatrixError(error) {}
};

#endif  // MATRIX_EXCEPTIONS
