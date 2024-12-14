#include <gtest/gtest.h>

#include "../src/matrix_cpp.hpp"
using std::cout, std::cin, std::endl;
// elevator    begining

TEST(MatrixTest, print_matrix) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.print_matrix();
}
TEST(MatrixTest, DefaultConstructor) {
  Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix.getMatrix(), nullptr);
}
TEST(MatrixTest, spaceConstructor_1) {
  Matrix matrix(4, 5);
  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 5);
  EXPECT_EQ(matrix.getElement(2, 2), 0);
  EXPECT_NE(matrix.getMatrix(), nullptr);
}
TEST(MatrixTest, spaceConstructor_Exception) {
  EXPECT_THROW(Matrix matrix(-4, 5), DimentionError);
}
TEST(MatrixTest, desstructor) {
  Matrix matrix(4, 5);
  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 5);
  EXPECT_NE(matrix.getMatrix(), nullptr);
  matrix.~Matrix();
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix.getMatrix(), nullptr);
}
TEST(MatrixTest, getElement) {
  Matrix matrix(4, 5);
  EXPECT_EQ(matrix.getElement(0, 0), 0);
  EXPECT_EQ(matrix.getElement(3, 4), 0);
}
TEST(MatrixTest, setMatrix) {
  Matrix matrix(4, 4);
  double ar[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -5, 23, 33, 0, 4, -7777};
  int n = sizeof(ar) / sizeof(ar[0]);
  matrix.setMatrix(n, ar);
  EXPECT_EQ(matrix.getElement(0, 0), 1);
  EXPECT_EQ(matrix.getElement(0, 1), 2);
  EXPECT_EQ(matrix.getElement(3, 3), -7777);
  EXPECT_EQ(matrix.getElement(2, 2), -5);
}
TEST(MatrixTest, setMatrix_2) {
  Matrix matrix(4, 5);
  double ar[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -5, 23, 33, 0, 4, -7777};
  int n = sizeof(ar) / sizeof(ar[0]);
  matrix.setMatrix(n, ar);
  EXPECT_EQ(matrix.getElement(0, 0), 1);
  EXPECT_EQ(matrix.getElement(0, 4), 5);
  EXPECT_EQ(matrix.getElement(2, 1), 23);
  EXPECT_EQ(matrix.getElement(3, 4), 0);
  EXPECT_EQ(matrix.getElement(3, 0), -7777);
  EXPECT_EQ(matrix.getElement(3, 1), 0);
}
TEST(MatrixTest, setMatrix_Exception) {
  Matrix matrix;
  double ar[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -5, 23, 33, 0, 4, -7777};
  int n = sizeof(ar) / sizeof(ar[0]);
  EXPECT_THROW(matrix.setMatrix(n, ar), MatrixSetError);
  Matrix matrix_1(4, 4);
  EXPECT_THROW(matrix_1.setMatrix(-5, ar), InputError);
  EXPECT_THROW(matrix_1.setMatrix(20, ar), OutOfRangeError);
  EXPECT_THROW(matrix_1.setMatrix(17, ar), OutOfRangeError);
  ar[5] = NAN;
  EXPECT_THROW(matrix_1.setMatrix(16, ar), DataError);
  ar[5] = INFINITY;
  EXPECT_THROW(matrix_1.setMatrix(16, ar), DataError);
  double* ar_2 = nullptr;
  EXPECT_THROW(matrix_1.setMatrix(5, ar_2), InputError);
}
TEST(MatrixTest, complexConstructor) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_EQ(matrix.getElement(0, 1), 2);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_THROW(matrix.setMatrix(-5, ar), InputError);
  ar[3] = 1000;
  matrix.setMatrix(n, ar);
  EXPECT_EQ(matrix.getElement(0, 3), 1000);
}
TEST(MatrixTest, getElement_Exception) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_THROW(matrix.getElement(-2, 0), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(0, -50), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(10, 0), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(0, 10), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(0, 4), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(3, 0), OutOfRangeError);
}
TEST(MatrixTest, copyConstructor) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix_1(matrix);
  EXPECT_EQ(matrix.getElement(0, 1), 2);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix_1.getElement(0, 1), 2);
  EXPECT_EQ(matrix_1.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
  EXPECT_EQ(matrix_1.getRows(), 3);
  EXPECT_EQ(matrix_1.getCols(), 4);
}
TEST(MatrixTest, moveConstructor) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_EQ(matrix.getElement(0, 1), 2);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
  Matrix matrix_1 = std::move(matrix);
  EXPECT_EQ(matrix.getMatrix(), nullptr);
  EXPECT_EQ(matrix_1.getElement(0, 1), 2);
  EXPECT_EQ(matrix_1.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix_1.getRows(), 3);
  EXPECT_EQ(matrix_1.getCols(), 4);
}
TEST(MatrixTest, getDimentions) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.getDimentions(b, a);
  EXPECT_EQ(b, 3);
  EXPECT_EQ(a, 4);
}
TEST(MatrixTest, getMatrix) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  const double** matr = matrix.getMatrix();
  EXPECT_EQ(matr[0][1], 2);
  EXPECT_EQ(matr[2][3], 999);
}
TEST(MatrixTest, getArrayFromMatrix) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix_2;
  EXPECT_THROW(matrix_2.getArrayFromMatrix(), MatrixSetError);
  std::unique_ptr<double[]> ptr = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ptr[i], ar[i]);
}
TEST(MatrixTest, setElement_Exception) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_THROW(matrix.setElement(5, 2, 10), OutOfRangeError);
  EXPECT_THROW(matrix.setElement(3, 2, 10), OutOfRangeError);
  EXPECT_THROW(matrix.setElement(2, -2, 10), OutOfRangeError);
  EXPECT_THROW(matrix.setElement(1, 1, NAN), DataError);
  EXPECT_THROW(matrix.setElement(1, 1, INFINITY), DataError);
}
TEST(MatrixTest, setElement) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.setElement(2, 2, 5000.55);
  EXPECT_EQ(matrix.getElement(2, 2), 5000.55);
}
TEST(MatrixTest, setDimentions_Exception) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_THROW(matrix.setDimentions(-5, 2), OutOfRangeError);
  EXPECT_THROW(matrix.setElement(2, 5, 10), OutOfRangeError);
  EXPECT_THROW(matrix.setElement(5, 2, 10), OutOfRangeError);
}
TEST(MatrixTest, setDimentions) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.setDimentions(5, 5);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getElement(0, 3), 8);
  EXPECT_EQ(matrix.getElement(2, 0), 7);
  EXPECT_EQ(matrix.getElement(2, 3), 999);
  EXPECT_EQ(matrix.getElement(3, 3), 0);
  EXPECT_EQ(matrix.getElement(4, 4), 0);
  EXPECT_EQ(matrix.getElement(4, 3), 0);
}
TEST(MatrixTest, setDimentions_2) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.setDimentions(3, 4);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getElement(0, 3), 8);
  EXPECT_EQ(matrix.getElement(2, 0), 7);
  EXPECT_EQ(matrix.getElement(2, 3), 999);
}
TEST(MatrixTest, setRows) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.setRows(5);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getElement(0, 3), 8);
  EXPECT_EQ(matrix.getElement(2, 0), 7);
  EXPECT_EQ(matrix.getElement(2, 3), 999);
  EXPECT_EQ(matrix.getElement(4, 2), 0);
}
TEST(MatrixTest, setCols) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  matrix.setCols(5);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getElement(0, 3), 8);
  EXPECT_EQ(matrix.getElement(2, 0), 7);
  EXPECT_EQ(matrix.getElement(2, 3), 999);
  EXPECT_EQ(matrix.getElement(2, 4), 0);
}
TEST(MatrixTest, setFull) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix;
  matrix.setFull(a, b, n, ar);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getElement(0, 3), 8);
  EXPECT_EQ(matrix.getElement(2, 0), 7);
  EXPECT_EQ(matrix.getElement(2, 3), 999);
  EXPECT_EQ(matrix.getRows(), a);
  EXPECT_EQ(matrix.getCols(), b);
}
TEST(MatrixTest, matrixDimentionEq) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(a, b);
  Matrix matrix3(b, a);
  Matrix matrix5(a, a);
  EXPECT_EQ(matrix.matrixDimentionEq(matrix2), true);
  EXPECT_EQ(matrix.matrixDimentionEq(matrix3), false);
  EXPECT_EQ(matrix.matrixDimentionEq(matrix5), false);
}
TEST(MatrixTest, matrixDimentionEq_Exception) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix4;
  EXPECT_THROW(matrix.matrixDimentionEq(matrix4), MatrixSetError);
}
TEST(MatrixTest, doubleServiceMethods) {
  double a = 0.00000001, b = 0, c = 5.0, d = 5, e = NAN, f = INFINITY;
  EXPECT_EQ(MatrixService::doubleEq(a, b), true);
  EXPECT_EQ(MatrixService::doubleEq(a, c), false);
  EXPECT_EQ(MatrixService::doubleEq(c, d), true);
  EXPECT_EQ(MatrixService::doubleEqComplex(a, b), true);
  EXPECT_EQ(MatrixService::doubleEqComplex(a, c), false);
  EXPECT_EQ(MatrixService::doubleEqComplex(c, d), true);
  EXPECT_THROW(MatrixService::doubleEqComplex(e, d), DataError);
  EXPECT_THROW(MatrixService::doubleEqComplex(-f, -f), DataError);
  EXPECT_THROW(MatrixService::doubleEqComplex(f, f), DataError);
  EXPECT_EQ(MatrixService::doubleEqComplex(f, -f), false);
  EXPECT_EQ(MatrixService::doubleEqComplex(-f, f), false);
  EXPECT_EQ(MatrixService::doubleEqComplex(c, -f), false);
  EXPECT_EQ(MatrixService::doubleEqComplex(f, a), false);
  EXPECT_EQ(MatrixService::doubleEqComplex(a, f), false);
  EXPECT_NO_THROW(MatrixService::doubleEqComplex(f, a));
  EXPECT_NO_THROW(MatrixService::doubleEqComplex(a, f));
  EXPECT_NO_THROW(MatrixService::doubleLegit(a));
  EXPECT_NO_THROW(MatrixService::doubleLegit(b));
  EXPECT_NO_THROW(MatrixService::doubleLegit(c));
  EXPECT_NO_THROW(MatrixService::doubleLegit(d));
  EXPECT_THROW(MatrixService::doubleLegit(e), DataError);
  EXPECT_THROW(MatrixService::doubleLegit(f), DataError);
  EXPECT_THROW(MatrixService::doubleLegit(-f), DataError);
}
TEST(MatrixTest, EqMatrix) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(a, b, n, ar);
  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
  ar[3] = 100;
  ar[14] = 5.5;
  matrix2.setFull(a, b, n, ar);
  EXPECT_EQ(matrix.EqMatrix(matrix2), false);
  matrix2.setFull(b, b, n, ar);
  EXPECT_EQ(matrix.EqMatrix(matrix2), false);
  matrix.setFull(b, b, n, ar);
  EXPECT_EQ(matrix2.EqMatrix(matrix), true);
}
TEST(MatrixTest, EQoperator) {
  double ar[]{1, 2, 3, 8, 4, 5, 6, -5, 7, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(a, b, n, ar);
  EXPECT_EQ((matrix == matrix2), true);
  ar[3] = 100;
  ar[14] = 5.5;
  matrix2.setFull(a, b, n, ar);
  EXPECT_EQ((matrix == matrix2), false);
  matrix2.setFull(b, b, n, ar);
  EXPECT_EQ((matrix == matrix2), false);
  matrix.setFull(b, b, n, ar);
  EXPECT_EQ((matrix2 == matrix), true);
}
TEST(MatrixTest, SumMatrix) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] += ar2[i];
  matrix.SumMatrix(matrix2);
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, SumMatrix_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(a, a);
  EXPECT_THROW(matrix.SumMatrix(matrix2), DimentionEqualityError);
}
TEST(MatrixTest, SubMatrix_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(a, a);
  EXPECT_THROW(matrix.SubMatrix(matrix2), DimentionEqualityError);
}
TEST(MatrixTest, SudMatrix) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] -= ar2[i];
  matrix.SubMatrix(matrix2);
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, ADDoperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] += ar2[i];
  Matrix matrix3 = matrix + matrix2;
  std::unique_ptr<double[]> ar3 = matrix3.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, ADDoperator_2) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] += ar2[i];
  matrix = matrix + matrix2;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, ADDoperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(b, b, n, ar);
  EXPECT_THROW((matrix + matrix2), DimentionEqualityError);
}
TEST(MatrixTest, SUBoperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] -= ar2[i];
  Matrix matrix3 = matrix - matrix2;
  std::unique_ptr<double[]> ar3 = matrix3.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, SUBoperator_2) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] -= ar2[i];
  matrix = matrix - matrix2;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, SUBoperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(b, b, n, ar);
  EXPECT_THROW((matrix - matrix2), DimentionEqualityError);
}
TEST(MatrixTest, ADD_EQoperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] += ar2[i];
  matrix += matrix2;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, SUB_EQoperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double ar2[]{55.5,   32.0,   -555, -7.777, 123,     323.22,
               123.55, 5555.5, -0.1, -55.55, -0.0001, 12};
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  for (int i = 0; i < a * b; i++) ar[i] -= ar2[i];
  matrix -= matrix2;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, SUB_EQoperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(b, b, n, ar);
  EXPECT_THROW((matrix -= matrix2), DimentionEqualityError);
}
TEST(MatrixTest, ADD_EQoperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(b, b, n, ar);
  EXPECT_THROW((matrix += matrix2), DimentionEqualityError);
}
TEST(MatrixTest, replaceMatrix) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(b, b);
  matrix.replaceMatrix(matrix2);
  EXPECT_EQ(matrix2.getMatrix(), nullptr);
  EXPECT_EQ(matrix.getRows(), b);
  EXPECT_EQ(matrix.getCols(), b);
  EXPECT_EQ(matrix2.getRows(), 0);
  EXPECT_EQ(matrix2.getCols(), 0);
  EXPECT_EQ(matrix.getElement(2, 2), 0);
}
TEST(MatrixTest, CP_ASSoperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2(a, a);
  matrix2 = matrix;
  EXPECT_EQ(matrix2.getElement(2, 2), 9);
  EXPECT_EQ(matrix2.getElement(0, 3), 8.9);
  EXPECT_EQ(matrix2.getElement(2, 0), 7.000001);
  EXPECT_EQ(matrix2.getRows(), a);
  EXPECT_EQ(matrix2.getCols(), b);
  EXPECT_EQ(matrix.getElement(2, 2), 9);
  EXPECT_EQ(matrix.getElement(0, 3), 8.9);
  EXPECT_EQ(matrix.getElement(2, 0), 7.000001);
  EXPECT_EQ(matrix.getRows(), a);
  EXPECT_EQ(matrix.getCols(), b);
}
TEST(MatrixTest, numMULToperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = 5.5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  Matrix matrix3 = matrix * e;
  std::unique_ptr<double[]> ar3 = matrix3.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, numMULToperator_2) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  int e = 5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  Matrix matrix3 = matrix * e;
  std::unique_ptr<double[]> ar3 = matrix3.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, numMULToperator_3) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = 5.5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  matrix = matrix * e;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, numMULToperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = NAN;
  EXPECT_THROW((matrix * e), DataError);
  e = INFINITY;
  EXPECT_THROW((matrix * e), DataError);
  e = 5;
  Matrix matrix2;
  EXPECT_THROW((matrix2 * e), MatrixSetError);
}
TEST(MatrixTest, matrixMULToperator) {
  double ar[]{1.1, 2, 3, 8.5, 4.005, 5.2, 6, -5, 7, 8, 9, 999};
  double ar2[]{55.5, 32.0, 123, 323, -0.1, -55.55, -555, -7};
  double ar_res[]{-4410.75, 455.05, 3636.2775, 1509.46, -553073.4, -4684.95};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  a = 4;
  b = 2;
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  Matrix matrix3 = matrix * matrix2;
  std::unique_ptr<double[]> ar3 = matrix3.getArrayFromMatrix();
  n = sizeof(ar_res) / sizeof(ar_res[0]);
  for (int i = 0; i < n; i++) EXPECT_DOUBLE_EQ(ar_res[i], ar3[i]);
}
TEST(MatrixTest, matrixMULToperator_2) {
  double ar[]{1.1, 2, 3, 8.5, 4.005, 5.2, 6, -5, 7, 8, 9, 999};
  double ar2[]{55.5, 32.0, 123, 323, -0.1, -55.55, -555, -7};
  double ar_res[]{-4410.75, 455.05, 3636.2775, 1509.46, -553073.4, -4684.95};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  a = 4;
  b = 2;
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  matrix = matrix * matrix2;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  n = sizeof(ar_res) / sizeof(ar_res[0]);
  for (int i = 0; i < n; i++) EXPECT_DOUBLE_EQ(ar_res[i], ar3[i]);
}
TEST(MatrixTest, matrixMULToperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2;
  EXPECT_THROW((matrix * matrix2), MatrixSetError);
  EXPECT_THROW((matrix2 * matrix), MatrixSetError);
  matrix2.setFull(a, b, n, ar);
  EXPECT_THROW((matrix * matrix2), DimentionAlignmentError);
}
TEST(MatrixTest, MulMatrix) {
  double ar[]{1.1, 2, 3, 8.5, 4.005, 5.2, 6, -5, 7, 8, 9, 999};
  double ar2[]{55.5, 32.0, 123, 323, -0.1, -55.55, -555, -7};
  double ar_res[]{-4410.75, 455.05, 3636.2775, 1509.46, -553073.4, -4684.95};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  a = 4;
  b = 2;
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  matrix.MulMatrix(matrix2);
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  n = sizeof(ar_res) / sizeof(ar_res[0]);
  for (int i = 0; i < n; i++) EXPECT_DOUBLE_EQ(ar_res[i], ar3[i]);
}
TEST(MatrixTest, MulMatrix_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2;
  EXPECT_THROW(matrix.MulMatrix(matrix2), MatrixSetError);
  EXPECT_THROW(matrix.MulMatrix(matrix2), MatrixSetError);
  matrix2.setFull(a, b, n, ar);
  EXPECT_THROW(matrix.MulMatrix(matrix2), DimentionAlignmentError);
}
TEST(MatrixTest, MulNumber) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = 5.5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  matrix.MulNumber(e);
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, MulNumber_2) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  int e = 5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  matrix.MulNumber(e);
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, MulNumber_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = NAN;
  EXPECT_THROW(matrix.MulNumber(e);, DataError);
  e = INFINITY;
  EXPECT_THROW(matrix.MulNumber(e), DataError);
  e = 5;
  Matrix matrix2;
  EXPECT_THROW(matrix2.MulNumber(e), MatrixSetError);
}
TEST(MatrixTest, matrixMULT_EQoperator) {
  double ar[]{1.1, 2, 3, 8.5, 4.005, 5.2, 6, -5, 7, 8, 9, 999};
  double ar2[]{55.5, 32.0, 123, 323, -0.1, -55.55, -555, -7};
  double ar_res[]{-4410.75, 455.05, 3636.2775, 1509.46, -553073.4, -4684.95};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  a = 4;
  b = 2;
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix2(a, b, n, ar2);
  matrix *= matrix2;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  n = sizeof(ar_res) / sizeof(ar_res[0]);
  for (int i = 0; i < n; i++) EXPECT_DOUBLE_EQ(ar_res[i], ar3[i]);
}
TEST(MatrixTest, matrixMULT_EQoperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2;
  EXPECT_THROW(matrix *= matrix2;, MatrixSetError);
  EXPECT_THROW(matrix *= matrix2;, MatrixSetError);
  matrix2.setFull(a, b, n, ar);
  EXPECT_THROW(matrix *= matrix2;, DimentionAlignmentError);
}
TEST(MatrixTest, numMULT_EQoperator) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = 5.5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  matrix *= e;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, numMULT_EQoperator_2) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  int e = 5;
  for (int i = 0; i < a * b; i++) ar[i] *= e;
  matrix *= e;
  std::unique_ptr<double[]> ar3 = matrix.getArrayFromMatrix();
  for (int i = 0; i < a * b; i++) EXPECT_EQ(ar[i], ar3[i]);
}
TEST(MatrixTest, numMULT_EQoperator_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  double e = NAN;
  EXPECT_THROW(matrix *= e;, DataError);
  e = INFINITY;
  EXPECT_THROW(matrix *= e, DataError);
  e = 5;
  Matrix matrix2;
  EXPECT_THROW(matrix2 *= e, MatrixSetError);
}
TEST(MatrixTest, Indexation_get) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_EQ(matrix(0, 0), 1.1);
  EXPECT_EQ(matrix(0, 1), 2);
  EXPECT_EQ(matrix(0, 2), 3);
  EXPECT_EQ(matrix(0, 3), 8.9);
  EXPECT_EQ(matrix(2, 2), 9);
}
TEST(MatrixTest, Indexation_set) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_EQ(matrix(2, 2), 9);
  matrix(2, 2) = 1000;
  EXPECT_EQ(matrix(2, 2), 1000);
  matrix(1, 1) = 0.7;
  EXPECT_EQ(matrix(1, 1), 0.7);
}
TEST(MatrixTest, Indexation_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_THROW(matrix(0, 0) = INFINITY, DataError);
  EXPECT_THROW(matrix(8, 0) = INFINITY, OutOfRangeError);
  EXPECT_THROW(matrix(-8, 0) = INFINITY, OutOfRangeError);
  Matrix matrix2;
  EXPECT_THROW(matrix2(0, 0), MatrixSetError);
  EXPECT_THROW(matrix2(0, 0) = 5, MatrixSetError);
}
TEST(MatrixTest, Transpose) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2 = matrix.Transpose();
  EXPECT_EQ(matrix2(0, 0), 1.1);
  EXPECT_EQ(matrix2(1, 0), 2);
  EXPECT_EQ(matrix(0, 2), 3);
  EXPECT_EQ(matrix2(0, 2), 7.000001);
  EXPECT_EQ(matrix2(1, 2), 8);
  EXPECT_EQ(matrix2.getRows(), b);
  EXPECT_EQ(matrix2.getCols(), a);
}
TEST(MatrixTest, Transpose_Exception) {
  Matrix matrix;
  EXPECT_THROW(matrix.Transpose(), MatrixSetError);
}
TEST(MatrixTest, Determinant) {
  double ar[]{5, 2, 2,   1,    10,   100, -200, 8,  10, -20, 1, 55,  0,
              0, 0, 0.5, -0.5, 0.25, -10, 5,    -2, 0,  0.5, 0, -0.5};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 5, b = 5;
  Matrix matrix(a, b, n, ar);
  double det = matrix.Determinant(), res = 496724.24999999;
  EXPECT_NEAR(det, res, 0.000001);
}
TEST(MatrixTest, Determinant_2) {
  double ar[]{1, 2, 3, 3, 2, 1, 2, 1, 3};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = sqrt(n);
  Matrix matrix(a, a, n, ar);
  double det = matrix.Determinant(), res = -12;
  EXPECT_EQ(det, res);
  EXPECT_DOUBLE_EQ(det, res);
}
TEST(MatrixTest, Determinant_Exception) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  Matrix matrix2;
  EXPECT_THROW(matrix.Determinant(), SquarenessError);
  EXPECT_THROW(matrix2.Determinant(), MatrixSetError);
}
TEST(MatrixTest, CalcComplements) {
  double ar[]{1, 2, 3, 3, 2, 1, 2, 1, 3};
  double ar2[]{5, -7, -1, -3, -3, 3, -4, 8, -4};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = sqrt(n);
  Matrix matrix(a, a, n, ar);
  Matrix matrix2(a, a, n, ar2);
  matrix = matrix.CalcComplements();
  EXPECT_EQ(matrix == matrix2, true);
}
TEST(MatrixTest, CalcComplements_Exception) {
  Matrix matrix2;
  EXPECT_THROW(matrix2.CalcComplements(), MatrixSetError);
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_THROW(matrix.Determinant(), SquarenessError);
}
TEST(MatrixTest, InverseMatrix) {
  double ar[]{2, 5, 0, 4, 8, 0, 1, 5, 10};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = sqrt(n);
  Matrix matrix(a, a, n, ar);
  matrix = matrix.InverseMatrix();
  Matrix matrix2(a, a);
  matrix2(0, 0) = -2;
  matrix2(0, 1) = 5.0 / 4;
  matrix2(0, 2) = 0;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = -1.0 / 2;
  matrix2(1, 2) = 0;
  matrix2(2, 0) = -3.0 / 10;
  matrix2(2, 1) = 1.0 / 8;
  matrix2(2, 2) = 1.0 / 10;
  EXPECT_EQ(matrix == matrix2, true);
}
TEST(MatrixTest, InverseMatrix_2) {
  double ar[]{1, 2, 0, 5, 0, 1, -5, 0.5, 0, 0, 0, 2, 1, 0, 0, 1};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = sqrt(n);
  Matrix matrix(a, a, n, ar);
  double ar2[]{0,   0,    -0.5,  1,    0.5, 0, -1,  -0.5,
               0.1, -0.2, -0.15, -0.1, 0,   0, 0.5, 0};
  Matrix matrix2(a, a, n, ar2);
  matrix = matrix.InverseMatrix();
  EXPECT_EQ(matrix == matrix2, true);
}
TEST(MatrixTest, InverseMatrix_Exception) {
  Matrix matrix2;
  EXPECT_THROW(matrix2.InverseMatrix(), MatrixSetError);
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  int n = sizeof(ar) / sizeof(ar[0]);
  int a = 3, b = 4;
  Matrix matrix(a, b, n, ar);
  EXPECT_THROW(matrix.InverseMatrix(), SquarenessError);
  double ar2[]{7676.88, 5656.6, -0.5,  1,    0.5, 10000, -1, -0.5,
               0.1,     -0.2,   -0.15, -0.1, 0,   0,     0,  0};
  a = 4;
  n = sizeof(ar2) / sizeof(ar2[0]);
  Matrix matrix3(a, a, n, ar2);
  EXPECT_THROW(matrix3.InverseMatrix(), NonInvertibleError);
}
TEST(MatrixTest, SingularMatrix) {
  Matrix mat(1, 1);
  EXPECT_EQ(mat.getRows(), 1);
  EXPECT_EQ(mat.getCols(), 1);
  EXPECT_EQ(mat.getElement(0, 0), 0);
  double ar[] = {5};
  Matrix mat2(1, 1, 1, ar);
  EXPECT_EQ(mat2.getRows(), 1);
  EXPECT_EQ(mat2.getCols(), 1);
  EXPECT_EQ(mat2.getElement(0, 0), 5);
  Matrix mat3(mat2);
  EXPECT_EQ(mat3.getRows(), 1);
  EXPECT_EQ(mat3.getCols(), 1);
  EXPECT_EQ(mat3.getElement(0, 0), 5);
  Matrix mat4 = std::move(mat3);
  EXPECT_EQ(mat4.getRows(), 1);
  EXPECT_EQ(mat4.getCols(), 1);
  EXPECT_EQ(mat4.getElement(0, 0), 5);
  EXPECT_EQ(mat3.getRows(), 0);
  EXPECT_EQ(mat3.getCols(), 0);
  EXPECT_EQ(mat3.getMatrix(), nullptr);
  mat = mat + mat2;
  EXPECT_EQ(mat(0, 0), 5);
  mat2(0, 0) = 10;
  mat -= mat2;
  EXPECT_EQ(mat(0, 0), -5);
  Matrix mat5(1, 5);
  mat5(0, 0) = 1;
  mat5(0, 1) = 2;
  mat5(0, 2) = 3;
  mat5(0, 3) = 4;
  mat5(0, 4) = 5;
  mat *= mat5;
  EXPECT_EQ(mat(0, 0), -5);
  EXPECT_EQ(mat(0, 1), -10);
  EXPECT_EQ(mat(0, 2), -15);
  EXPECT_EQ(mat(0, 3), -20);
  EXPECT_EQ(mat(0, 4), -25);
  mat *= 0.5;
  EXPECT_EQ(mat(0, 0), -2.5);
  EXPECT_EQ(mat(0, 1), -5);
  EXPECT_EQ(mat(0, 2), -7.5);
  EXPECT_EQ(mat(0, 3), -10);
  EXPECT_EQ(mat(0, 4), -12.5);
  EXPECT_EQ(mat2.Determinant(), 10);
  mat5 = mat2.InverseMatrix();
  mat4(0, 0) = 0.1;
  EXPECT_EQ(mat4 == mat5, true);
}

// elevator     end
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}