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
    setNullMatrix();
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
    doubleLegit(value);
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
            if(k<n){
                doubleLegit(array[k]);
                matrix_[i][j]=array[k];
            }
            else 
                matrix_[i][j]=0;
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
        replaceMatrix(matrix2);
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const{
    bool output=matrixDimentionEq(other);
    for(int i=0;output && i<rows_;i++){
        for(int j=0;output && j<cols_;j++){
            if(matrix_[i][j]!=other.matrix_[i][j])
                output=doubleEqComplex(matrix_[i][j],other.matrix_[i][j]);
        }
    }
    return output;
}

bool S21Matrix::matrixDimentionEq(const S21Matrix& other) const{
    if(!matrix_ || !other.matrix_)
        throw MatrixSetError();
    return ((rows_ == other.rows_) && (cols_ == other.cols_));
}

void S21Matrix::setNullMatrix()noexcept{
    rows_=0;
    cols_=0;
    matrix_=nullptr;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other)noexcept{
    if(this!=&other){
        this->~S21Matrix();
        this->setDimentions(other.rows_, other.cols_);
        for(int i=0;i<rows_;i++){
            for(int j=0;j<cols_;j++){
                this->matrix_[i][j]=other.matrix_[i][j];
            }
        }
    }
    return *this;
}

void S21Matrix::replaceMatrix(S21Matrix& other)noexcept{
    this->~S21Matrix();
    this->rows_=other.rows_;
    this->cols_=other.cols_;
    this->matrix_=other.matrix_;
    other.setNullMatrix();
}

S21Matrix S21Matrix::matrixSumSub(const S21Matrix& other, SumSub mod) const{    //check??
    S21Matrix result;
    if(!matrixDimentionEq(other) )
        throw DimentionEqualityError();
    result.setDimentions(this->rows_,this->cols_);
    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            doubleLegit(this->matrix_[i][j]);
            doubleLegit(other.matrix_[i][j]);
            switch(mod){
                case SumSub::Sum:
                    result.matrix_[i][j]=this->matrix_[i][j]+other.matrix_[i][j];
                    break;
                case SumSub::Sub:
                    result.matrix_[i][j]=this->matrix_[i][j]-other.matrix_[i][j];
                    break;
            }
        }
    }
    
    return result;
}

S21Matrix S21Matrix::operator*(const double num) const{
    if(!matrix_)
        throw MatrixSetError();
    doubleLegit(num);
    S21Matrix result=*this;
    for(int i=0;i<result.rows_;i++){
        for(int j=0;j<result.cols_;j++){
            doubleLegit(result.matrix_[i][j]);
            result.matrix_[i][j]=result.matrix_[i][j]*num;
        }
    }
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const{
    if(!matrix_||!other.matrix_)
        throw MatrixSetError();
    if(cols_!=other.rows_)
        throw DimentionAlignmentError();
    S21Matrix result(rows_,other.cols_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            result.matrix_[i][j] = 0;
            for (int k = 0; k < cols_; k++) {
                doubleLegit(this->matrix_[i][j]);
                doubleLegit(other.matrix_[i][j]);
                result.matrix_[i][j] += ((matrix_[i][k]) * (other.matrix_[k][j]));
            }
        }
    }
    return result;    
}

// template <typename T>       //sad
// S21Matrix& S21Matrix::operator*=(const T& other){       
//     std::variant< double, S21Matrix> v{other};
//     switch (v.index()) {
//         case 0: this->MulNumber(other); break;
//         case 1: this->MulMatrix(other); break;
//         default: throw InputError();
//     }
//     return *this;
// } 

S21Matrix::MatrixElement S21Matrix::operator()(const int row, const int col) const{
    if(row<0 ||col<0||row>=rows_||col>=cols_)
        throw OutOfRangeError();
    if(!matrix_)
        throw MatrixSetError();
    return MatrixElement(*this,row,col);
}

double S21Matrix::MatrixElement::operator=(const double input){     //check!!!!!
    if(!ptr)
        throw MatrixSetError();
    doubleLegit(input);
    *ptr=input;
    return input;
}

void S21Matrix::print_matrix() const noexcept{
    using std::cout,std::endl;
    if(!matrix_)  cout<<nullptr<<endl;
    else{
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) 
                cout<<matrix_[i][j]<<" ";
            cout<<endl;
        }
    }
}









