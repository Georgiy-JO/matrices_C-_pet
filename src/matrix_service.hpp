#ifndef MATRIX_SERVICE
#define MATRIX_SERVICE
#include <cmath>

#include "matrix_exceptions.hpp"

using std::isinf, std::isnan;

// Represents the value of zero as a double.
constexpr double DOUBLE_ZERO(0);
// Defines a small margin of error for floating-point comparisons.
constexpr double EPSILON(1e-7);

/**
 * @brief Provides utility methods for matrix-related operations, including
 * comparisons of double values.
 */
namespace MatrixService {
  /**
   * @brief Compares two double values for equality within a small epsilon
   * margin.
   * @param a The first double value.
   * @param b The second double value.
   * @return True if the values are equal within the epsilon margin, false
   * otherwise.
   */
  inline static bool doubleEq(const double& a, const double& b) noexcept {
    return fabs(a - b) < EPSILON;
  }
  /**
   * @brief Compares two double values for equality, considering complex cases
   * like NaN and infinity.
   * @param a The first double value.
   * @param b The second double value.
   * @return True if the values are considered equal, false otherwise.
   */
  inline static bool doubleEqComplex(const double& a, const double& b) {
    if (isnan(a) || isnan(b) ||
        (isinf(a) && isinf(b) &&
         ((a < DOUBLE_ZERO && b < DOUBLE_ZERO) ||
          (a > DOUBLE_ZERO && b > DOUBLE_ZERO))))
      throw DataError();
    return doubleEq(a, b);
  }
  /**
   * @brief Validates a double value, ensuring it is neither NaN nor infinite.
   * @param a The double value to validate.
   * @throws DataError if the value is NaN or infinite.
   */
  inline static void doubleLegit(const double& a) {
    if (isnan(a) || isinf(a)) throw DataError();
  }
}
#endif  // MATRIX_SERVICE