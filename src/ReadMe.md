# Matrix using *C*


![TopPicture](../DCIM/pic-0.jpg?raw=true "THE BEGINING")

## Contents  

1. [Chapter I. Teoretical information](#chapter-i-teoretical-information) \
   1.1. [Historical background](#historical-background)\
   1.2. [Matrix structure](#usual-matrix-structure)\
   1.3. [Matrix related terms](#terms) \
   1.4. [Extra information](#extra-information)
2. [Chapter II. Practical interpritation](#chapter-ii-practical-interpritation) \
   2.1. [Matrix structure in C language](#matrix-structure-in-c-language) \
   2.2. [Functions](#functions)\
   2.3. [Logic split](#logic-split)
3. [Chapter III. Check list](#chapter-iii-result-check-list) 



## Chapter I. Teoretical information

### Historical background

The first mentions of matrices (or as they were called then - "magic squares") were found in ancient China. \
They became famous in the middle of the 18th century thanks to the work of the famous mathematician Gabriel Cramer, who published his work "Introduction to the Analysis of Algebraic Curves", which described a fundamentally new algorithm for solving systems of linear equations. \
Soon after, the works of Carl Friedrich Gauss on the "classical" method of solving linear equations, the Cayley-Hamilton theorem, the works of Karl Weierstrass, Georg Frobenius, and other outstanding scientists were published. \
It was not until 1850 that James Joseph Sylvester introduced the term "Matrix" in his work.

### Usual matrix structure
```
    (1,1) (1,2) (1,3)
A = (2,1) (2,2) (2,3)
    (3,1) (3,2) (3,3)
```

### Terms

* A **matrix** is a collection of numbers arranged into a fixed number of rows and columns (in a way can be seent as tables).
* The **order** of a matrix is the number of its rows or columns.
* The **main diagonal** of a square matrix is the diagonal from the upper left to the lower right corner.
* A **column matrix** is a matrix with only one column (same logic with a **row matrix**) - can be called vectors too. 
* A **diagonal matrix** is a square matrix in which all elements outside the main diagonal are zero. 
* An **identity matrix** is a diagonal matrix with all diagonal elements equal to one:
* A **triangular matrix** is a square matrix with all elements on one side of the main diagonal equal to zero.
    ```
        1 2 3
    A = 0 4 5
        0 0 6
    ```
* The **determinant** is a number that is associated to each square matrix and calculated from the elements using special formulas (**The determinant can only be calculated for a square matrix**). The determinant of a matrix equals the sum of the products of elements of the row (column) and the corresponding algebraic complements.
* A matrix A to the power of -1 is called the **inverse** of a square matrix A if the product of these matrices equals the identity matrix.(**If the determinant of the matrix is zero, then it does not have an inverse**).The formula to calculate the inverse of matrix is $`A^{-1}=\frac{1} {|A|} × A_*^T`$ \
    * For the following matrix:
        ```
             2  5  7
        A =  6  3  4
             5 -2 -3
        ```
        The inverse matrix will look like this:
        ```
                                   1  -1   1
        A^(-1) =  1/|A| * M^T. = -38  41 -34
                                  27 -29  24 
        ```

### Extra information 

* The matrices A, B are ***equal*** |A = B| if they have the same dimensions and the corresponding elements are identical, thus for all i and j: A(i,j) = B(i,j)
* **The sum** of two matrices A = m × n and B = m × n of the same size is a matrix C = m × n = A + B of the same size whose elements are defined by the equations C(i,j) = A(i,j) + B(i,j).
* **The difference** of two matrices A = m × n and B = m × n of the same size is a matrix C = m × n = A - B of the same size whose elements are defined by the equations C(i,j) = A(i,j) - B(i,j).
* The product of **multiplication** of the matrix A = m × n by the number λ is the matrix B = m × n = λ × A whose elements are defined by the equations B = λ × A(i,j).
* The product of **multiplication** of A = m × k by B = k × n is a matrix C = m × n = A × B of size m × n whose elements are defined by the equation C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + ... + A(i,k) × B(k,j).
    ```
                1 4    1 -1  1    9 11 17   
    C = A × B = 2 5  × 2  3  4 = 12 13 22
                3 6              15 15 27
    ```
* The **transpose** of matrix A is in switching its rows with its columns with their numbers retained
    ```
              1 4   1 2 3
    A = A^T = 2 5 = 4 5 6
              3 6
    ```
* **Minor** M(i,j) is a (n-1)-order determinant obtained by deleting out the i-th row and the j-th column from the matrix A.
    * For the following matrix:
        ```
            1 2 3
        A = 0 4 2
            5 2 1
        ```

        The minor of the first element of the first row is:
        ```
        M(1,1) = 4 2
                 2 1

        |M| = 4 - 4 = 0
        ```

        The minors of matrix will look like this:
        ```
             0 -10 -20
        M = -4 -14  -8
            -8   2   4
        ```
* The **algebraic complement** of a matrix element is the value of the minor multiplied by -1^(i+j).
    * The matrix of algebraic complement for the previous example would look like this:
        ```
              0  10 -20
        M. =  4 -14   8
             -8  -2   4
        ```

## Chapter II. Practical interpritation

### Matrix structure in C language:
```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

### Functions

All operations (except matrix comparison) return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

#### Basic functions 

| Function | maning | 
|---|---|
|int s21_create_matrix(int rows, int columns, matrix_t *result);|Creating matrices (create_matrix)|
|void s21_remove_matrix(matrix_t *A);|Cleaning of matrices (remove_matrix)|

#### [Comperison](#extra-information) function
```c
#define SUCCESS 1
#define FAILURE 0
```

| Function | maning | 
|---|---|
|int s21_eq_matrix(matrix_t *A, matrix_t *B);|Matrix comparison (eq_matrix)|

* The comparison must be up to and including 7 decimal places.


#### [Matrix operations](#extra-information) functions

| Function | maning | 
|---|---|
|int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);|Adding matrices (sum_matrix) |
|int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);|Subtracting matrices (sub_matrix)|
|int s21_mult_number(matrix_t *A, double number, matrix_t *result);|Matrix multiplication by scalar (mult_number)|
|int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);|Multiplication of two matrices (mult_matrix)|

#### [Matrix nature](#extra-information) functions 

| Function | maning | 
|---|---|
|int s21_transpose(matrix_t *A, matrix_t *result);|Matrix transpose |
|int s21_calc_complements(matrix_t *A, matrix_t *result);| Matrix of algebraic complements (minors with proper signs)|
| int s21_determinant(matrix_t *A, double *result);| Matrix [determinant](#terms)|
|int s21_inverse_matrix(matrix_t *A, matrix_t *result);|[Inverse](#terms) of the matrix|

### Logic split
 * Due to the fact that according to the task we are using different Error_code structure for different functions, it's important to remember wich logic is used for wich function.

    |SUCCESS 1 <br> FAILURE 0|SUCCESS 0 <br> INPUT_ERRORR 1 <br> CALCULATION_ERROR 2|BIGGER 1 <br>EQUAL 0 <br>SMALLER -1<br>COMP_ERR 2|None/Other|
    |---|---|---|---|
    |int s21_the_matrix_sizer()|***int s21_create_matrix()***|int s21_double_compare()|***void s21_remove_matrix()***|
    |int s21_if_matrix_legit()|***int s21_sum_matrix()***||double s21_determinant_recursive()* |
    |int s21_more_presice_check()|***int s21_sub_matrix()***||void s21_mult_matrix_waggon()|
    |int s21_if_matrix_rows_legit()|***int s21_mult_number()***|||
    |int s21_if_matrix_legit_complex()|***int s21_mult_matrix()***|||
    |int s21_if_double_legit()|ing s21_recreate_matrix()|||
    |int s21_matrix_size_compare()|int s21_filling_matrix()|||
    |***int s21_eq_matrix()***|int s21_matrix_builder()|||
    |int s21_the_matrix_sizer()|int s21_matrix_rebuilder()|||
    ||***int s21_transpose()***|||
    ||***int s21_determinant()***|||
    ||int s21_minor_maker()|||
    ||int s21_minor_maker_complex()|||
    ||***int s21_calc_complements()***|||
    ||***int s21_inverse_matrix()***|||
    ||int s21_calc_complements_waggon()|||

    * For *s21_determinant_recursive()* **NAN** is an error code.

# Chapter III. Result check list

|Check|Task|
|---|---|
|✔|Implementation of the matrix.h library functions|
|✔|Implement basic operations with matrices (partially described [above](#matrix-operations)): create_matrix (creation), remove_matrix (cleaning and destruction), eq_matrix (comparison), sum_matrix (addition), sub_matrix (subtraction), mult_matrix (multiplication), mult_number (multiplication by number), transpose (transpose), determinant (calculation of determinant), calc_complements (calculation of matrix of algebraic complements), inverse_matrix (finding inverse of the matrix).|
|✔|The library must be developed in C language of C11 standard using gcc compiler;|
|✔|The library code must be located in the **src** folder on the develop branch;|
|✔|Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard;|
|✔|When writing code it is necessary to follow the Google style;|
|✔|Make it as a static library named *s21_matrix.a* (with the s21_matrix.h header file);|
|✔|The library must be developed according to the principles of structured programming;|
|✔|Use prefix s21_ before each function;|
|✔|Prepare full coverage of library functions code with unit-tests using the Check library;|
|✔|Unit tests must cover at least 80% of each function (checked using gcov);|
|✔|Provide a Makefile for building the library and tests (with targets all, clean, test, s21_matrix.a, gcov_report);|
|✔|The gcov_report target should generate a gcov report in the form of an html page. Unit tests must be run with gcov flags to do this; |
|✔|The matrix must be implemented as the structure described [above](#matrix-structure-in-c-language);|
|✔|Verifiable accuracy of the fractional part is up to 6 decimal places.|
