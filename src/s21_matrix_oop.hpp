#ifndef MATRIX_CPP_H
#define MATRIX_CPP_H
#include <iostream>
#include <cmath>
#include <memory>
#include "matrix_exceptions.hpp"

class S21Matrix {
    private:
        int rows_{0}, cols_{0};         // Rows and columns
        double **matrix_=nullptr;         // Pointer to the memory where the matrix is allocated

        void allocateMatrix();
        void freeMatrixPart(const int n)noexcept;
        void freeMatrix()noexcept{freeMatrixPart(rows_);}
    public:
        //constructor - destructor section
        S21Matrix()noexcept:rows_(0), cols_(0), matrix_(nullptr){}  // A default constructor that initialises a matrix of some predefined dimension.
        S21Matrix(const int rows, const int cols);      // Parametrized constructor with number of rows and columns.
        S21Matrix(int rows, int cols, int n, const double arr[]):S21Matrix(rows,cols){setMatrix(n, arr);}
        S21Matrix(const S21Matrix& other)noexcept; // Copy constructor.
        S21Matrix(S21Matrix&& other)noexcept;       // Move constructor.
        ~S21Matrix() noexcept;                       // Destructor.

        //getters and setters
        int getRows() const noexcept{return rows_;}
        int getCols() const noexcept{return cols_;}
        void getDimentions(int& rows, int& columns) const noexcept{
            rows = rows_;
            columns = cols_;
        }
        const double** getMatrix() const noexcept{return const_cast<const double**> (matrix_);} //dangerous one
        double getElement(const int row, const int col) const;
        std::unique_ptr<double[]> getArrayFromMatrix() const;

        void setElement(const int row, const int col, const double value);
        void setMatrix(const int n, const double array[]);
        void setRows(const int rows){setDimentions(rows,cols_);}
        void setCols(const int cols){setDimentions(rows_,cols);}
        void setDimentions(const int rows, const int columns);
        void setFull(const int r, const int c,const int n, const double ar[]){
            setDimentions(r,c);
            setMatrix(n,ar);
        }

        
        // methods
        // void print_matrix() const; // Print the matrix to the console.
        // bool EqMatrix(const S21Matrix& other) const;   //Checks matrices for equality with each other.
        // void SumMatrix(const S21Matrix& other);  //Adds the second matrix to the current one             //different matrix dimensions. 
        // void SubMatrix(const S21Matrix& other);  //Subtracts another matrix from the current one         //different matrix dimensions. 
        // void MulNumber(const double num);        //Multiplies the current matrix by a number.   
        // void MulMatrix(const S21Matrix& other);  //Multiplies the current matrix by the second matrix.   //The number of columns of the first matrix is not equal to the number of rows of the second matrix.
        // S21Matrix Transpose() const;                   //Creates a new transposed matrix from the current one and returns it.
        // S21Matrix CalcComplements() const;            //Calculates the algebraic addition matrix of the current one and returns it.  //The matrix is not square.    
        // double Determinant() const;                    //Calculates and returns the determinant of the current matrix.                //The matrix is not square.    
        // S21Matrix InverseMatrix() const;               //Calculates and returns the inverse matrix.                                   //Matrix determinant is 0. 


        // operarions overload
        // int& operator()(int row, int col) const; // Indexation by matrix elements (row, column).   // Index is outside the matrix. 
        // bool operator==(const S21Matrix& other) const;// Checks for matrices equality (`EqMatrix`). 
        // S21Matrix& operator=(const S21Matrix& other);// Assignment of values from one matrix to another one.
        // S21Matrix operator+(const S21Matrix& other) const; // Addition of two matrices.    //Different matrix dimensions.   
        // S21Matrix operator-(const S21Matrix& other) const; // Subtraction of one matrix from another.     //Different matrix dimensions.      
        // S21Matrix& operator+=(const S21Matrix& other); // Addition assignment (`SumMatrix`)         //different matrix dimensions.          
        // S21Matrix& operator-=(const S21Matrix& other); // Difference assignment (`SubMatrix`)       //different matrix dimensions. 
        // S21Matrix operator*(const S21Matrix& other) const;  //Matrix multiplication        //The number of columns of the first matrix does not equal the number of rows of the second matrix.
        // S21Matrix operator*(const double num) const;          // Multiplication of a matrix by a number.
        // S21Matrix& operator*=(const S21Matrix& other); // Multiplication assignment (`MulMatrix`/`MulNumber`).  //-  The number of columns of the first matrix does not equal the number of rows of the second matrix.
};
#endif // MATRIX_CPP_H


    
