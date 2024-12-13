#include <cmath>

#include "matrix_exceptions.hpp"

using std::isinf, std::isnan;

constexpr double DOUBLE_ZERO(0);
constexpr double EPSILON(1e-7);

class MatrixService {
 public:
  inline static bool doubleEq(const double& a, const double& b) noexcept {
    return fabs(a - b) < EPSILON;
  }
  inline static bool doubleEqComplex(const double& a, const double& b) {
    if (isnan(a) || isnan(b) ||
        (isinf(a) && isinf(b) &&
         ((a < DOUBLE_ZERO && b < DOUBLE_ZERO) ||
          (a > DOUBLE_ZERO && b > DOUBLE_ZERO))))
      throw DataError();
    return doubleEq(a, b);
  }
  inline static void doubleLegit(const double& a) {
    if (isnan(a) || isinf(a)) throw DataError();
  }
};