#include "s21_matrix_oop.hpp"
#include "matrix_exceptions.hpp"


S21Matrix::S21Matrix(const int rows, const int cols){
    
    if (rows <= 0 || cols <= 0) 
        throw DimentionError();
    rows_=rows;
    cols_=cols;
    allocateMatrix();
}

void S21Matrix::allocateMatrix(){
    matrix_= new double*[rows_];
    if (!matrix_)
        throw MemoryAllocationError();
    
    for (int i = 0; i < rows_; ++i){
        matrix_[i]=new double [cols_]{0};
        if(!matrix_[i]){
            freeMatrixPart(i);
            throw MemoryAllocationError();
        }
    }
}

void S21Matrix::freeMatrixPart(const int n) noexcept{
    if(matrix_){
        for(int i=0;i<n;i++)
            delete[] matrix_[i];
        delete [] matrix_;
        matrix_=nullptr;
    }
}

S21Matrix::~S21Matrix()noexcept {
    freeMatrix();
    rows_=0;
    cols_=0;
}  

S21Matrix::S21Matrix(const S21Matrix& other) noexcept :S21Matrix(other.rows_,other.cols_){
    for (int i = 0; i < rows_; ++i){
        for (int j = 0; j < cols_; ++j){
            this->matrix_[i][j]=other.matrix_[i][j];
        }
    }
}

double S21Matrix::getElement(const int row, const int col) const{
    if(row>=rows_ || col>=cols_ || row<0 || col<0)
        throw OutOfRangeError();
    return matrix_[row][col];
}

void S21Matrix::setElement(const int row, const int col, const double value){
    if(row>=rows_ || col>=cols_|| row<0 || col<0)
        throw OutOfRangeError();
    if(!matrix_)
        throw MatrixSetError();
    matrix_[row][col]=value;
}

void S21Matrix::setMatrix(const int n, const double array[]){
    if(!matrix_)
        throw MatrixSetError();
    if (n<0 || !array)
        throw InputError();
    if(n>rows_*cols_)
        throw OutOfRangeError();
    
    for(int i=0,k=0;i<rows_;i++){
        for(int j=0;j<cols_;j++,k++){
            matrix_[i][j]=(k<n)?array[k]:0;
        }
    }    
}

std::unique_ptr<double[]> S21Matrix::getArrayFromMatrix() const {
    if(!matrix_)
        throw MatrixSetError();
    std::unique_ptr<double[]> array {std::make_unique<double[]>(rows_*cols_)};
    for(int i=0, k=0;i<rows_;i++){
        for (int j=0;j<cols_;j++, k++){
            array[k]=matrix_[i][j];
        }
    }
    return array;
}

void S21Matrix::setDimentions(const int rows, const int columns){
    if(rows<rows_ || columns<cols_)
        throw OutOfRangeError();
    else if (rows>rows_ || columns>cols_)
    {
        S21Matrix matrix2(rows,columns);
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                if(i< this->rows_ && j< this->cols_ )
                    matrix2.setElement(i,j,this->matrix_[i][j]);
                else
                    matrix2.setElement(i,j,0);
            }
        }
        this->~S21Matrix();
        this->rows_=matrix2.rows_;
        this->cols_=matrix2.cols_;
        this->matrix_=matrix2.matrix_;
        matrix2.rows_=0;
        matrix2.cols_=0;
        matrix2.matrix_=nullptr;
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept 
: rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

















