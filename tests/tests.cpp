#include <gtest/gtest.h>
#include "../src/s21_matrix_oop.hpp"
using std::cout, std::cin, std::endl;
// elevator    begining

TEST(MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix.getMatrix(),nullptr);
}
TEST(MatrixTest, spaceConstructor_1) {
  S21Matrix matrix(4,5);
  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 5);
  EXPECT_EQ(matrix.getElement(2,2), 0);
  EXPECT_NE(matrix.getMatrix(),nullptr);
}
TEST(MatrixTest, spaceConstructor_Exception) {
  EXPECT_THROW (S21Matrix matrix(-4,5),DimentionError);
}
TEST(MatrixTest, desstructor) {
  S21Matrix matrix(4,5);
  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 5);
  EXPECT_NE(matrix.getMatrix(),nullptr);
  matrix.~S21Matrix();
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix.getMatrix(),nullptr);
}
TEST(MatrixTest, getElement) {
  S21Matrix matrix(4,5);
  EXPECT_EQ(matrix.getElement(0,0), 0);
  EXPECT_EQ(matrix.getElement(3,4), 0);
}
TEST(MatrixTest, setMatrix){
  S21Matrix matrix(4,4);
  double ar[]{1,2,3,4,
              5,6,7,8,
              9,10,-5,23,
              33,0,4,-7777};
  int n=sizeof(ar)/sizeof(ar[0]);
  matrix.setMatrix(n,ar);
  EXPECT_EQ(matrix.getElement(0,0), 1);
  EXPECT_EQ(matrix.getElement(0,1), 2);
  EXPECT_EQ(matrix.getElement(3,3), -7777);
  EXPECT_EQ(matrix.getElement(2,2), -5);
}
TEST(MatrixTest, setMatrix_2){
  S21Matrix matrix(4,5);
  double ar[]{1,2,3,4,5,
              6,7,8,9,10,
              -5,23,33,0,4,
              -7777};
  int n=sizeof(ar)/sizeof(ar[0]);
  matrix.setMatrix(n,ar);
  EXPECT_EQ(matrix.getElement(0,0), 1);
  EXPECT_EQ(matrix.getElement(0,4), 5);
  EXPECT_EQ(matrix.getElement(2,1), 23);
  EXPECT_EQ(matrix.getElement(3,4), 0);
  EXPECT_EQ(matrix.getElement(3,0), -7777);
  EXPECT_EQ(matrix.getElement(3,1), 0);
}
TEST(MatrixTest, setMatrix_Exception){
  S21Matrix matrix;
  double ar[]{1,2,3,4,
              5,6,7,8,
              9,10,-5,23,
              33,0,4,-7777};
  int n=sizeof(ar)/sizeof(ar[0]);
  EXPECT_THROW (matrix.setMatrix(n,ar),MatrixSetError);
  S21Matrix matrix_1(4,4);
  EXPECT_THROW (matrix_1.setMatrix(-5,ar),InputError);
  EXPECT_THROW (matrix_1.setMatrix(20,ar),OutOfRangeError);
  EXPECT_THROW (matrix_1.setMatrix(17,ar),OutOfRangeError);
  ar[5]=NAN;
  EXPECT_THROW (matrix_1.setMatrix(16,ar),DataError);
  ar[5]=INFINITY;
  EXPECT_THROW (matrix_1.setMatrix(16,ar),DataError);
  double* ar_2=nullptr;
  EXPECT_THROW (matrix_1.setMatrix(5,ar_2),InputError);
}
TEST(MatrixTest, complexConstructor){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  EXPECT_EQ(matrix.getElement(0,1), 2);
  EXPECT_EQ(matrix.getElement(2,2), 9);
  EXPECT_THROW (matrix.setMatrix(-5,ar),InputError);
  ar[3]=1000;
  matrix.setMatrix(n,ar);
  EXPECT_EQ(matrix.getElement(0,3), 1000);
}
TEST(MatrixTest, getElement_Exception) {
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  EXPECT_THROW(matrix.getElement(-2,0), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(0,-50), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(10,0), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(0,10), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(0,4), OutOfRangeError);
  EXPECT_THROW(matrix.getElement(3,0), OutOfRangeError);
}
TEST(MatrixTest, copyConstructor) {
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix_1(matrix);
  EXPECT_EQ(matrix.getElement(0,1), 2);
  EXPECT_EQ(matrix.getElement(2,2), 9);
  EXPECT_EQ(matrix_1.getElement(0,1), 2);
  EXPECT_EQ(matrix_1.getElement(2,2), 9);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
  EXPECT_EQ(matrix_1.getRows(), 3);
  EXPECT_EQ(matrix_1.getCols(), 4);
}
TEST(MatrixTest, moveConstructor) {
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  EXPECT_EQ(matrix.getElement(0,1), 2);
  EXPECT_EQ(matrix.getElement(2,2), 9);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
  S21Matrix matrix_1 =std::move(matrix);
  EXPECT_EQ(matrix.getMatrix(), nullptr);
  EXPECT_EQ(matrix_1.getElement(0,1), 2);
  EXPECT_EQ(matrix_1.getElement(2,2), 9);
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix_1.getRows(), 3);
  EXPECT_EQ(matrix_1.getCols(), 4);
}
TEST(MatrixTest, getDimentions) {
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  matrix.getDimentions(b,a);
  EXPECT_EQ(b,3);
  EXPECT_EQ(a,4);
}
TEST(MatrixTest, getMatrix) {
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  const double** matr=matrix.getMatrix();
  EXPECT_EQ(matr[0][1], 2);
  EXPECT_EQ(matr[2][3], 999);
}
TEST(MatrixTest, getArrayFromMatrix){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix_2;
  EXPECT_THROW(matrix_2.getArrayFromMatrix(),MatrixSetError);
  std::unique_ptr<double[]> ptr=matrix.getArrayFromMatrix();
  for(int i=0;i<a*b;i++)
    EXPECT_EQ(ptr[i],ar[i]);
}
TEST(MatrixTest, setElement_Exception){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  EXPECT_THROW(matrix.setElement(5,2,10),OutOfRangeError);
  EXPECT_THROW(matrix.setElement(3,2,10),OutOfRangeError);
  EXPECT_THROW(matrix.setElement(2,-2,10),OutOfRangeError);
  EXPECT_THROW(matrix.setElement(1,1,NAN),DataError);
  EXPECT_THROW(matrix.setElement(1,1,INFINITY),DataError);

}
TEST(MatrixTest, setElement){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  matrix.setElement(2,2,5000.55);
  EXPECT_EQ(matrix.getElement(2,2),5000.55);
}
TEST(MatrixTest, setDimentions_Exception){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  EXPECT_THROW(matrix.setDimentions(-5,2),OutOfRangeError);
  EXPECT_THROW(matrix.setElement(2,5,10),OutOfRangeError);
  EXPECT_THROW(matrix.setElement(5,2,10),OutOfRangeError);
}
TEST(MatrixTest, setDimentions){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  matrix.setDimentions(5,5);
  EXPECT_EQ(matrix.getElement(2,2),9);
  EXPECT_EQ(matrix.getElement(0,3),8);
  EXPECT_EQ(matrix.getElement(2,0),7);
  EXPECT_EQ(matrix.getElement(2,3),999);
  EXPECT_EQ(matrix.getElement(3,3),0);
  EXPECT_EQ(matrix.getElement(4,4),0);
  EXPECT_EQ(matrix.getElement(4,3),0);
}
TEST(MatrixTest, setDimentions_2){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  matrix.setDimentions(3,4);
  EXPECT_EQ(matrix.getElement(2,2),9);
  EXPECT_EQ(matrix.getElement(0,3),8);
  EXPECT_EQ(matrix.getElement(2,0),7);
  EXPECT_EQ(matrix.getElement(2,3),999);
}
TEST(MatrixTest, setRows){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  matrix.setRows(5);
  EXPECT_EQ(matrix.getElement(2,2),9);
  EXPECT_EQ(matrix.getElement(0,3),8);
  EXPECT_EQ(matrix.getElement(2,0),7);
  EXPECT_EQ(matrix.getElement(2,3),999);
  EXPECT_EQ(matrix.getElement(4,2),0);
}
TEST(MatrixTest, setCols){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  matrix.setCols(5);
  EXPECT_EQ(matrix.getElement(2,2),9);
  EXPECT_EQ(matrix.getElement(0,3),8);
  EXPECT_EQ(matrix.getElement(2,0),7);
  EXPECT_EQ(matrix.getElement(2,3),999);
  EXPECT_EQ(matrix.getElement(2,4),0);
}
TEST(MatrixTest, setFull){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix;
  matrix.setFull(a,b,n,ar);
  EXPECT_EQ(matrix.getElement(2,2),9);
  EXPECT_EQ(matrix.getElement(0,3),8);
  EXPECT_EQ(matrix.getElement(2,0),7);
  EXPECT_EQ(matrix.getElement(2,3),999);
  EXPECT_EQ(matrix.getRows(),a);
  EXPECT_EQ(matrix.getCols(),b);
}
TEST(MatrixTest, matrixDimentionEq){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix2(a,b);
  S21Matrix matrix3(b,a);
  S21Matrix matrix5(a,a);
  EXPECT_EQ(matrix.matrixDimentionEq(matrix2),true);
  EXPECT_EQ(matrix.matrixDimentionEq(matrix3),false);
  EXPECT_EQ(matrix.matrixDimentionEq(matrix5),false);
}
TEST(MatrixTest, matrixDimentionEq_Exception){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix4;
  EXPECT_THROW(matrix.matrixDimentionEq(matrix4),MatrixSetError);
}
TEST(MatrixTest, doubleServiceMethods){
  double a=0.00000001, b=0, c=5.0,d=5, e=NAN,f=INFINITY;
  EXPECT_EQ(MatrixService::doubleEq(a,b),true);
  EXPECT_EQ(MatrixService::doubleEq(a,c),false);
  EXPECT_EQ(MatrixService::doubleEq(c,d),true);
  EXPECT_EQ(MatrixService::doubleEqComplex(a,b),true);
  EXPECT_EQ(MatrixService::doubleEqComplex(a,c),false);
  EXPECT_EQ(MatrixService::doubleEqComplex(c,d),true);
  EXPECT_THROW(MatrixService::doubleEqComplex(e,d),DataError);
  EXPECT_THROW(MatrixService::doubleEqComplex(-f,-f),DataError);
  EXPECT_THROW(MatrixService::doubleEqComplex(f,f),DataError);
  EXPECT_EQ(MatrixService::doubleEqComplex(f,-f),false);
  EXPECT_EQ(MatrixService::doubleEqComplex(-f,f),false);
  EXPECT_EQ(MatrixService::doubleEqComplex(c,-f),false);
  EXPECT_EQ(MatrixService::doubleEqComplex(f,a),false);
  EXPECT_EQ(MatrixService::doubleEqComplex(a,f),false);
  EXPECT_NO_THROW(MatrixService::doubleEqComplex(f,a));
  EXPECT_NO_THROW(MatrixService::doubleEqComplex(a,f));
  EXPECT_NO_THROW(MatrixService::doubleLegit(a));
  EXPECT_NO_THROW(MatrixService::doubleLegit(b));
  EXPECT_NO_THROW(MatrixService::doubleLegit(c));
  EXPECT_NO_THROW(MatrixService::doubleLegit(d));
  EXPECT_THROW(MatrixService::doubleLegit(e),DataError);
  EXPECT_THROW(MatrixService::doubleLegit(f),DataError);
  EXPECT_THROW(MatrixService::doubleLegit(-f),DataError);
}
TEST(MatrixTest, EqMatrix){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix2(a,b,n,ar);
  EXPECT_EQ(matrix.EqMatrix(matrix2),true);
  ar[3]=100;
  ar[14]=5.5;
  matrix2.setFull(a,b,n,ar);
  EXPECT_EQ(matrix.EqMatrix(matrix2),false);
  matrix2.setFull(b,b,n,ar);
  EXPECT_EQ(matrix.EqMatrix(matrix2),false);
  matrix.setFull(b,b,n,ar);
  EXPECT_EQ(matrix2.EqMatrix(matrix),true);
}
TEST(MatrixTest, operatorEQ){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix2(a,b,n,ar);
  EXPECT_EQ((matrix==matrix2),true);
  ar[3]=100;
  ar[14]=5.5;
  matrix2.setFull(a,b,n,ar);
  EXPECT_EQ((matrix==matrix2),false);
  matrix2.setFull(b,b,n,ar);
  EXPECT_EQ((matrix==matrix2),false);
  matrix.setFull(b,b,n,ar);
  EXPECT_EQ((matrix2==matrix),true);
}
TEST(MatrixTest, SumMatrix){
  double ar[]{1.1,2,3,8.9,
              4.005,5.666,6,-5,
              7.000001,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  double ar2[]{55.5, 32.0, -555, -7.777,
                123, 323.22, 123.55, 5555.5,
                  -0.1, -55.55, -0.0001, 12};
  n=sizeof(ar2)/sizeof(ar2[0]);
  S21Matrix matrix2(a,b,n,ar2);
  for(int i=0;i<a*b;i++)
    ar[i]+=ar2[i];
  matrix.SumMatrix(matrix2);
  std::unique_ptr<double[]> ar3= matrix.getArrayFromMatrix();
  for(int i=0;i<a*b;i++)
    EXPECT_EQ(ar[i],ar3[i]);
  matrix.print_matrix();
}
TEST(MatrixTest, SumMatrix_Exception){
  double ar[]{1.1,2,3,8.9,
              4.005,5.666,6,-5,
              7.000001,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix(a,b,n,ar);
  S21Matrix matrix2(a,a);
  EXPECT_THROW(matrix.SumMatrix(matrix2),DimentionEqualityError);
  ar[2]=NAN;
  matrix2.setFull(a,b,n,ar);
  EXPECT_THROW(matrix.SumMatrix(matrix2),DataError);
}










/*
TEST(MatrixTest, setFull){
  double ar[]{1,2,3,8,
              4,5,6,-5,
              7,8,9,999};
  int n=sizeof(ar)/sizeof(ar[0]);
  int a=3,b=4;
  S21Matrix matrix;
  matrix.setFull(a,b,n,ar);
  EXPECT_EQ(matrix.getElement(2,2),9);
  EXPECT_EQ(matrix.getElement(0,3),8);
  EXPECT_EQ(matrix.getElement(2,0),7);
  EXPECT_EQ(matrix.getElement(2,3),999);
  EXPECT_EQ(matrix.getRows(),a);
  EXPECT_EQ(matrix.getCols(),b);
  EXPECT_THROW(matrix.setDimentions(-5,2),OutOfRangeError);
}
*/



// elevator     end
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}