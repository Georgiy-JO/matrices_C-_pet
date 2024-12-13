# [Matrix using *C++*](/misc/media/w_sh_h_w_g_a.png)

![TopPicture](/misc/media/top_pic.png "THE BEGINING")

## Teoretical information

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
- You can get the desired element using indices as follows A[1,1] = 1, where the first index is the row number, the second is the column number.

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

## Implementation 
### Class structure
```c++
class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        S21Matrix();              // Default constructor
        ~S21Matrix();             // Destructor

        void SumMatrix(const S21Matrix& other); 
        // Other methods..
}
```
- Exceptional situations require special handling using the exception mechanism.
### Methods of the class

#### Function kind methods
| Check | Operation                                | Description                                                                 | Exceptional situations                                                                             |
| ----- | ---------------------------------------- | --------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| ✔     | `bool EqMatrix(const S21Matrix& other)`  | Checks matrices for equality with each other.                               |                                                                                                    |
| ✔     | `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one                                   | different matrix dimensions.                                                                       |
| ✔     | `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one                               | different matrix dimensions.                                                                       |
| ✔     | `void MulNumber(const double num) `      | Multiplies the current matrix by a number.                                  |                                                                                                    |
| ✔     | `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix.                         | The number of columns of the first matrix is not equal to the number of rows of the second matrix. |
| ✔     | `S21Matrix Transpose()`                  | Creates a new transposed matrix from the current one and returns it.        |                                                                                                    |
| ✔     | `S21Matrix CalcComplements()`            | Calculates the algebraic addition matrix of the current one and returns it. | The matrix is not square.                                                                          |
| ✔     | `double Determinant()`                   | Calculates and returns the determinant of the current matrix.               | The matrix is not square.                                                                          |
| ✔     | `S21Matrix InverseMatrix()`              | Calculates and returns the inverse matrix.                                  | Matrix determinant is 0.                                                                           |


#### Overloaded operators

| Check | Operator         | Description                                                  | Exceptional situations                                                                            |
| ----- | ---------------- | ------------------------------------------------------------ | ------------------------------------------------------------------------------------------------- |
| ✔     | `+`              | Addition of two matrices.                                    | Different matrix dimensions.                                                                      |
| ✔     | `-`              | Subtraction of one matrix from another.                      | Different matrix dimensions.                                                                      |
| ✔     | `*`              | Matrix multiplication and matrix multiplication by a number. | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| ✔     | `==`             | Checks for matrices equality (`EqMatrix`).                   |                                                                                                   |
| ✔     | `=`              | Assignment of values from one matrix to another one.         |                                                                                                   |
| ✔     | `+=`             | Addition assignment (`SumMatrix`)                            | different matrix dimensions.                                                                      |
| ✔     | `-=`             | Difference assignment (`SubMatrix`)                          | different matrix dimensions.                                                                      |
| ✔     | `*=`             | Multiplication assignment (`MulMatrix`/`MulNumber`).         | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| ✔     | `(int i, int j)` | Indexation by matrix elements (row, column).                 | Index is outside the matrix.                                                                      |


### Constructors and destructors

| Check | Method                              | Description                                                                 |     |
| ----- | ----------------------------------- | --------------------------------------------------------------------------- | --- |
| ✔     | `S21Matrix()`                       | A basic constructor that initialises a matrix of some predefined dimension. |     |
| ✔     | `S21Matrix(int rows, int cols) `    | Parametrized constructor with number of rows and columns.                   |     |
| ✔     | `S21Matrix(const S21Matrix& other)` | Copy constructor.                                                           |     |
| ✔     | `S21Matrix(S21Matrix&& other)`      | Move constructor.                                                           |     |
| ✔     | `~S21Matrix()`                      | Destructor.                                                                 |     |



## Key requirements
| Check | Task                                                                                                                                                                                                    |
| ----- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ✔     | Implementation of the s21_matrix_oop.h library functions                                                                                                                                                |
| ✔     | The program must be developed in C++ language of C++17 standard using gcc compiler;                                                                                                                     |
| ✔     | The program code must be located in the src folder;                                                                                                                                                     |
| ✔     | When writing code it is necessary to follow the Google style;                                                                                                                                           |
| ✔     | Implement the matrix as an `S21Matrix` class;                                                                                                                                                           |
| ✔     | Use only the `matrix_`, `rows_` and `cols_` fields as private;                                                                                                                                          |
| ✔     | Implement the access to private fields `rows_` and `cols_` via accessor and mutator. If the matrix increases in size, it is filled with zeros. If it decreases in size, the excess is simply discarded; |
| ✔     | Make it as a static library (with s21_matrix_oop.h header file);                                                                                                                                        |
| ✔     | Implement the operations described [above](#function-kind-methods);                                                                                                                                     |
| ✔     | Overload the operators according to the table [above](#overloaded-operators);                                                                                                                           |
| ✔     | Prepare full coverage of library functions code with unit-tests using the GTest library;                                                                                                                |
| ✔     | Provide a Makefile for building the library and tests (with targets all, clean, test, s21_matrix_oop.a).                                                                                                |
